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

#define PTR_OFFSET(x)   ((void*)(x))  // BUFFER_OFFSET

/**
 * Clear all errors in OpenGL
 */
SGE_API void    glClearError();

/**
 * Check OpenGL errors, return false and logerror if has errors
 */
SGE_API bool    glCheckError(const char* function, const char* file, int line);

/**
 * Log the gpu information
 */
SGE_API String  getGPUInfo();

namespace sge 
{
    /**
     * Some buffer type in opengl
     */
    enum    BufferType
    {
        // GL_ARRAY_BUFFER type
        VertexBuffer    =   GL_ARRAY_BUFFER,
        // GL_ELEMENT_ARRAY_BUFFER type
        ElementBuffer   =   GL_ELEMENT_ARRAY_BUFFER,
        // GL_UNIFORM_BUFFER type
        UniformBuffer   =   GL_UNIFORM_BUFFER,
        // GL_TRANSFORM_FEEDBACK_BUFFER type
        TransformBuffer =   GL_TRANSFORM_FEEDBACK_BUFFER,
        // GL_DRAW_INDIRECT_BUFFER type
        IndirectBuffer =    GL_DRAW_INDIRECT_BUFFER,
    };

    /**
     * Buffer desc
     * @template T for BufferType
     */
    template<BufferType T>
    class SGE_API GLBuffer
    {
    public:
        GLBuffer()
            : _id(0)
            , _size(0)
        {}

        virtual ~GLBuffer() { destory(); }

        /**
         * Get the id of the buffer
         */
        GLuint  id() const { return _id; }

        /**
         * Get the buffer size
         */
        GLuint  size() const { return _size; }

        /**
         * Get the buffer is valid
         */
        bool    isValid() const { return _id != 0; }

        /**
         * Create the buffer
         */
        void    create(size_t size, const void* data = NULL, GLenum usage = GL_STATIC_DRAW)
        {
            destory();
            GLCall(glGenBuffers(1, &_id));
            bind();
            GLCall(glBufferData(T, size, data, usage));
            _size   =   size;
            unbind();
        }

        /**
         * Update the buffer
         */
        void    update(size_t offset, size_t dataLen, void* data)
        {
            ASSERT(isValid() && offset + dataLen <= _size && dataLen > 0);
            bind();
            GLCall(glBufferSubData(T, offset, dataLen, data));
            unbind();
        }

        /**
         * Bind the buffer
         */
        void    bind() const { GLCall(glBindBuffer(T, _id)); }

        /**
         * Unbind the buffer
         */
        void    unbind() const { GLCall(glBindBuffer(T, 0)); }

        /**
         * Destory the buffer
         */
        void    destory()
        {
            if (isValid())
            {
                GLCall(glDeleteBuffers(1, &_id));
                _id     =   0;
                _size   =   0;
            }
        }

    protected:
        GLuint  _id;
        size_t  _size;

        DISABLE_COPY(GLBuffer)
    };

    typedef GLBuffer<VertexBuffer>      VBO;
    typedef GLBuffer<ElementBuffer>     IBO;
    typedef GLBuffer<ElementBuffer>     EBO;
    typedef GLBuffer<UniformBuffer>     UBO;
    typedef GLBuffer<IndirectBuffer>    CmdBO;

    /**
     * Some texture type
     */
    enum    TextureType
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
    class SGE_API   TextureBase
    {
    public:
        /**
         * Destructor
         */
        virtual ~TextureBase() { destory(); }

        /**
         * Get the type of texture
         */
        TextureType getType() const { return type; }
        
        /**
         * Get the texture id in gl
         */
        GLuint      getTexID() const { return _texId; }
        
        /**
         * Bind this texture
         */
        void        bind(int texUnit = 0) const { GLCall(glActiveTexture(GL_TEXTURE0 + texUnit)); GLCall(glBindTexture(type, _texId)); }
        
        /**
         * Unbind this texture
         */
        void        unbind() const { GLCall(glBindTexture(type, 0)); }
        
        /**
         * Check this texture valid
         */
        bool        isValid() const { return _texId != unsigned(-1); }
        
        /**
         * Destory this texture id
         */
        void        destory()
        {
            if (isValid())
            {
                GLCall(glDeleteTextures(1, &_texId));
                _texId  =   unsigned(-1);
            }
        }
    protected:
        TextureBase() 
            : _texId(unsigned(-1))
        {}

        GLuint  _texId;
        
        // repeat deleted if copy when destruct
        DISABLE_COPY(TextureBase)
    };

    /**
     * Class Texture2D
     */
    class SGE_API   Texture2D : public TextureBase<Tex2D>
    {
    public:
        /**
         * Constructor while null texture
         */
        Texture2D() 
            : _width(0)
            , _height(0)
        {}

        /**
         * Get the width of this texture
         */
        int     getWidth() { return _width; }

        /**
         * Get the height of this texture
         */
        int     getHeight() { return _height; }
        
        /**
         * Load/Reload texture form a image file
         */
        bool    loadFromFile(const char* file);

        /**
         * Load/Reload texture form a stream
         */
        bool    loadFromStream(byte* stream, size_t len);

        /**
         * Load/Reload texture form a raw dada with rgb format
         */
        bool    loadFromRGB(byte* data, int w, int h);

        /**
         * Load/Reload texture form a raw dada with rgba format
         */
        bool    loadFromRGBA(byte* data, int w, int h);
    private:
        int     _width;
        int     _height;

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


} // !namespace

#endif //!GLX
