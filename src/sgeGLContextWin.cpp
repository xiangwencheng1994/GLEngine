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
#include <map>

#define COLOR_BITS  24
#define DEPTH_BITS  24

namespace sge
{
    static std::map<int, int> msaaFormat;

    static bool MapSupportedMsaaFormat()
    {
        HINSTANCE hInstance = GetModuleHandle(NULL);
        bool ret = false;
        HWND hWnd = NULL;
        HGLRC hRC = NULL;

        do
        {
            WNDCLASSEX wce;
            wce.cbSize = sizeof(WNDCLASSEX);
            wce.style = 0;
            wce.lpfnWndProc = DefWindowProc;
            wce.cbClsExtra = wce.cbWndExtra = 0;
            wce.hInstance = hInstance;
            wce.hIcon = 0;
            wce.hCursor = 0;
            wce.hbrBackground = 0;
            wce.lpszMenuName = 0;
            wce.lpszClassName = "MapSupportedMassFormat";
            wce.hIconSm = 0;
            if (!RegisterClassEx(&wce))
            {
                Log::error("RegisterClassEx for MapSupportedMassFormat failed!");
                break;
            };

            hWnd = CreateWindow("MapSupportedMassFormat", "MassTest", WS_OVERLAPPED,
                2, 2, 2, 2, NULL, NULL, hInstance, NULL);
            if (!hWnd)
            {
                Log::error("CreateWindow for MapSupportedMassFormat failed!");
                break;
            }

            HDC hDC = GetDC(hWnd);

            PIXELFORMATDESCRIPTOR pfd =
            {
                sizeof(PIXELFORMATDESCRIPTOR),
                1,
                PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                PFD_TYPE_RGBA,
                32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
            };
            int format = ChoosePixelFormat(hDC, &pfd);
            if (!format)
            {
                Log::error("ChoosePixelFormat for MapSupportedMassFormat failed, with Error Code %d", ::GetLastError());
                break;
            }

            if (!SetPixelFormat(hDC, format, &pfd))
            {
                Log::error("SetPixelFormat for MapSupportedMassFormat failed, with Error Code %d", ::GetLastError());
                break;
            }

            hRC = wglCreateContext(hDC);
            if (!hRC)
            {
                Log::error("wglCreateContext for MapSupportedMassFormat failed");
                break;
            }

            if (!wglMakeCurrent(hDC, hRC))
            {
                Log::error("wglMakeCurrent for MapSupportedMassFormat failed");
                break;
            }

            GLenum err = glewInit();
            if (err != GLEW_OK)
            {
                Log::error("glewInit for MapSupportedMassFormat failed with Code: %d", err);
                break;
            }
            
            glEnable(GL_MULTISAMPLE);

            int maxMsaa = 0;
            glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxMsaa);
            for (int msaa = maxMsaa; msaa > 0; --msaa)
            {
                int chooseAttribs[] = {
                    WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
                    WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
                    WGL_COLOR_BITS_ARB,         COLOR_BITS,
                    WGL_DEPTH_BITS_ARB,         DEPTH_BITS,
                    WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
                    WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
                    WGL_SAMPLE_BUFFERS_ARB,     GL_TRUE,
                    WGL_SAMPLES_ARB,            msaa,
                    0, 0 };
                
                int pixelFormat = 0;
                UINT numFormats = 1;
                if (wglChoosePixelFormatARB(hDC, chooseAttribs, NULL,
                    1, &pixelFormat, &numFormats))
                {
                    msaaFormat[msaa] = pixelFormat;
                }
                else
                {
                    msaaFormat[msaa] = -1;
                }
            }

            ret = true;
        } while (false);

        if (hRC) wglDeleteContext(hRC);
        if (hWnd) DestroyWindow(hWnd);
        return ret;
    }

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


    int GLContext::GetFormatForMsaa(int msaa)
    {
        if (msaaFormat.size() == 0)
            MapSupportedMsaaFormat();
        while (msaa > 0)
        {
            if (msaaFormat[msaa] > 0)
                return msaaFormat[msaa];
            --msaa;
        }
        return -1;
    }

    GLContext* GLContext::CreateGLContext(HWND hWnd, HDC hDC /*= NULL*/, int format /*= 0*/)
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
        
        if (format <= 0)
        {
            format = ChoosePixelFormat(hDC, &pfd);
        }

        if (format <= 0)
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