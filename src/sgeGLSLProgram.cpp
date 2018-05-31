/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGLSLProgram.cpp
 * date: 2017/12/12
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

#include <sgeGLSLProgram.h>
#include <sgeLog.h>
#include <vector>

namespace sge
{

    class GLSLProgramPrivate
    {
        GLuint  program;
        std::vector<GLint> shaders;

        GLSLProgramPrivate() : program(0) { }
        ~GLSLProgramPrivate() { destory(); }

        bool addShader(GLenum type, const char* src)
        {
            if (src == NULL)
            {
                return false;
            }
            GLint   status = 0;
            char    compileLog[512] = { 0 };
            GLint shader = glCreateShader(type);
            assert(shader && "glCreateShader failed");
            glShaderSource(shader, 1, (const GLchar**)&src, 0);
            glCompileShader(shader);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE)
            {
                glGetShaderInfoLog(shader, sizeof(compileLog), 0, compileLog);
                Log::error("Shader Compile faild: %s", compileLog);
                glDeleteShader(shader);
                shader = NULL;
#ifdef _WIN32
                ::MessageBoxA(NULL, "Compile OpenGL Shader failed, see log for more details.", "Error", MB_OK);
#endif
                return false;
            }
            shaders.push_back(shader);
            return true;
        }

        bool createProgram()
        {
            program = glCreateProgram();
            assert(program && "glCreateProgram failed!");

            for (std::vector<GLint>::iterator it = shaders.begin();
                it != shaders.end(); it++)
            {
                GLint shader = *it;
                if (shader > 0)
                {
                    glAttachShader(program, shader);
                }
            }

            GLint   status = 0;
            char    compileLog[512] = { 0 };
            glLinkProgram(program);
            glGetProgramiv(program, GL_LINK_STATUS, &status);
            if (status == GL_FALSE)
            {
                glGetProgramInfoLog(program, sizeof(compileLog), 0, compileLog);
                Log::error("Link GLProgram faild: %s", compileLog);
                glDeleteProgram(program);
                program = NULL;
#ifdef _WIN32
                ::MessageBoxA(NULL, "Link GLProgram failed, see log for more details.", "Error", MB_OK);
#endif
                return false;
            }
            return true;
        }

        void destory()
        {
            std::vector<GLint>::iterator it = shaders.begin();
            while (it != shaders.end())
            {
                GLint shader = *it;
                if (shader > 0)
                {
                    glDeleteShader(shader);
                }
                it = shaders.erase(it);
            }
            assert(shaders.size() == 0);
            if (program)
            {
                glDeleteProgram(program);
                program = NULL;
            }
        }

        friend class GLSLProgram;
    };


    GLSLProgram::GLSLProgram()
        : d(new GLSLProgramPrivate())
    {
    }

    GLSLProgram::~GLSLProgram()
    {
        delete d;
    }

    bool GLSLProgram::create()
    {
        bool ret = true;
        if (d->program == 0)
        {
            d->addShader(GL_VERTEX_SHADER, getVertexShaderSrc());
            d->addShader(GL_TESS_CONTROL_SHADER, getTessControlShaderSrc());
            d->addShader(GL_TESS_EVALUATION_SHADER, getTessEvaluationShaderSrc());
            d->addShader(GL_GEOMETRY_SHADER, getGeometryShaderSrc());
            d->addShader(GL_FRAGMENT_SHADER, getFragmentShaderSrc());

            ret = d->createProgram();
            if (ret)
            {
                this->onCreateAfter();
            }
        }
        return ret;
    }

    void GLSLProgram::destory()
    {
        d->destory();
    }

    void GLSLProgram::begin() const
    {
        glUseProgram(d->program);
    }

    void GLSLProgram::end() const
    {
        glUseProgram(0);
    }

    GLuint GLSLProgram::getProgramId() const
    {
        return d->program;
    }

    uniform GLSLProgram::getUniformLocation(const char * name) const
    {
        return glGetUniformLocation(d->program, name);
    }

    attribute GLSLProgram::getAttribLocation(const char * name) const
    {
        return glGetAttribLocation(d->program, name);
    }

}

