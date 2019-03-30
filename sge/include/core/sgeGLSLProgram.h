/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGLSLProgram.h
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

#ifndef SGE_GLSLPROGRAM_H
#define SGE_GLSLPROGRAM_H

#include <core/sgePlatform.h>

namespace sge
{
    typedef GLint   attribute;
    typedef GLint   uniform;
    typedef GLint   uniformBlock;
    
    /**
     * Class GLSLProgram, provided encapsulation of opengl shader compile and program link
     */
    class SGE_API   GLSLProgram
    {
    public:
        /**
         * Constructor
         */
        GLSLProgram()
            : _programId(0)
        {
        }
        
        /**
         * destructor, it will release program
         */
        virtual ~GLSLProgram() { destory(); }

        /**
         * Create this program.
         * @return true if all shander compile success and program link success, otherwise return false
         */
        bool    create();

        /**
         * Destory this program
         */
        void    destory()
        {
            if (_programId)
            {
                GLCall(glDeleteProgram(_programId));
                _programId  =   0;
            }
        }

        /**
         * Begin use this program
         */
        virtual void    begin() { GLCall(glUseProgram(_programId)); }

        /**
         * End this program
         * it will switch to default program (0)
         */
        virtual void    end() { GLCall(glUseProgram(0)); }

        /**
         * Get this program Id
         * @return 0 if it uncreated or created failed.
         */
        GLuint  getProgramId() const { return _programId; }

        /**
         * Check this program is vaild
         */
        bool    isVaild() const { return _programId != 0; }

        /**
         * Get the last error string while create
         */
        String  getLastError() const { return _lastError; }

        /**
         * Get the uniform var in program
         * @param name The uniform name
         * @return -1 if program is disable or it has no such uniform
         */
        uniform getUniformLocation(const char* name) const { GLCall(uniform loc = glGetUniformLocation(_programId, name)); return loc; }

        /**
         * Get the uniform block in program
         * @param name The uniform block name
         * @return -1 if program is disable or it has no such uniform block
         */
        uniformBlock    getUniformBlock(const char * name) const { GLCall(uniformBlock loc = glGetUniformBlockIndex(_programId, name)); return loc; }

        /**
         * Get the uniform block size
         */
        GLint   getUniformBlockSize(uniformBlock loc) const
        {
            GLint   size;
            GLCall(glGetActiveUniformBlockiv(_programId, loc, GL_UNIFORM_BLOCK_DATA_SIZE, &size));
            return  size;
        };

        /**
         * Get the attribute var in program
         * @param name The attribute name
         * @return -1 if program is disable or it has no such attribute
         */
        attribute   getAttribLocation(const char* name) const { GLCall(attribute loc = glGetAttribLocation(_programId, name)); return loc; }
        
    protected:

        /**
         * Get the vertex shader source
         * @return NULL to use opengl default shader
         */
        virtual String  getVertexShaderSrc() const = 0;

        /**
         * Get the tess control shader source
         * @return NULL to use opengl default shader
         */
        virtual String  getTessControlShaderSrc() const { return String(); }
        
        /**
         * Get the tess evaluation shader source
         * @return NULL to use opengl default shader
         */
        virtual String  getTessEvaluationShaderSrc() const { return String(); }
        
        /**
         * Get the geometry shader source
         * @return NULL to use opengl default shader
         */
        virtual String  getGeometryShaderSrc() const { return String(); }
        
        /**
         * Get the fragment shader source
         * @return NULL to use opengl default shader
         */
        virtual String  getFragmentShaderSrc() const = 0;
        
        /**
         * Callback function after program create successed
         */
        virtual void    onAfterCreate() = 0;

        /**
         * Callback function before program link
         */
        virtual void    onBeforeLink() {}

    protected:
        GLint   createShader(GLenum type, const char* src);

    private:
        GLuint      _programId;
        String      _lastError;
        DISABLE_COPY(GLSLProgram)
    };

}

#endif // !SGE_GLSLPROGRAM_H