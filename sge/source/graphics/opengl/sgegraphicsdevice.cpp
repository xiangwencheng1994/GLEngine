#include <graphics/sgeGraphicsDevice.h>
#include <core/sgeLog.h>

#include "sgeOpenGL.h"

#pragma warning(disable: 4302) // ignored warning void* to uint
#pragma warning(disable: 4311) // ignored warning void* to uint
#pragma warning(disable: 4312) // ignored warning uint to void*

namespace sge
{
    #define D_SET_ERROR(format, ...) d->setLastError(__FUNCTION__, format, __VA_ARGS__);
    #define glClearError()  while(glGetError());
    #ifdef _DEBUG
        #define GLCall(x)   glClearError();     \
                            x;                  \
                            while(GLenum gl_err = glGetError())    \
                                D_SET_ERROR("[Graphics]gl error : %#04X", gl_err)
    #else
        #define GLCall(x)   x
    #endif


    static GLenum prefectVBOUsage(BufferPlace place)
    {
        GLenum usage = GL_STATIC_DRAW;
        switch (place)
        {
        case sge::kNoCarePlace:
            usage = GL_DYNAMIC_COPY;
            break;
        case sge::kGPUPlace:
            usage = GL_STATIC_DRAW;
            break;
        case sge::kAGPPlace:
            usage = GL_DYNAMIC_DRAW;
            break;
        default:
            break;
        }
        return usage;
    }

    static GLenum getGLBufferType(BufferType type)
    {
        switch (type)
        {
        case sge::kVertexBufferType: return GL_ARRAY_BUFFER;
        case sge::kIndexBufferType: return GL_ELEMENT_ARRAY_BUFFER;
        //TODO: more buffer type
        default:
            break;
        }
        return GL_INVALID_ENUM;
    }

    static GLenum getGLBufferBindType(BufferType type)
    {
        switch (type)
        {
        case sge::kVertexBufferType: return GL_ARRAY_BUFFER_BINDING;
        case sge::kIndexBufferType: return GL_ELEMENT_ARRAY_BUFFER_BINDING;
            //TODO: more buffer type
        default:
            break;
        }
        return GL_INVALID_ENUM;
    }

    static GLenum getGLTextureWarpType(TextureWrapType wrap)
    {
        switch (wrap)
        {
        case sge::kTextureRepeat: return GL_REPEAT;
        case sge::kTextureClamp: return GL_CLAMP;
        case sge::kTextureBorder: return GL_CLAMP_TO_BORDER;
        case sge::kTextureMirror: return GL_MIRRORED_REPEAT;
        default:
            break;
        }
        return GL_REPEAT;
    }

    struct PixelFormatInfo
    {
        PixelFormatInfo(GLenum anInternalFormat, GLenum aFormat, GLenum aType, int aBpp, bool aCompressed, bool anAlpha)
            : internalFormat(anInternalFormat)
            , format(aFormat)
            , type(aType)
            , bpp(aBpp)
            , compressed(aCompressed)
            , alpha(anAlpha)
        {}

        GLenum internalFormat;
        GLenum format;
        GLenum type;
        int bpp;
        bool compressed;
        bool alpha;
    };

    typedef Map<PixelFormat, const PixelFormatInfo> PixelFormatInfoMap;

    class GraphicsDevicePrivate
    {
    public:
        GraphicsDevicePrivate()
        {
            memset(_errStr, 0, sizeof(_errStr));
        }

        const char* getLastError() const { return _errStr; }
        void setLastError(const char* fun, const char* msg, ...)
        {
            FORMAT_ARG(_errStr, 1024, msg);
            Log::error("[%s]%s", fun, _errStr);
        }

    public:
        PixelFormatInfoMap  _formatInfoMap;
    private:
        char    _errStr[1024];
    };

    
    GraphicsDevice::GraphicsDevice()
        : d(new GraphicsDevicePrivate())
    {
    }


    GraphicsDevice::~GraphicsDevice()
    {
        delete d;
    }


