/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGLX.h
 * date: 2018/05/31
 * author: xiang
 *
 * License
 *
 * Copyright (c) 2017-2019, Xiang Wencheng <xiangwencheng@outlook.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * - Neither the names of its contributors may be used to endorse or
 *   promote products derived from this software without specific
 *   prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SGE_GLX_H
#define SGE_GLX_H

#include <core/sgePlatform.h>
#include <core/sgeMath.h>
#include <core/sgeLog.h>
#include <core/sgeGLSLProgram.h>

#define PTR_OFFSET(x) ((void*)(x))  // BUFFER_OFFSET

/**
 * Clear all errors in OpenGL
 */
SGE_API void glClearError();

/**
 * Check OpenGL errors, return false and logerror if has errors
 */
SGE_API bool glCheckError(const char* function, const char* file, int line);

namespace sge 
{
    /**
     * Some buffer type in opengl
     */
    enum BufferType
    {
        // GL_ARRAY_BUFFER type
        VertexBuffer    = GL_ARRAY_BUFFER,
        // GL_ELEMENT_ARRAY_BUFFER type
        ElementBuffer   = GL_ELEMENT_ARRAY_BUFFER,
        // GL_UNIFORM_BUFFER type
        UniformBuffer   = GL_UNIFORM_BUFFER,
        // GL_TRANSFORM_FEEDBACK_BUFFER type
        TransformBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
#ifndef OPENGLES
        // GL_DRAW_INDIRECT_BUFFER type
        IndirectBuffer = GL_DRAW_INDIRECT_BUFFER,
#endif
    };

    /**
     * Buffer desc
     * @template T for BufferType
     */
    template<BufferType T>
    struct BufferDesc
    {
        /**
         * The id of buffer by gl
         */
        GLuint  id;

        /**
         * The buffer size
         */
        size_t  size;

        /**
         * Constructor with gl id
         */
        BufferDesc(GLuint id = unsigned(-1)) : id(id), size(0) {}

        /**
         * Get the buffer is valid
         */
        bool isValid() const { return id != unsigned(-1); }
    };

    typedef BufferDesc<VertexBuffer>    VBO;
    typedef BufferDesc<ElementBuffer>   IBO;
    typedef BufferDesc<ElementBuffer>   EBO;
    typedef BufferDesc<UniformBuffer>   UBO;
#ifndef OPENGLES
    typedef BufferDesc<IndirectBuffer>  CmdBO;
#endif

    /**
     * Some texture type
     */
    enum TextureType
    {
        // GL_TEXTURE_2D type
        Tex2D       =   GL_TEXTURE_2D,
        // GL_TEXTURE_2D_ARRAY type
        Tex2DArray  =   GL_TEXTURE_2D_ARRAY,
        // GL_TEXTURE_3D type
        Tex3D       =   GL_TEXTURE_3D
    };

    /**
     * Base texture class
     */
    template<TextureType type>
    class TextureBase
    {
    public:
        /**
         * Destructor
         */
        ~TextureBase()
        {
            release();
        }

        /**
         * Get the type of texture
         */
        TextureType getType() const { return type; }
        
        /**
         * Get the texture id in gl
         */
        GLuint      getTexID() const { return mTexID; }
        
        /**
         * Bind this texture
         */
        void        bind(int texUnit = 0) const { GLCall(glActiveTexture(GL_TEXTURE0 + texUnit)); GLCall(glBindTexture(type, mTexID)); }
        
        /**
         * Unbind this texture
         */
        void        unbind() const { GLCall(glBindTexture(type, 0)); }
        
        /**
         * Check this texture valid
         */
        bool        isValid() const { return mTexID != unsigned(-1); }
        
        /**
         * Release this texture id
         */
        virtual void    release() 
        {
            if (isValid())
            {
                GLCall(glDeleteTextures(1, &mTexID));
                mTexID = unsigned(-1);
            }
        }
    protected:
        TextureBase(GLuint texId = unsigned(-1)) : mTexID(texId) {}
        GLuint  mTexID;

        friend class GLX;

        // repeat deleted if copy when destruct
        DISABLE_COPY(TextureBase)
    };

    /**
     * Class Texture2D
     */
    class SGE_API Texture2D : public TextureBase<Tex2D>
    {
    public:
        /**
         * Constructor while null texture
         */
        Texture2D() : mSize(0, 0) {}

        /**
         * Get the size of this texture
         */
        int2 getSize() { return mSize; }

        /**
         * Get the width of this texture
         */
        int getWidth() { return mSize.x; }

        /**
         * Get the height of this texture
         */
        int getHeight() { return mSize.y; }
        
        /**
         * Load/Reload texture form a image file
         */
        bool loadFromFile(const char* file);

        /**
         * Load/Reload texture form a stream
         */
        bool loadFromStream(byte* stream, size_t len);

        /**
         * Load/Reload texture form a raw dada with rgb format
         */
        bool loadFromRGB(byte* data, int w, int h);

        /**
         * Load/Reload texture form a raw dada with rgba format
         */
        bool loadFromRGBA(byte* data, int w, int h);
    private:
        int2    mSize;
        DISABLE_COPY(Texture2D);
    };

    /**
     * The indirect command struct for drawArray
     */
    typedef struct DrawArraysIndirectCommand_t
    {
        GLuint  count;          //vertex count
        GLuint  primCount;      //instance count
        GLuint  first;          //first vertex offset
        GLuint  baseInstance;   // base instance
    } DrawArraysIndirectCommand;
    
