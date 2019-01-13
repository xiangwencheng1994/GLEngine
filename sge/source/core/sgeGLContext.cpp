/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGLContext.cpp
 * date: 2018/11/13
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

#include <core/sgeGLContext.h>
#include <core/sgeLog.h>

#ifdef OPENGLES
#include <EGL/eglext.h>
#else // Desktop OpenGL
#include <map>
#include <GL/wglew.h>
#define COLOR_BITS  24
#define DEPTH_BITS  24
#endif

namespace sge
{

#ifdef OPENGLES
    static EGLint eglGetSupportedRendererType(EGLDisplay display)
    {
#if defined(EGL_KHR_create_context)
        const char* extensions = eglQueryString(display, EGL_EXTENSIONS);
        if (extensions && strstr(extensions, "EGL_KHR_create_context"))
        {
            Log::info("Use EGL_OPENGL_ES3_BIT_KHR");
            return EGL_OPENGL_ES3_BIT_KHR;
        }
        else
        {
            Log::info("Use EGL_OPENGL_ES2_BIT");
        }
#endif
        return EGL_OPENGL_ES2_BIT;
    }
#endif

#ifndef OPENGLES

    static bool mapSupportedMsaaFormat(std::map<int, int>& msaaFormat)
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
    
    int GLContext::getFormatForMsaa(int msaa)
    {
        static std::map<int, int> msaaFormat;

        if (msaaFormat.size() == 0)
            mapSupportedMsaaFormat(msaaFormat);
        while (msaa > 0)
        {
            if (msaaFormat[msaa] > 0)
                return msaaFormat[msaa];
            --msaa;
        }
        return -1;
    }

#endif

    class GLContextPrivate
    {
    public:
        WindowHandle    mHWnd;
        DisplayHandle   mHDC;
#ifdef OPENGLES
        EGLConfig       mConfig;
        EGLSurface      mSurface;
        EGLContext      mContext;
        EGLDisplay      mDisplay;
#else
        HGLRC           mHRC;
#endif
        GLContextPrivate()
            : mHWnd(NULL)
            , mHDC(NULL)
#ifdef OPENGLES
            , mConfig(0)
            , mSurface(EGL_NO_SURFACE)
            , mContext(EGL_NO_CONTEXT)
            , mDisplay(EGL_NO_DISPLAY)
#else
            , mHRC(NULL)
#endif
        {}

        ~GLContextPrivate()
        {
            ASSERT(mHWnd == NULL);
            ASSERT(mHDC == NULL);
#ifdef OPENGLES
            ASSERT(mConfig == 0);
            ASSERT(mSurface == EGL_NO_SURFACE);
            ASSERT(mContext == EGL_NO_CONTEXT);
            ASSERT(mDisplay == EGL_NO_DISPLAY);
#else
            ASSERT(mHRC == NULL);
#endif
        }
    };

    GLContext::GLContext()
        : d(new GLContextPrivate())
    {
    }

    bool GLContext::initialize(WindowHandle hWnd, DisplayHandle hDC, int format)
    {
#ifdef OPENGLES
        ASSERT(EGL_NO_CONTEXT == d->mContext && "Not init gl context again");

        EGLDisplay  display = eglGetDisplay(hDC);
        if (display == EGL_NO_DISPLAY)
        {
            Log::error("eglGetDisplay = EGL_NO_DISPLAY");
            return false;
        }

        EGLint  major, minor;
        if (EGL_FALSE == eglInitialize(display, &major, &minor))
        {
            Log::error("eglInitialize = EGL_FALSE");
            return false;
        }

        const EGLint attribs[] =
        {
            EGL_RENDERABLE_TYPE, eglGetSupportedRendererType(display),
            EGL_RED_SIZE, 5,
            EGL_GREEN_SIZE, 6,
            EGL_BLUE_SIZE, 5,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 8,
            EGL_STENCIL_SIZE, 8,
            EGL_NONE
        };

        EGLint	numConfigs(0);
        EGLConfig   config;
        if (EGL_FALSE == eglChooseConfig(display, attribs, &config, 1, &numConfigs))
        {
            Log::error("eglChooseConfig = EGL_FALSE");
            return false;
        }
        ASSERT(numConfigs && "EGL Can not find any config while eglChooseConfig");

#ifdef ANDROID
        EGLint  format(0);
        if (EGL_FALSE == eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format))
        {
            Log::error("eglGetConfigAttrib = EGL_FALSE");
            return false;
        }
        ANativeWindow_setBuffersGeometry(hWnd, 0, 0, format);
#endif

