/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGLContext.h
 * date: 2018/11/13
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

#ifndef CELL_GLCONTEXT_H
#define CELL_GLCONTEXT_H

#include <core/sgePlatform.h>

#ifdef OPENGLES
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#else // Desktop OpenGL
#include <gl/glew.h>
#endif

namespace sge
{

    /**
     * Manager OpenGL Context
     */
    class SGE_API GLContext
    {
    public:
        /**
         * Constructor, define a empty context
         */
        GLContext();

        /**
         * Destructor
         */
        ~GLContext();

#ifdef OPENGLES
        /**
         * Init OpenGLES context
         * @param hWnd  target window
         * @param hDC   target display
         * @return true if init success
         */
        bool Init(EGLNativeWindowType hWnd, EGLNativeDisplayType hDC);

        // getters
        EGLConfig       GetConfig() { return _config; }
        EGLSurface      GetSurface() { return _surface; }
        EGLContext      GetContext() { return _context; }
        EGLDisplay      GetDisplay() { return _display; }
#else
    #ifdef _WIN32
        /**
         * Get the pixel format by msaa
         */
        static int  GetFormatForMsaa(int msaa);

        /**
         *  Init OpenGL context
         * @param hWnd  target window
         * @param hDC   target draw context
         * @param format format
         * @return true if init success
         */
        bool Init(HWND hWnd, HDC hDC, int format);
                
        HDC             GetDC() { return _hDC; }
        HWND            GetWnd() { return _hWnd; }
    #endif

        HGLRC           GetHGLRC() { return _hRC; }
#endif
        
        /**
         * Shutdown this context
         */
        void Shutdown();

        /**
         * Set this context for current thread
         */
        void MakeCurrent();

        /**
         * Swap the back buffer and front buffer
         */
        void SwapBuffer();

        /**
         * Enable or disable vertical synchronization
         * @param enable, the default is enable, limit 60 fps in most
         */
        void EnableVSYNC(GLboolean enable);

    private:

#ifdef OPENGLES

        EGLConfig       _config;
        EGLSurface      _surface;
        EGLContext      _context;
        EGLDisplay      _display;
#else

    #if WIN32
        HDC             _hDC;
        HWND            _hWnd;
    #else
        //TODO: linux native type
    #endif

        HGLRC           _hRC;
#endif
        DISABLE_COPY(GLContext)
    };

}


#endif // !CELL_GLCONTEXT_H
