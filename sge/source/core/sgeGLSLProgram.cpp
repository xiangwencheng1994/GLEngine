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

#include <core/sgeGLSLProgram.h>
#include <core/sgeLog.h>
#include <vector>

namespace sge
{

    class GLSLProgramPrivate
    {
        GLuint  program;
        std::vector<GLint> shaders;

        GLSLProgramPrivate() : program(0) { }
        ~GLSLProgramPrivate() 
        {
            ASSERT(program == 0);
        }

        bool AddShader(GLenum type, std::string src)
        {
            if (src.size() == 0)
            {
                return true;
            }
            //src.resize(src.size() + 1, 0);
            GLint   status = 0;
            char    compileLog[512] = { 0 };
            GLCall(GLint shader = glCreateShader(type));
            ASSERT(shader && "glCreateShader failed");
            char* source = (char*)src.c_str();
            GLCall(glShaderSource(shader, 1, (const GLchar**)&source, 0));
            GLCall(glCompileShader(shader));
            GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));
            if (status == GL_FALSE)
            {
                GLCall(glGetShaderInfoLog(shader, sizeof(compileLog), 0, compileLog));
                Log::error("Shader Compile faild: %s", compileLog);
                GLCall(glDeleteShader(shader));
                shader = NULL;
#if defined (_DEBUG) && defined(_MSC_VER)
                DebugBreak();
#elif defined _WIN32
                MessageBox(NULL, "Shader Compile faild, see log for more details.", "Error", MB_OK);
#endif
                return false;
            }
            shaders.push_back(shader);
            return true;
        }

        void CreateProgram()
        {
            GLCall(program = glCreateProgram());
            ASSERT(program && "glCreateProgram failed!");

            for (std::vector<GLint>::iterator it = shaders.begin();
                it != shaders.end(); it++)
            {
                GLint shader = *it;
                if (shader > 0)
                {
                    GLCall(glAttachShader(program, shader));
                }
            }
        }

        bool LinkProgram()
        {
            GLint   status = 0;
            char    compileLog[512] = { 0 };
            GLCall(glLinkProgram(program));
            GLCall(glGetProgramiv(program, GL_LINK_STATUS, &status));
            if (status == GL_FALSE)
            {
                GLCall(glGetProgramInfoLog(program, sizeof(compileLog), 0, compileLog));
                Log::error("Link GLProgram faild: %s", compileLog);
                GLCall(glDeleteProgram(program));
                program = NULL;
#if defined (_DEBUG) && defined(_MSC_VER)
                DebugBreak();
#elif defined _WIN32
                MessageBox(false, "Link GLProgram failed, see log for more details.", "Error", MB_OK);
#endif
                return false;
            }

            // remove shaders after built program that we don't need any more
            std::vector<GLint>::iterator it = shaders.begin();
            while (it != shaders.end())
            {
                GLint shader = *it;
                if (shader > 0)
                {
                    GLCall(glDeleteShader(shader));
                }
                it = shaders.erase(it);
            }
            ASSERT(shaders.size() == 0);

            return true;
        }

        void Destory()
        {
            ASSERT(shaders.size() == 0);
            if (program)
            {
                GLCall(glDeleteProgram(program));
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
        Destory();
        delete d;
    }

    bool GLSLProgram::Create()
    {
        bool ret = true;
        if (d->program == 0)
        {
            ret &= d->AddShader(GL_VERTEX_SHADER, GetVertexShaderSrc());
#ifndef OPENGLES
            ret &= d->AddShader(GL_TESS_CONTROL_SHADER, GetTessControlShaderSrc());
            ret &= d->AddShader(GL_TESS_EVALUATION_SHADER, GetTessEvaluationShaderSrc());
            ret &= d->AddShader(GL_GEOMETRY_SHADER, GetGeometryShaderSrc());
#endif // OPENGLES
            ret &= d->AddShader(GL_FRAGMENT_SHADER, GetFragmentShaderSrc());
            
            d->CreateProgram();
            this->OnBeforeLink();
            ret = d->LinkProgram();
            if (ret)
            {
                this->OnAfterCreate();
            }
        }
        return ret;
    }

    void GLSLProgram::Destory()
    {
        d->Destory();
    }

    void GLSLProgram::Begin() const
    {
        GLCall(glUseProgram(d->program));
    }

    void GLSLProgram::End() const
    {
        GLCall(glUseProgram(0));
    }

    GLuint GLSLProgram::ProgramId() const
    {
        return d->program;
    }

    uniform GLSLProgram::GetUniformLocation(const char * name) const
    {
        return glGetUniformLocation(d->program, name);
    }

#ifndef OPENGLES
       
    UniformBlock GLSLProgram::GetUniformBlock(const char * name) const
    {
        UniformBlock ub;
        ub.index = glGetUniformBlockIndex(d->program, name);
        GLCall(glGetActiveUniformBlockiv(d->program, ub.index, GL_UNIFORM_BLOCK_DATA_SIZE, &ub.blockSize));
        return ub;
    }

#endif // !OPENGLES

    attribute GLSLProgram::GetAttribLocation(const char * name) const
    {
        return glGetAttribLocation(d->program, name);
    }

}

