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

#ifndef SGE_GLSL_UTIL_H
#define SGE_GLSL_UTIL_H

#include <core/sgeLog.h>
#include <core/sgeGLSLProgram.h>
#include <core/sgeGLX.h>

#include <core/sgeFileReader.h>

namespace sge
{
    /**
     * PROGRAM from ShaderPath
     * read ShaderPath.vert for vertex shader source if exists
     * read ShaderPath.tesc for tess control shader source if exists
     * read ShaderPath.tese for tess evaluation shader source if exists
     * read ShaderPath.geom for geometry shader source if exists
     * read ShaderPath.frag for fragment shader source if exists
     */
    class SGE_API   PROGRAM_FILED : public GLSLProgram
    {
    public:
        /**
         * The ShaderPath
         */
        virtual const char* getShaderPath() const   =   0;

    private:
        virtual String  tryGetShader(const char* type) const
        {
            bool    hasFile =   false;
            char    path[MAX_PATH];
            sprintf(path, "%s.%s", getShaderPath(), type);
            FileReader  file(path, &hasFile);
            return  hasFile ? file.ReadAll() : String();
        }

        virtual String  getVertexShaderSrc() const override { return tryGetShader("vert"); }
        virtual String  getTessControlShaderSrc() const override { return tryGetShader("tesc"); }
        virtual String  getTessEvaluationShaderSrc() const override { return tryGetShader("tese"); }
        virtual String  getGeometryShaderSrc() const override { return tryGetShader("geom"); }
        virtual String  getFragmentShaderSrc() const override { return tryGetShader("frag"); }
    };

    /**
     * The base P3 C4 program
     */
    class SGE_API   PROGRAM_P3C4 : public PROGRAM_FILED
    {
    public:
        const char* getShaderPath() const override { return "shader/P3C4"; }

    public:
        uniform     _mvp;
        attribute   _position;
        attribute   _color;
        
    private:
        void onAfterCreate() override
        {
            _mvp        =   getUniformLocation("_mvp");
            _position   =   getAttribLocation("_position");
            _color      =   getAttribLocation("_color");
        }
    };

    /**
     * The cube texture sky box demo program
     */
    class SGE_API   PROGRAM_SKYBOX : public PROGRAM_FILED
    {
    public:
        const char* getShaderPath() const override { return "shader/Skybox"; }

    public:
        attribute   _position;
        uniform     _mvp;
        uniform     _cubeTexture;

        void    begin() override
        {
            PROGRAM_FILED::begin();
            GLCall(glGetIntegerv(GL_CULL_FACE_MODE, &_oldCullFaceMode));
            GLCall(glGetIntegerv(GL_DEPTH_FUNC, &_oldDepthFuncMode));
            GLCall(glCullFace(GL_FRONT));
            GLCall(glDepthFunc(GL_LEQUAL));
            GLCall(glEnableVertexAttribArray(_position));
        }

        void    end() override
        {
            GLCall(glCullFace(_oldCullFaceMode));
            GLCall(glDepthFunc(_oldDepthFuncMode));
            GLCall(glDisableVertexAttribArray(_position));
            PROGRAM_FILED::end();
        }

    private:
        GLint   _oldCullFaceMode;
        GLint   _oldDepthFuncMode;
    private:
        void onAfterCreate() override
        {
            _position   =   getAttribLocation("_position");
            _mvp        =   getUniformLocation("_mvp");
            _cubeTexture    =   getUniformLocation("_cubeTexture");
        }
    };

}

#endif //!SGE_GLSL_UTIL_H