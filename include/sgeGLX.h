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
* Copyright (c) 2017-2018, Xiang Wencheng <xiangwencheng@outlook.com>
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

#include <sge.h>

#include <glew/glew.h>

#define PTR_OFFSET(x) ((void*)(x))  // BUFFER_OFFSET

namespace sge 
{

    /**
     * The buffer types
     */
    enum BufferType
    {
        Vertex  =   GL_ARRAY_BUFFER,
        Element =   GL_ELEMENT_ARRAY_BUFFER,
        //TODO: add more type support
    };

    /**
     * The buffer usage
     * "Static*" means the data will not modified
     * "Dynamic*" means the data can be modified
     * "Stream*" means the data will modified very frequently
     * "*Draw" means the data usually be used for drawing, VBO must has it
     * "*Read" means the data usually be used for user reading
     * "*Copy" means the data usually be used for copying between buffers
     */
    enum BufferUsage
    {
        StaticDraw  =   GL_STATIC_DRAW,
        StaticRead  =   GL_STATIC_READ,
        StaticCopy  =   GL_STATIC_COPY,
        DynamicDraw =   GL_DYNAMIC_DRAW,
        DynamicRead =   GL_DYNAMIC_READ,
        DynamicCopy =   GL_DYNAMIC_COPY,
        StreamDraw  =   GL_STREAM_DRAW,
        StreamRead  =   GL_STREAM_READ,
        StreamCopy  =   GL_STREAM_COPY,
    };

    /**
     * Class GLX, easy to use OpenGL API
     */
    class GLX
    {
    public:

        /**
         * Create a buffer.
         */
        static GLuint CreateBuffer(BufferType type, BufferUsage usage, size_t size, const void* data = NULL)
        {
            GLuint id;
            glGenBuffers(1, &id);
            glBindBuffer(type, id);            
            glBufferData(type, size, data, usage);
            return id;
        }


    private:
        GLX() = delete; // Delete constructor, all function static
    };

} // !namespace

#endif //!GLX