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

#include <core/sgeGLSLProgram.h>
#include <core/sgeLog.h>
#include <vector>

namespace sge
{
        
    bool GLSLProgram::create()
    {
        assert(_programId == 0);
        bool    ret =   false;
        GLuint  vs  =   0;
        GLuint  tcs =   0;
        GLuint  tes =   0;
        GLuint  gs  =   0;
        GLuint  fs  =   0;
        do
        {
            String  vsSource    =   getVertexShaderSrc();
            if (vsSource.size() > 0) 
            {
                if (0 == (vs = createShader(GL_VERTEX_SHADER, vsSource.c_str())))
                    break;
            }

            String  tcsSource   =   getTessControlShaderSrc();
            if (tcsSource.size() > 0)
            {
                if (0 == (tcs = createShader(GL_TESS_CONTROL_SHADER, tcsSource.c_str())))
                    break;
            }

            String  tesSource   =   getTessEvaluationShaderSrc();
            if (tesSource.size() > 0)
            {
                if (0 == (tes = createShader(GL_TESS_EVALUATION_SHADER, tesSource.c_str())))
                    break;
            }

            String  gsSource    =   getGeometryShaderSrc();
            if (gsSource.size() > 0)
            {
                if (0 == (gs = createShader(GL_GEOMETRY_SHADER, gsSource.c_str())))
                    break;
            }

            String  fsSource    =   getFragmentShaderSrc();
            if (fsSource.size() > 0)
            {
                if (0 == (fs = createShader(GL_FRAGMENT_SHADER, fsSource.c_str())))
                    break;
            }

            GLCall(_programId = glCreateProgram());
            ASSERT(_programId && "glCreateProgram failed");

            if (vs)     GLCall(glAttachShader(_programId, vs));
            if (tcs)    GLCall(glAttachShader(_programId, tcs));
            if (tes)    GLCall(glAttachShader(_programId, tes));
            if (gs)     GLCall(glAttachShader(_programId, gs));
            if (fs)     GLCall(glAttachShader(_programId, fs));

            onBeforeLink();

            GLint   status  =   0;
            char    compileLog[512] =   { 0 };
            GLCall(glLinkProgram(_programId));
            GLCall(glGetProgramiv(_programId, GL_LINK_STATUS, &status));
            if (status == GL_FALSE)
            {
                GLCall(glGetProgramInfoLog(_programId, sizeof(compileLog), 0, compileLog));
                _lastError  =   compileLog;
                Log::error("Link GLProgram faild: %s", compileLog);
                break;
            }

            onAfterCreate();
            ret =   true;

        } while (false);
        
        if (vs)     GLCall(glDeleteShader(vs));
        if (tcs)    GLCall(glDeleteShader(tcs));
        if (tes)    GLCall(glDeleteShader(tes));
        if (gs)     GLCall(glDeleteShader(gs));
        if (fs)     GLCall(glDeleteShader(fs));
        if (!ret && _programId) GLCall(glDeleteProgram(_programId));

        return  ret;
    }

    GLint GLSLProgram::createShader(GLenum type, const char* src)
    {
        GLint   status  =   0;
        char    compileLog[512] =   { 0 };

        GLCall(GLint shader = glCreateShader(type));
        ASSERT(shader && "glCreateShader failed");

        GLCall(glShaderSource(shader, 1, (const GLchar**)&src, 0));
        GLCall(glCompileShader(shader));

        GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));
        if (status == GL_FALSE)
        {
            GLCall(glGetShaderInfoLog(shader, sizeof(compileLog), 0, compileLog));
            _lastError  =   compileLog;
            Log::error("Shader Compile faild: %s", compileLog);
            GLCall(glDeleteShader(shader));
            shader  =   0;
        }
        return  shader;
    }

}

