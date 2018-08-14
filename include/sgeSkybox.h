/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeSkybox.h
 * date: 2017/12/21
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

#ifndef SGE_SKYBOX_H
#define SGE_SKYBOX_H

#include <sge.h>
#include <sgeGLSLUtil.h>
#include <sgeTexture.h>

namespace sge
{
    /**
     * Class Skybox
     */
    class Skybox
    {
    public:
        TexureCubeFile files;

        /**
         * Create function, must called once before use
         */
        bool create()
        {
            bool ret = _PROGRAM_SKYBOX.create();
            if (ret)
            {
                _cubeTex = loadTextureCubeFromFile(files);
                glGenBuffers(1, &_vbo);
                glBindBuffer(GL_ARRAY_BUFFER, _vbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);
                glGenBuffers(1, &_ibo);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeTrianglesIndices), CubeTrianglesIndices, GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
            return ret;
        }

        /**
         * Destory function
         */
        void destroy()
        {
            glDeleteTextures(1, &_cubeTex);
            glDeleteBuffers(1, &_vbo);
            glDeleteBuffers(1, &_ibo);
        }

        /**
         * Render the skybox
         */
        void render(const mat4f& mvp)
        {
            _PROGRAM_SKYBOX.begin();
            {
                glUniformMatrix4fv(_PROGRAM_SKYBOX._mvp, 1, false, mvp);
                glUniform1i(_PROGRAM_SKYBOX._cubeTexture, 0);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeTex);
                glBindBuffer(GL_ARRAY_BUFFER, _vbo);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
                glVertexAttribPointer(_PROGRAM_SKYBOX._position, 3, GL_FLOAT, GL_FALSE, 0, PTR_OFFSET(0));
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);
            }
            _PROGRAM_SKYBOX.end();
        }

    protected:
        PROGRAM_SKYBOX _PROGRAM_SKYBOX;
        GLuint _cubeTex;
        GLuint _vbo, _ibo;
    };

}

#endif // SGE_SKYBOX_H