#include <graphics/sgeGraphicsDevice.h>
#include <core/sgeLog.h>
#include "sgeOpenGL.h"

#pragma warning(disable: 4302) // ignored warning void* to uint
#pragma warning(disable: 4311) // ignored warning void* to uint
#pragma warning(disable: 4312) // ignored warning uint to void*

namespace sge
{
    
    static inline void glClearError()
    {
        while (GLenum error = glGetError());
    }

    static inline bool glCheckError(const char* function, const char* file, int line)
    {
        while (GLenum error = glGetError())
        {
            Log::error("[GLError:%#04X]%s(%d) %s", error, file, line, function);
            return false;
        }
        return true;
    }


    #ifdef _DEBUG
        #define GLCall(x)   glClearError();\
                            x;\
                            ASSERT(glCheckError(#x, __FILE__, __LINE__))
    #else
        #define GLCall(x)   x
    #endif


    static GLenum prefectVBOUsage(BufferPlace place)
    {
        GLenum usage = GL_STATIC_DRAW;
        switch (place)
        {
        case sge::NOCARE:
            usage = GL_DYNAMIC_COPY;
            break;
        case sge::GPU:
            usage = GL_STATIC_DRAW;
            break;
        case sge::AGP:
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
        case sge::VBO: return GL_VERTEX_ARRAY;
        case sge::IBO: return GL_ELEMENT_ARRAY_BUFFER;
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
        case sge::VBO: return GL_VERTEX_ARRAY_BINDING;
        case sge::IBO: return GL_ELEMENT_ARRAY_BUFFER_BINDING;
            //TODO: more buffer type
        default:
            break;
        }
        return GL_INVALID_ENUM;
    }

    GraphicsDevice::GraphicsDevice()
        : d(NULL)
    {
    }


    GraphicsDevice::~GraphicsDevice()
    {
    }


    NativeBufferId GraphicsDevice::createBuffer(BufferType type, size_t size, const void * data, BufferPlace place)
    {
        GLuint id = 0, oldBind = 0;
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



}
