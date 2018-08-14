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

#ifndef SGE_GLSLPROGRAM_H
#define SGE_GLSLPROGRAM_H

#include <sge.h>
#include <string>

#include <glew/glew.h>

namespace sge
{
    class GLSLProgramPrivate;

    typedef GLint attribute;
    typedef GLint uniform;
    
    /**
     * Class GLSLProgram, provided encapsulation of opengl shader compile and program link
     */
    class SGE_API GLSLProgram
    {
    public:
        /**
         * Constructor
         */
        GLSLProgram();
        
        /**
         * destructor, it will release program
         */
        virtual ~GLSLProgram();

        /**
         * Create this program.
         * @return true if all shander compile success and program link success, otherwise return false
         */
        bool create();

        /**
         * Destory this program
         */
        void destory();

        /**
         * Begin use this program
         */
        virtual void begin() const;

        /**
         * End this program
         * it will switch to default program (0)
         */
        virtual void end() const;

        /**
         * Get this program Id
         * @return 0 if it uncreated or created failed.
         */
        GLuint getProgramId() const;

        /**
         * Get the uniform var in program
         * @param name The uniform name
         * @return -1 if program is disable or it has no such uniform
         */
        uniform getUniformLocation(const char* name) const;

        /**
         * Get the attribute var in program
         * @param name The attribute name
         * @return -1 if program is disable or it has no such attribute
         */
        attribute getAttribLocation(const char* name) const;
        
    protected:

        /**
         * Get the vertex shader source
         * @return NULL to use opengl default shader
         */
        virtual std::string getVertexShaderSrc() const = 0;

        /**
         * Get the tess control shader source
         * @return NULL to use opengl default shader
         */
        virtual std::string getTessControlShaderSrc() const { return std::string(); }
        
        /**
         * Get the tess evaluation shader source
         * @return NULL to use opengl default shader
         */
        virtual std::string getTessEvaluationShaderSrc() const { return std::string(); }
        
        /**
         * Get the geometry shader source
         * @return NULL to use opengl default shader
         */
        virtual std::string getGeometryShaderSrc() const { return std::string(); }
        
        /**
         * Get the fragment shader source
         * @return NULL to use opengl default shader
         */
        virtual std::string getFragmentShaderSrc() const = 0;
        
        /**
         * Callback function after program create successed
         */
        virtual void onCreateAfter() = 0;

    private:
        GLSLProgramPrivate* d;
        DISABLE_COPY(GLSLProgram)
    };

}

#endif // !SGE_GLSLPROGRAM_H