    bool GraphicsDevice::initialize()
    {
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            D_SET_ERROR("glewInit faild, %s", (const char*)glewGetErrorString(err));
        }

        typedef PixelFormatInfoMap::value_type PixelFormatInfoMapValue;
        
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::BGRA8888, PixelFormatInfo(GL_BGRA, GL_BGRA, GL_UNSIGNED_BYTE, 32, false, true)));
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::RGBA8888, PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 32, false, true)));
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::RGBA4444, PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, 16, false, true)));
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::RGB5A1, PixelFormatInfo(GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, 16, false, true)));
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::RGB565, PixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 16, false, false)));
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::RGB888, PixelFormatInfo(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, 24, false, false)));
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::A8, PixelFormatInfo(GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE, 8, false, false)));
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::I8, PixelFormatInfo(GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE, 8, false, false)));
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::AI88, PixelFormatInfo(GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, 16, false, true)));

#ifdef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::PVRTC2, PixelFormatInfo(GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, false)));
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::PVRTC2A, PixelFormatInfo(GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 2, true, true)));
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::PVRTC4, PixelFormatInfo(GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)));
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::PVRTC4A, PixelFormatInfo(GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, true)));
#endif
#ifdef GL_ETC1_RGB8_OES
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::ETC, PixelFormatInfo(GL_ETC1_RGB8_OES, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)));
#endif
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::S3TC_DXT1, PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)));
#endif
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::S3TC_DXT3, PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)));
#endif
#ifdef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::S3TC_DXT5, PixelFormatInfo(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)));
#endif
#ifdef GL_ATC_RGB_AMD
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::ATC_RGB, PixelFormatInfo(GL_ATC_RGB_AMD, 0xFFFFFFFF, 0xFFFFFFFF, 4, true, false)));
#endif
#ifdef GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::ATC_EXPLICIT_ALPHA, PixelFormatInfo(GL_ATC_RGBA_EXPLICIT_ALPHA_AMD, 0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)));
#endif
#ifdef GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD
        d->_formatInfoMap.insert(PixelFormatInfoMapValue(PixelFormat::ATC_INTERPOLATED_ALPHA, PixelFormatInfo(GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD, 0xFFFFFFFF, 0xFFFFFFFF, 8, true, false)));