    /**
     * The indirect command struct for drawElements
     */
    typedef struct DrawElementsIndirectCommand_t
    {
        GLuint count;           //vertex/indices count
        GLuint primCount;       //instance count;
        GLuint firstIndex;      //first index offset;
        GLuint baseVertex;      //base vertex;
        GLuint baseInstance;    //base instance;
    } DrawElementsIndirectCommand;

    /**
     * Class GLX, easy to use OpenGL API
     */
    class GLX
    {
    public:

        /**
         * To log OpenGL version
         */
        static void logGLVersion()
        {
            const GLubyte* renderer = glGetString(GL_RENDERER);
            const GLubyte* vendor = glGetString(GL_VENDOR);
            const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
            GLint major, minor;
            glGetIntegerv(GL_MAJOR_VERSION, &major);
            glGetIntegerv(GL_MINOR_VERSION, &minor);
            Log::debug("GL Vendor: %s", vendor);
            Log::debug("GL Renderer: %s", renderer);
            Log::debug("GL Version: %d.%d, GLSL%s", major, minor, glslVersion);
        }
        
#pragma region Buffer
        
        /**
         * Create a buffer
         * @template T  The buffer type
         * @param size The buffer size
         * @param data The buffer data
         * @param usage The buffer usage
         * @return The buffer desc
         */
        template<BufferType T>
        static BufferDesc<T> createBuffer(size_t size, const void* data = NULL, GLenum usage = GL_STATIC_DRAW)
        {
            BufferDesc<T> buffer;
            buffer.size = size;
            GLCall(glGenBuffers(1, &buffer.id));
            GLCall(glBindBuffer(T, buffer.id));
            GLCall(glBufferData(T, size, data, usage));
            GLCall(glBindBuffer(T, 0));
            return buffer;
        }
        
        /**
         * Bind a buffer
         * @template T  The buffer type
         * @param buffer The buffer we wanted bind
         */
        template<BufferType T>
        static void bindBuffer(BufferDesc<T>* buffer)
        {
            GLCall(glBindBuffer(T, buffer ? buffer->id : 0));
        }
        
        /**
         * Update buffer data
         * @template T  The buffer type
         * @param buffer The buffer we wanted update
         * @param offset The start point of the buffer by byte counts
         * @param dataLen The len we wanted update by byte counts
         * @param data The new data pointer
         */
        template<BufferType T>
        static void updateBuffer(BufferDesc<T>& buffer, size_t offset, size_t dataLen, void* data)
        {
            ASSERT(buffer.isValid() && offset + dataLen <= buffer.size && dataLen);
            GLCall(glBindBuffer(T, buffer.id));
            GLCall(glBufferSubData(T, offset, dataLen, data));
            GLCall(glBindBuffer(T, 0));
        }

        /**
         * Delete a buffer
         * @template T  The buffer type
         * @param buffer The buffer we wanted delete
         */
        template<BufferType T>
        static void deleteBuffer(BufferDesc<T>& buffer)
        {
            if (buffer.isValid())
            {
                GLCall(glDeleteBuffers(1, &buffer.id));
                buffer.id = unsigned(-1);
            }
        }

        /**
         * Set a float vertex input pointer for a program attribute
         * @params see alse glVertexAttribPointer
         */
        static void setVertexAttribPointer(attribute attr, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
        {
            if (attr != unsigned(-1))
            {
                GLCall(glEnableVertexAttribArray(attr));
                GLCall(glVertexAttribPointer(attr, size, type, normalized, stride, pointer));
            }
        }

        /**
         * Set a int vertex input pointer for a program attribute
         * @params see alse glVertexAttribIPointer
         */
        static void setVertexAttribPointerI(attribute attr, GLint size, GLenum type, GLsizei stride, const void* pointer)
        {
            if (attr != unsigned(-1))
            {
                GLCall(glEnableVertexAttribArray(attr));
                GLCall(glVertexAttribIPointer(attr, size, type, stride, pointer));
            }
        }

#ifndef OPENGLES
        /**
         * Set a double vertex input pointer for a program attribute
         * @params see alse glVertexAttribIPointer
         */
        static void setVertexAttribPointerL(attribute attr, GLint size, GLenum type, GLsizei stride, const void* pointer)
        {
            if (attr != unsigned(-1))
            {
                GLCall(glEnableVertexAttribArray(attr));
                GLCall(glVertexAttribLPointer(attr, size, type, stride, pointer));
            }
        }
#endif

        /**
         * Disable a vertex trribute array
         */
        static void disableVertexAttribArray(attribute attr)
        {
            if (attr != unsigned(-1))
            {
                GLCall(glDisableVertexAttribArray(attr));
            }
        }

        /**
         * Delete a texture
         * @template T  The texture type
         * @param texture The texture we wanted delete
         */
        template<TextureType T>
        static void deleteTexture(TextureBase<T>& texture)
        {
            if (texture.isValid())
            {
                GLCall(glDeleteTextures(1, &texture.mTexID));
                texture.mTexID = unsigned(-1);
            }
        }

#pragma endregion
        
    private:
        GLX() = delete; // Delete constructor, all function static
    };

} // !namespace

#endif //!GLX
