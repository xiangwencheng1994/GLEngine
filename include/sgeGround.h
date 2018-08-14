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
#include <sgeCamera.h>

namespace sge
{
    #define LINE_MAX            10
    #define LINE_VERTEX_COUNT   ((LINE_MAX * 2 + 1) * 4)

    /**
     * Class Ground
     */
    class Ground
    {
    public:

        /**
         * Create function, must called once before use
         */
        bool create()
        {
            plane = -0.001;

            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            float3 vertics[LINE_VERTEX_COUNT];
            int c = 0;
            for (int z = -LINE_MAX; z <= LINE_MAX; ++z)
            {
                vertics[c++] = vec3f(-LINE_MAX, 0, z);
                vertics[c++] = vec3f(LINE_MAX, 0, z);
            }
            for (int x = -LINE_MAX; x <= LINE_MAX; ++x)
            {
                vertics[c++] = vec3f(x, 0, -LINE_MAX);
                vertics[c++] = vec3f(x, 0, LINE_MAX);
            }
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertics), vertics, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            return true;
        }

        /**
         * Destory function
         */
        void destroy()
        {
        }

        /**
         * Render the ground
         */
        void render(const mat4f& mvp, const PROGRAM_P3C4& prg)
        {
            prg.begin();
            {
                glUniformMatrix4fv(prg._mvp, 1, false, mvp * mat4f::createTranslation(0, plane, 0));
                glBindBuffer(GL_ARRAY_BUFFER, vbo);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                glVertexAttribPointer(prg._position, 3, GL_FLOAT, false, 12, 0);
                glDisableVertexAttribArray(prg._color);
                glVertexAttrib4f(prg._color, 0.2, 0.2, 0.2, 1);
                glDrawArrays(GL_LINES, 0, LINE_VERTEX_COUNT);
            }
            prg.end();
        }

    protected:
        float plane;
        GLuint vbo;
    };

}

#endif // SGE_SKYBOX_H