#endif
        
        return err == GLEW_OK;
    }


    void GraphicsDevice::shutdown()
    {
    }

    
    const char * GraphicsDevice::getLastError()
    {
        return d->getLastError();
    }


    NativeBufferId GraphicsDevice::createBuffer(BufferType type, size_t size, const void * data, BufferPlace place)
    {
        GLuint id = reinterpret_cast<GLuint>(kInvalidBufferId), oldBind = 0;
        GLCall(glGenBuffers(1, &id));
        GLenum bufferType = getGLBufferType(type);
        GLenum bufferTypeBind = getGLBufferBindType(type);
        GLCall(glGetIntegerv(bufferTypeBind, (GLint*)&oldBind));
        GLCall(glBindBuffer(bufferType, id));
        GLCall(glBufferData(bufferType, size, data, prefectVBOUsage(place)));
        GLCall(glBindBuffer(bufferType, oldBind));
        return reinterpret_cast<NativeBufferId>(id);
    }


    void GraphicsDevice::destoryBuffer(NativeBufferId& buffer)
    {
        ASSERT(buffer);
        GLuint id = reinterpret_cast<GLuint>(buffer);
        GLCall(glDeleteBuffers(1, &id));
        buffer = NULL;
    }


    void GraphicsDevice::updateBuffer(NativeBufferId buffer, size_t offset, size_t size, const void* data)
    {
        ASSERT(buffer && size > 0 && data);
        GLuint id = reinterpret_cast<GLuint>(buffer);
        GLuint oldBind = 0;
        GLCall(glGetIntegerv(GL_COPY_WRITE_BUFFER_BINDING, (GLint*)&oldBind));
        GLCall(glBindBuffer(GL_COPY_WRITE_BUFFER, id));
        GLCall(glBufferSubData(GL_COPY_WRITE_BUFFER, offset, size, data));
        GLCall(glBindBuffer(GL_COPY_WRITE_BUFFER, oldBind));
    }


    void GraphicsDevice::getBufferData(NativeBufferId buffer, size_t offset, void* outData, size_t size)
    {
        ASSERT(buffer && outData && size > 0);
        GLuint id = reinterpret_cast<GLuint>(buffer);
        GLuint oldBind = 0;
        GLCall(glGetIntegerv(GL_COPY_READ_BUFFER_BINDING, (GLint*)&oldBind));
        GLCall(glBindBuffer(GL_COPY_READ_BUFFER, id));
        GLCall(glGetBufferSubData(GL_COPY_READ_BUFFER, offset, size, outData));
        GLCall(glBindBuffer(GL_COPY_READ_BUFFER, oldBind));
    }


    void GraphicsDevice::copyBufferData(NativeBufferId dist, NativeBufferId src, size_t distOffset, size_t srcOffset, size_t size)
    {
        ASSERT(dist && src && size > 0);
        GLuint readId = reinterpret_cast<GLuint>(dist);
        GLuint writeId = reinterpret_cast<GLuint>(dist);
        GLuint oldReadBind = 0, oldWriteBind = 0;
        GLCall(glGetIntegerv(GL_COPY_READ_BUFFER_BINDING, (GLint*)&oldReadBind));
        GLCall(glGetIntegerv(GL_COPY_WRITE_BUFFER_BINDING, (GLint*)&oldWriteBind));
        GLCall(glBindBuffer(GL_COPY_READ_BUFFER, readId));
        GLCall(glBindBuffer(GL_COPY_WRITE_BUFFER, writeId));
        GLCall(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, srcOffset, distOffset, size));
        GLCall(glBindBuffer(GL_COPY_READ_BUFFER, oldReadBind));
        GLCall(glBindBuffer(GL_COPY_WRITE_BUFFER, oldWriteBind));
    }


    size_t GraphicsDevice::queryBufferSize(NativeBufferId buffer)
    {
        GLuint id = reinterpret_cast<GLuint>(buffer);
        GLuint oldBind = 0;
        GLCall(glGetIntegerv(GL_COPY_READ_BUFFER_BINDING, (GLint*)&oldBind));
        GLCall(glBindBuffer(GL_COPY_READ_BUFFER, id));
        GLint64 size = 0;
        GLCall(glGetBufferParameteri64v(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size));
        GLCall(glBindBuffer(GL_COPY_READ_BUFFER, oldBind));
        return static_cast<size_t>(size);
    }


    NativeShaderProgramId GraphicsDevice::createShaderProgram(const char* vs, const char* ps)
    {
        GLint vsShader = 0;
        GLint psShader = 0;
        GLint program = reinterpret_cast<GLint>(kInvalidProgramId);
        GLint status = 0;
        char compileLog[512] = { 0 };

        do
        {
            GLCall(vsShader = glCreateShader(GL_VERTEX_SHADER));
            if (vsShader == 0)
            {
                D_SET_ERROR("Create Vertex Shader failed");
                break;
            }
            GLCall(glShaderSource(vsShader, 1, (const GLchar**)&vs, 0));
            GLCall(glCompileShader(vsShader));
            GLCall(glGetShaderiv(vsShader, GL_COMPILE_STATUS, &status));
            if (status == GL_FALSE)
            {
                GLCall(glGetShaderInfoLog(vsShader, sizeof(compileLog), 0, compileLog));
                D_SET_ERROR("Compile Vertex Shader failed: %s", compileLog);
                break;
            }

            GLCall(psShader = glCreateShader(GL_FRAGMENT_SHADER));
            if (psShader == 0)
            {
                D_SET_ERROR("Create Fragment Shader failed");
                break;
            }
            GLCall(glShaderSource(psShader, 1, (const GLchar**)&ps, 0));
            GLCall(glCompileShader(psShader));
            GLCall(glGetShaderiv(psShader, GL_COMPILE_STATUS, &status));
            if (status == GL_FALSE)
            {
                GLCall(glGetShaderInfoLog(psShader, sizeof(compileLog), 0, compileLog));
                D_SET_ERROR("Compile Fragment Shader failed: %s", compileLog);
                break;
            }

            GLCall(program = glCreateProgram());
            if (program == 0)
            {
                D_SET_ERROR("Create Program failed");
                break;
            }

            GLCall(glAttachShader(program, vsShader));
            GLCall(glAttachShader(program, psShader));

            GLCall(glLinkProgram(program));
            GLCall(glGetProgramiv(program, GL_LINK_STATUS, &status));

            if (status == GL_FALSE)
            {
                GLCall(glGetProgramInfoLog(program, sizeof(compileLog), 0, compileLog));
                GLCall(glDeleteProgram(program));
                D_SET_ERROR("Link Program failed: %s", compileLog);
                program = 0;
                break;
            }

        } while (false);

        if (vsShader) { GLCall(glDeleteShader(vsShader)); }
        if (psShader) { GLCall(glDeleteShader(psShader)); }

        return reinterpret_cast<NativeShaderProgramId>(program);
    }


    void GraphicsDevice::destoryShaderProgram(NativeShaderProgramId& program)
    {
        GLint programId = reinterpret_cast<GLint>(program);
        GLCall(glDeleteProgram(programId));
        program = sge::kInvalidProgramId;
    }


    NativeTextureId GraphicsDevice::createTexture2D(const void * data, size_t dataLen, PixelFormat pixelFormat, int width, int height)
    {
        MipmapInfo mipmap;
        mipmap.address = (byte*)data;
        mipmap.len = static_cast<int>(dataLen);
        return createTexture2D(&mipmap, 1, pixelFormat, width, height);
    }


    NativeTextureId GraphicsDevice::createTexture2D(MipmapInfo* mipmaps, size_t mipmapsNum, PixelFormat pixelFormat, int width, int height)
    {
        ASSERT(pixelFormat != PixelFormat::NONE && pixelFormat != PixelFormat::AUTO);
        ASSERT(width > 0 && height > 0);

        if (mipmapsNum <= 0)
        {
            return kInvalidTextureId;
        }

        auto formatItr = d->_formatInfoMap.find(pixelFormat);
        if (formatItr == d->_formatInfoMap.end())
        {
            return kInvalidTextureId;
        }

        const PixelFormatInfo& info = formatItr->second;

        GLint oldUnPackSize = 4;
        GLCall(glGetIntegerv(GL_UNPACK_ALIGNMENT, &oldUnPackSize));

        //Set the row align only when mipmapsNum == 1 and the data is uncompressed
        if (mipmapsNum == 1 && !info.compressed)
        {
            unsigned int bytesPerRow = width * info.bpp / 8;
            if (bytesPerRow % 8 == 0) { GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 8)); }
            else if (bytesPerRow % 4 == 0) { GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 4)); }
            else if (bytesPerRow % 2 == 0) { GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 2)); }
            else { GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1)); }
        }
        else
        {
            GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        }
        
        GLuint id = reinterpret_cast<GLuint>(kInvalidTextureId);

        GLuint oldBind = 0;
        GLCall(glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&oldBind));

        GLCall(glGenTextures(1, &id));
        GLCall(glBindTexture(GL_TEXTURE_2D, id));

        if (mipmapsNum == 1)
        {
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        }
        else
        {
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
        }

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getGLTextureWarpType(kTextureRepeat)));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getGLTextureWarpType(kTextureRepeat)));
        
        // Specify OpenGL texture image
        for (int i = 0; i < mipmapsNum; ++i)
        {
            const byte* data = mipmaps[i].address;
            GLsizei datalen = mipmaps[i].len;

            if (info.compressed)
            {
                GLCall(glCompressedTexImage2D(GL_TEXTURE_2D, i, info.internalFormat, (GLsizei)width, (GLsizei)height, 0, datalen, data));
            }
            else
            {
                GLCall(glTexImage2D(GL_TEXTURE_2D, i, info.internalFormat, (GLsizei)width, (GLsizei)height, 0, info.format, info.type, data));
            }
            
            if (i > 0 && (width != height || nextPOT(width) != width))
            {
                Log::warn("[Graphics] Create Texture2D with Mipmap level %u is not squared. Texture won't render correctly. width=%d != height=%d", i, width, height);
            }

            width = MAX(width >> 1, 1);
            height = MAX(height >> 1, 1);
        }
        
        GLCall(glBindTexture(GL_TEXTURE_2D, oldBind));
        GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, oldUnPackSize));
        return reinterpret_cast<NativeTextureId>(id);
    }


    void GraphicsDevice::updateTextureWarp(NativeTextureId texture, TextureWrapType wrapS, TextureWrapType wrapT)
    {
        GLuint id = reinterpret_cast<GLuint>(texture);

        GLuint oldBind = 0;
        GLCall(glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&oldBind));
        GLCall(glBindTexture(GL_TEXTURE_2D, id));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getGLTextureWarpType(wrapS)));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getGLTextureWarpType(wrapT)));
        GLCall(glBindTexture(GL_TEXTURE_2D, oldBind));
    }


    void GraphicsDevice::updateTextureMagnification(NativeTextureId texture, TextureMagnification mag)
    {
        GLuint id = reinterpret_cast<GLuint>(texture);

        GLuint oldBind = 0;
        GLCall(glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&oldBind));
        GLCall(glBindTexture(GL_TEXTURE_2D, id));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag == TextureMagnification::kTextureLinear ? GL_LINEAR : GL_NEAREST));
        GLCall(glBindTexture(GL_TEXTURE_2D, oldBind));
    }
    
    void GraphicsDevice::updateTextureMinification(NativeTextureId texture, TextureMinification min)
    {
        GLuint id = reinterpret_cast<GLuint>(texture);

        GLenum filter;
        switch (min)
        {
        case sge::kTextureNearestMipmapNearest: filter = GL_NEAREST_MIPMAP_NEAREST; break;
        case sge::kTextureLinearMipmapNearest: filter = GL_LINEAR_MIPMAP_NEAREST; break;
        case sge::kTextureNearestMipmapLinear: filter = GL_NEAREST_MIPMAP_LINEAR; break;
        case sge::kTextureLinearMipmapLinear: filter = GL_LINEAR_MIPMAP_LINEAR; break;
        default: filter = GL_NEAREST_MIPMAP_NEAREST; break;
        }

        GLuint oldBind = 0;
        GLCall(glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&oldBind));
        GLCall(glBindTexture(GL_TEXTURE_2D, id));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter));
        GLCall(glBindTexture(GL_TEXTURE_2D, oldBind));
    }

    void GraphicsDevice::updateTexture2D(NativeTextureId texture, const void * data, PixelFormat pixelFormat, int offsetX, int offsetY, int width, int height)
    {
        ASSERT(pixelFormat != PixelFormat::NONE && pixelFormat != PixelFormat::AUTO);
        ASSERT(width > 0 && height > 0);

        GLuint id = reinterpret_cast<GLuint>(texture);
        
        GLuint oldBind = 0;
        GLCall(glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&oldBind));
        GLCall(glBindTexture(GL_TEXTURE_2D, id));
        const PixelFormatInfo& info = d->_formatInfoMap.at(pixelFormat);
        GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, width, height, info.format, info.type, data));
        GLCall(glBindTexture(GL_TEXTURE_2D, oldBind));
    }


    void GraphicsDevice::destoryTexture(NativeTextureId & texture)
    {
        GLuint id = reinterpret_cast<GLuint>(texture);
        GLCall(glDeleteTextures(1, &id));
        texture = kInvalidTextureId;
    }

}
