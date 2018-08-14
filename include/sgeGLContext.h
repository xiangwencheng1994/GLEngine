/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGLContext.h
 * date: 2017/12/04
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

#ifndef SGE_GLCONTEXT_H
#define SGE_GLCONTEXT_H

#include <sge.h>
#include <glew/glew.h>

namespace sge {

    class GLContextPrivate;

    /**
     * Class GLContext for save opengl context
     */
    class SGE_API GLContext
    {
    public:

#ifdef _WIN32
        /**
         * Get the pixel format by msaa
         */
        static int  GetFormatForMsaa(int msaa);

        /**
         * Create GLContext from windows handle
         */
        static GLContext* CreateGLContext(HWND hWnd, HDC hDC = NULL, int format = 0);

        /**
         * Get bind window handle
         */
        HWND    GetHWND();

        /**
         * Get bind device context
         */
        HDC     GetHDC();

        /**
         * Get bind gl render context
         */
        HGLRC   GetHRC();
#endif

        /**
         * Destructor
         */
        ~GLContext();

        /**
         * Set this context to current thread
         */
        BOOL MakeCurrent();

        /**
         * Swap the back buffer and front buffer
         */
        void SwapBuffers();

        /**
         * Enable or disable vertical synchronization
         * @param enable£¬the default is enable, limit 60 fps in most
         */
        void EnableVSYNC(GLboolean enable);

    private:
        GLContext();
        GLContextPrivate* d;
        DISABLE_COPY(GLContext)
    };

} // !namespace

#endif