        EGLSurface  surface = eglCreateWindowSurface(display, config, hWnd, NULL);
        if (EGL_NO_SURFACE == surface)
        {
            Log::error("eglCreateWindowSurface = EGL_NO_SURFACE");
            return  false;
        }

        EGLint  attr[] = { EGL_CONTEXT_CLIENT_VERSION,
            attribs[1] == EGL_OPENGL_ES3_BIT_KHR ? 3 : 2
            , EGL_NONE };
        EGLContext  context = eglCreateContext(display, config, EGL_NO_CONTEXT, attr);
        if (EGL_NO_CONTEXT == context)
        {
            EGLint ret = eglGetError();
            ASSERT("eglCreateContext:eglGetError" && ret);
            Log::error("eglCreateContext = EGL_NO_CONTEXT");
            eglDestroySurface(display, surface);
            eglTerminate(display);
            return  false;
        }

        if (EGL_FALSE == eglMakeCurrent(display, surface, surface, context))
        {
            Log::error("eglMakeCurrent = EGL_FALSE");
            eglDestroySurface(display, surface);
            eglTerminate(display);
            return  false;
        }
        
        d->mConfig = config;
        d->mContext = context;
        d->mDisplay = display;
        d->mSurface = surface;
        //eglQuerySurface(display, surface, EGL_WIDTH, &_width);
        //eglQuerySurface(display, surface, EGL_HEIGHT, &_height);
#else
        HGLRC hRC = NULL;
        if (!hDC && !(hDC = GetDC(hWnd)))
        {
            Log::error("Get DC failed, with Error Code %d", GetLastError());
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

        if (format <= 0 && (format = ChoosePixelFormat(hDC, &pfd)) <= 0)
        {
            Log::error("ChoosePixelFormat failed, with Error Code %d", GetLastError());
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

        d->mHWnd = hWnd;
        d->mHDC = hDC;
        d->mHRC = hRC;
        makeCurrent();
        GLenum ret = glewInit();
        if (GLEW_OK != ret)
        {
            Log::error("glewInit failed with code(%d) while CreateGLContext.", ret);
            return false;
        }
#endif
        return true;
    }

    GLContext::~GLContext()
    {
        shutdown();
        delete d;
    }

    void GLContext::shutdown()
    {
#ifdef OPENGLES
        if (EGL_NO_DISPLAY != d->mDisplay)
        {
            eglMakeCurrent(d->mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            if (EGL_NO_CONTEXT != d->mContext)
            {
                eglDestroyContext(d->mDisplay, d->mContext);
                d->mContext = EGL_NO_CONTEXT;
            }
            if (EGL_NO_SURFACE != d->mSurface)
            {
                eglDestroySurface(d->mDisplay, d->mSurface);
                d->mSurface = EGL_NO_SURFACE;
            }
            d->mConfig = 0;
            eglTerminate(d->mDisplay);
            d->mDisplay = EGL_NO_DISPLAY;
        }
#else
        if (d->mHRC != NULL)
        {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(d->mHRC);
            d->mHRC = NULL;
            d->mHWnd = NULL;
            d->mHDC = NULL;
        }
#endif
    }

    inline void GLContext::makeCurrent()
    {
#ifdef OPENGLES
        EGLBoolean  ret = eglMakeCurrent(d->mDisplay, d->mSurface, d->mSurface, d->mContext);
        ASSERT(EGL_TRUE == ret);
#else
        wglMakeCurrent(d->mHDC, d->mHRC);
#endif
    }

    inline void GLContext::swapBuffer()
    {
#ifdef OPENGLES
        EGLBoolean  ret = eglSwapBuffers(d->mDisplay, d->mSurface);
        ASSERT(EGL_TRUE == ret);
#else
        SwapBuffers(d->mHDC);
#endif
    }

    inline void GLContext::setEnableVSYNC(GLboolean enable)
    {
#ifdef OPENGLES
        eglSwapInterval(d->mDisplay, enable ? EGL_MAX_SWAP_INTERVAL : 0);
#else
        wglSwapIntervalEXT(enable);
#endif
    }

}