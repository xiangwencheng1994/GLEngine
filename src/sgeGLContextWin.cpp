/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGLContextWin.cpp
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



#ifdef _WIN32
#include <sgeGLContext.h>
#include <sgeLog.h>

#include <assert.h>
#include <glew/wglew.h>


namespace sge
{
    class GLContextPrivate
    {
        HWND        hWnd;
        HDC	        hDC;
        HGLRC       hRC;

        GLContextPrivate() : hWnd(0), hDC(0), hRC(0)
        {
        }

        friend class GLContext;
    };

    GLContext::GLContext()
        : d(new GLContextPrivate())
    {
    }

    GLContext* GLContext::CreateGLContext(HWND hWnd, HDC hDC /*= NULL*/, unsigned format /*= 0*/)
    {
        HGLRC hRC = NULL;
        if (!hDC) hDC = ::GetDC(hWnd);
        if (!hDC)
        {
            Log::error("Get DC failed, with Error Code %d", ::GetLastError());
            return NULL;
        }

        PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
        };

        if (!format) format = ChoosePixelFormat(hDC, &pfd);
        if (!format)
        {
            Log::error("ChoosePixelFormat failed, with Error Code %d", ::GetLastError());
            return NULL;
        }

        if (!SetPixelFormat(hDC, format, &pfd))
        {
            Log::error("SetPixelFormat failed, with Error Code %d", ::GetLastError());
            return NULL;
        }

        hRC = wglCreateContext(hDC);
        if (!hRC)
        {
            Log::error("wglCreateContext failed");
            return NULL;
        }

        GLContext* ctx = new GLContext();
        ctx->d->hWnd = hWnd;
        ctx->d->hDC = hDC;
        ctx->d->hRC = hRC;
        if (ctx->MakeCurrent()) glewInit();
        else Log::error("MakeCurrent failed while CreateGLContext.");
        return ctx;
    }

    HWND GLContext::GetHWND()
    {
        return d->hWnd;
    }

    HDC GLContext::GetHDC()
    {
        return d->hDC;
    }

    HGLRC GLContext::GetHRC()
    {
        return d->hRC;
    }

    GLContext::~GLContext()
    {
        if (d)
        {
            if (d->hRC != NULL)
            {
                wglMakeCurrent(NULL, NULL);
                wglDeleteContext(d->hRC);
                d->hRC = NULL;
            }

            if (d->hDC != NULL)
            {
                ReleaseDC(d->hWnd, d->hDC);
                d->hDC = NULL;
            }
            delete d;
            d = NULL;
        }
        
    }

    BOOL GLContext::MakeCurrent()
    {
        return wglMakeCurrent(d->hDC, d->hRC);
    }

    

    void GLContext::SwapBuffers()
    {
        ::SwapBuffers(d->hDC);
    }

    void GLContext::EnableVSYNC(GLboolean enable)
    {
        wglSwapIntervalEXT(enable);
    }

}

#else

//TODO: EGL ? 
//TODO: GLES ?
//TODO: LINUX GL

#endif