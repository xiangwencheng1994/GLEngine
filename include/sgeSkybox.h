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
     * The Skybox Shader Program
     */
    class SkyboxProgram : public GLSLProgram
    {
    public:
        SkyboxProgram() : position(-1), projection(-1), view(-1), cube(-1) {}

        attribute   position;

        virtual void begin() const
        {
            __super::begin();
            glEnableVertexAttribArray(position);
            glDepthFunc(GL_LEQUAL);
            glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        }

        virtual void end() const
        {
            glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
            glDepthFunc(GL_LESS);
            glDisableVertexAttribArray(position);
            __super::end();
        }

        virtual void setProjection(const mat4f& mvp)
        {
            glUniformMatrix4fv(this->projection, 1, GL_FALSE, mvp);
        }

        virtual void setView(const mat4f& view)
        {
            glUniformMatrix4fv(this->view, 1, GL_FALSE, view);
        }

        virtual void setSkyCubeUnit(GLuint index)
        {
            glUniform1i(this->cube, index);
        }

    protected:
        uniform     projection;
        uniform     view;
        uniform     cube;

        virtual const char* getVertexShaderSrc() const
        {
            const char* vs = GLSL_VERSION ENDL
                "in vec3 position;" ENDL
                "out vec3 TexCoord;" ENDL
                "uniform mat4 projection;" ENDL
                "uniform mat4 view;" ENDL
                "void main()" ENDL
                "{" ENDL
                "   TexCoord = position;" ENDL
                "   vec4 pos = projection * view * vec4(position, 1.0);" ENDL
                "   gl_Position = pos.xyww;" ENDL
                "}" ENDL;
            return vs;
        }

        virtual const char* getFragmentShaderSrc() const
        {
            const char* fs = GLSL_VERSION ENDL
                "in vec3 TexCoord;" ENDL
                "out vec4 FragColor;" ENDL
                "uniform samplerCube skybox;" ENDL
                "void main()" ENDL
                "{" ENDL
                "   FragColor = texture(skybox, TexCoord);" ENDL
                "}" ENDL;
            return fs;
        }

        virtual void onCreateAfter()
        {
            position = getAttribLocation("position");
            projection = getUniformLocation("projection");
            view = getUniformLocation("view");
            cube = getUniformLocation("skybox");
        }

    };
    
    /**
     * The cube verts
     */
    const float skyboxVerts[] = 
    {
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f
    };

    /**
     * The Element index
     */
    const GLubyte skyboxIndex[] = 
    {
        0, 2, 1, 0, 3, 2,
        4, 6, 5, 4, 7, 6,
        5, 2, 3, 5, 6, 2,
        4, 1, 7, 4, 0, 1,
        7, 2, 6, 7, 1, 2,
        4, 3, 0, 4, 5, 3,
    };

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
            bool ret = pro.create();
            if (ret)
            {
                skyboxCubeTex = loadTextureCubeFromFile(files);
                glGenBuffers(1, &skyBoxVBOId);
                glBindBuffer(GL_ARRAY_BUFFER, skyBoxVBOId);
                glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVerts), skyboxVerts, GL_STATIC_DRAW);
                glGenBuffers(1, &skyBoxEBOId);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyBoxEBOId);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndex), skyboxIndex, GL_STATIC_DRAW);
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
            glDeleteTextures(1, &skyboxCubeTex);
            glDeleteBuffers(1, &skyBoxVBOId);
            glDeleteBuffers(1, &skyBoxEBOId);
        }

        /**
         * Render the skybox
         */
        void render(const mat4f& projection, const mat4f& view)
        {
            pro.begin();
            {
                pro.setProjection(projection);
                pro.setView(view);
                pro.setSkyCubeUnit(0);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxCubeTex);
                glBindBuffer(GL_ARRAY_BUFFER, skyBoxVBOId);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyBoxEBOId);
                glVertexAttribPointer(pro.position, 3, GL_FLOAT, GL_FALSE, 0, PTR_OFFSET(0));
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);
            }
            pro.end();
        }

    protected:
        SkyboxProgram pro;
        GLuint skyboxCubeTex;
        GLuint skyBoxVBOId, skyBoxEBOId;
    };

}

#endif // SGE_SKYBOX_H