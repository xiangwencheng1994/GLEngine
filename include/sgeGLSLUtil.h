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
#include <sgeGLX.h>
#include <sgeMath.h>

#include <sgeFileReader.h>

namespace sge
{
    /**
     * PROGRAM from ShaderPath
     * read ShaderPath.vert for vertex shader source if exists
     * read ShaderPath.tesc for tess control shader source if exists
     * read ShaderPath.tese for tess evaluation shader source if exists
     * read ShaderPath.geom for geometry shader source if exists
     * read ShaderPath.geom for fragment shader source if exists
     */
    class PROGRAM_FILED : public GLSLProgram
    {
    public:
        /**
         * The ShaderPath
         */
        virtual const char* ShaderPath() const   =   0;

    private:
        std::string TryGetShader(const char* type) const
        {
            bool hasFile = false;
            char    path[MAX_PATH];
            sprintf(path, "%s.%s", ShaderPath(), type);
            FileReader file(path, &hasFile);
            return hasFile ? file.ReadAll() : std::string();
        }
        std::string GetVertexShaderSrc() const override { return TryGetShader("vert"); }
        std::string GetTessControlShaderSrc() const override { return TryGetShader("tesc"); }
        std::string GetTessEvaluationShaderSrc() const override { return TryGetShader("tese"); }
        std::string GetGeometryShaderSrc() const override { return TryGetShader("geom"); }
        std::string GetFragmentShaderSrc() const override { return TryGetShader("frag"); }
    };

    /**
     * The base P3 C4 program
     */
    class PROGRAM_P3C4 : public PROGRAM_FILED
    {
    public:
        const char* ShaderPath() const override { return "shader/P3C4"; }

    public:
        uniform     _mvp;
        attribute   _position;
        attribute   _color;
        
    private:
        void OnAfterCreate() override
        {
            _mvp        =   GetUniformLocation("_mvp");
            _position   =   GetAttribLocation("_position");
            _color      =   GetAttribLocation("_color");
        }
    };

    /**
     * The cube texture sky box demo program
     */
    class PROGRAM_SKYBOX : public PROGRAM_FILED
    {
    public:
        const char* ShaderPath() const override { return "shader/Skybox"; }

    public:
        uniform     _mvp;
        attribute   _position;

        uniform     _cubeTexture;

        void Begin() const override
        {
            __super::Begin();
            glGetIntegerv(GL_CULL_FACE_MODE, (GLint*)&OldCullFaceMode);
            glGetIntegerv(GL_DEPTH_FUNC, (GLint*)&OldDepthFuncMode);
            glCullFace(GL_FRONT);
            glDepthFunc(GL_LEQUAL);
            glEnableVertexAttribArray(_position);
        }

        void End() const override
        {
            glCullFace(OldCullFaceMode);
            glDepthFunc(OldDepthFuncMode);
            glDisableVertexAttribArray(_position);
            __super::End();
        }

    private:
        GLint OldCullFaceMode;
        GLint OldDepthFuncMode;
    private:
        void OnAfterCreate() override
        {
            _mvp        =   GetUniformLocation("_mvp");
            _position   =   GetAttribLocation("_position");
            _cubeTexture    =   GetUniformLocation("_cubeTexture");
        }
    };

    /**
     * The base model shader
     */
    class PROGRAM_MODEL : public PROGRAM_FILED
    {
    public:
        const char* ShaderPath() const override { return "shader/Model"; }
        
    public:
        // mesh attribute
        attribute       _position;
        attribute       _normal;

        // instance data
        attribute       _local;
        attribute       _matIndex;

        // model-view-projection matrix
        uniform         MVP;
        // the camera pos in world space
        uniform         CameraPos;
        // the normalized light direction
        uniform         LightDir;
        // the ambient intensity
        uniform         AmbientIntensity;
        // the diffuse intensity
        uniform         DiffuseIntensity;
        // the specular intensity
        uniform         SpecularIntensity;

        UniformBlock    Materials;
    private:
        void OnAfterCreate() override
        {
            //Get uniform and attribute.

            // mesh attribute
            _position   =   GetAttribLocation("_position");
            _normal     =   GetAttribLocation("_normal");
            // material attribute
            _local      =   GetAttribLocation("_local");
            _matIndex   =   GetAttribLocation("_matIndex");

            // model-view-projection matrix
            MVP         =   GetUniformLocation("MVP");
            // the camera pos in world space
            CameraPos   =   GetUniformLocation("CameraPos");
            // the normalized light direction
            LightDir    =   GetUniformLocation("LightDir");
            // the ambient intensity
            AmbientIntensity    =   GetUniformLocation("AmbientIntensity");
            // the diffuse intensity
            DiffuseIntensity    =   GetUniformLocation("DiffuseIntensity");
            // the specular intensity
            SpecularIntensity   =   GetUniformLocation("SpecularIntensity");

            Materials = GetUniformBlock("Materials");
        }
    };


    class PROGRAM_FEEDBACK_CALC_INST_CMD : public PROGRAM_FILED
    {
    public:
        // The mesh id of this instance
        attribute   _meshId;        
        // The flag of this instance
        attribute   _flag;
        // The local matrix of this instance
        attribute   _local;

        // The mvp matrix for world
        uniform     _mvp;

        // The meshes desc
        UniformBlock Meshes;
    public:
        const char* ShaderPath() const override { return "shader/InstCmd"; }

        void Begin() const override
        {
            __super::Begin();
            GLCall(glBeginTransformFeedback(GL_POINTS));
            GLCall(glEnable(GL_RASTERIZER_DISCARD));
        }

        void End() const override
        {
            GLCall(glEndTransformFeedback());
            GLCall(glDisable(GL_RASTERIZER_DISCARD));
            __super::End();
        }
    private:
        void OnBeforeLink() override
        {
            const GLchar* feedbackVaryings[] = {
                "vertCount",
                "primCount",
                "firstIndex",
                "baseVertex",
                "baseInstance",
            };
            GLCall(glTransformFeedbackVaryings(ProgramId(), 5,
                feedbackVaryings, GL_INTERLEAVED_ATTRIBS));
        }

        void OnAfterCreate() override
        {
            _meshId = GetAttribLocation("_meshId");
            _flag = GetAttribLocation("_flag");
            _local = GetAttribLocation("_local");
            
            _mvp = GetUniformLocation("_mvp");
            
            Meshes = GetUniformBlock("Meshes");
        }
    };

}

#endif //!SGE_GLSL_UTIL_H