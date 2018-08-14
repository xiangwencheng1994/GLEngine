/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGLSLUtil.h
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

#ifndef SGE_GLSL_UTIL_H
#define SGE_GLSL_UTIL_H

#include <sgeLog.h>
#include <sgeGLSLProgram.h>
#include <sgeMath.h>

#include <sgeFileReader.h>

namespace sge
{
    class PROGRAM_P3C4 : public GLSLProgram
    {
    public:
        const char* VS_FILE = "shader/P3C4.vs.glsl";
        const char* FS_FILE = "shader/C4.fs.glsl";
    public:
        uniform     _mvp;
        attribute   _position;
        attribute   _color;

        void begin() const
        {
            __super::begin();
            glEnableVertexAttribArray(_position);
            glEnableVertexAttribArray(_color);
        }

        void end() const
        {
            glDisableVertexAttribArray(_position);
            glDisableVertexAttribArray(_color);
            __super::end();
        }
    private:
        std::string getVertexShaderSrc() const { return FileReader(VS_FILE, NULL).readAll(); }
        std::string getFragmentShaderSrc() const { return FileReader(FS_FILE, NULL).readAll(); }        
        void onCreateAfter()
        {
            _mvp = getUniformLocation("_mvp");
            _position = getAttribLocation("_position");
            _color = getAttribLocation("_color");
        }
    };

    class PROGRAM_SKYBOX : public GLSLProgram
    {
    public:
        const char* VS_FILE = "shader/skybox.vs.glsl";
        const char* FS_FILE = "shader/skybox.fs.glsl";
    public:
        uniform     _mvp;
        attribute   _position;

        uniform     _cubeTexture;

        void begin() const
        {
            __super::begin();
            glGetIntegerv(GL_CULL_FACE_MODE, (GLint*)&OldCullFaceMode);
            glGetIntegerv(GL_DEPTH_FUNC, (GLint*)&OldDepthFuncMode);
            glCullFace(GL_FRONT);
            glDepthFunc(GL_LEQUAL);
            glEnableVertexAttribArray(_position);
        }

        void end() const
        {
            glCullFace(OldCullFaceMode);
            glDepthFunc(OldDepthFuncMode);
            glDisableVertexAttribArray(_position);
            __super::end();
        }
    private:
        GLint OldCullFaceMode;
        GLint OldDepthFuncMode;
    private:
        std::string getVertexShaderSrc() const { return FileReader(VS_FILE, NULL).readAll(); }
        std::string getFragmentShaderSrc() const { return FileReader(FS_FILE, NULL).readAll(); }
        void onCreateAfter()
        {
            _mvp = getUniformLocation("_mvp");
            _position = getAttribLocation("_position");
            _cubeTexture = getUniformLocation("_cubeTexture");
        }                
    };

}

#endif //!SGE_GLSL_UTIL_H