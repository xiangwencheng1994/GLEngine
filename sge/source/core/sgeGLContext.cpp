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

#include <core/sgeGLContext.h>
#include <core/sgeLog.h>

#ifdef OPENGLES

#include <EGL/eglext.h>

namespace sge
{

    GLContext::GLContext()
    {
        _config = 0;
        _surface = EGL_NO_SURFACE;
        _context = EGL_NO_CONTEXT;
        _display = EGL_NO_DISPLAY;
    }

    GLContext::~GLContext()
    {
        Shutdown();
    }

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

    bool GLContext::Init(EGLNativeWindowType hWnd, EGLNativeDisplayType hDC)
    {
        ASSERT(EGL_NO_CONTEXT == _context && "Not init gl context again");

        EGLDisplay  display = eglGetDisplay(hDC);
        if (display == EGL_NO_DISPLAY)
        {
            Log::error("eglGetDisplay ");
            return false;
        }

        EGLint  major, minor;
        if (EGL_FALSE == eglInitialize(display, &major, &minor))
        {
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
            return false;
        }
        ASSERT(numConfigs && "EGL没有找到支持的配置");

#ifdef ANDROID
        EGLint  format(0);
        if (EGL_FALSE == eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format))
        {
            return false;
        }
        ANativeWindow_setBuffersGeometry(hWnd, 0, 0, format);
#endif


        EGLSurface  surface = eglCreateWindowSurface(display, config, hWnd, NULL);
        if (EGL_NO_SURFACE == surface)
        {
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
            eglDestroySurface(display, surface);
            eglTerminate(display);
            return  false;
        }

        if (EGL_FALSE == eglMakeCurrent(display, surface, surface, context))
        {
            eglDestroySurface(display, surface);
            eglTerminate(display);
            return  false;
        }

        _context = context;
        _display = display;
        _config = config;
        _surface = surface;
        //eglQuerySurface(display, surface, EGL_WIDTH, &_width);
        //eglQuerySurface(display, surface, EGL_HEIGHT, &_height);

        return  true;
    }

    inline void GLContext::MakeCurrent()
    {
        EGLBoolean  ret = eglMakeCurrent(_display, _surface, _surface, _context);
        ASSERT(EGL_TRUE == ret);
    }

    void GLContext::Shutdown()
    {
        if (EGL_NO_DISPLAY != _display)
        {
            eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            if (EGL_NO_CONTEXT != _context)
            {
                eglDestroyContext(_display, _context);
                _context = EGL_NO_CONTEXT;
            }
            if (EGL_NO_SURFACE != _surface)
            {
                eglDestroySurface(_display, _surface);
                _surface = EGL_NO_SURFACE;
            }
            eglTerminate(_display);
            _display = EGL_NO_DISPLAY;
        }
    }

    inline void GLContext::SwapBuffer()
    {
        EGLBoolean  ret = eglSwapBuffers(_display, _surface);
        ASSERT(EGL_TRUE == ret);
    }

}


#else // Desktop OpenGL

#if SGE_TARGET_PLATFORM == SGE_PLATFORM_WIN32

#include <map>
#include <GL/wglew.h>

#define COLOR_BITS  24
#define DEPTH_BITS  24

namespace sge
{
    static bool MapSupportedMsaaFormat(std::map<int, int>& msaaFormat)
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

    GLContext::GLContext()
        : _hWnd(0)
        , _hDC(0)
        , _hRC(0)
    {
    }

    int GLContext::GetFormatForMsaa(int msaa)
    {
        static std::map<int, int> msaaFormat;

        if (msaaFormat.size() == 0)
            MapSupportedMsaaFormat(msaaFormat);
        while (msaa > 0)
        {
            if (msaaFormat[msaa] > 0)
                return msaaFormat[msaa];
            --msaa;
        }
        return -1;
    }

    bool GLContext::Init(HWND hWnd, HDC hDC /*= NULL*/, int format /*= 0*/)
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

        _hWnd = hWnd;
        _hDC = hDC;
        _hRC = hRC;
        MakeCurrent();
        GLenum ret = glewInit();
        if (GLEW_OK != ret)
        {
            Log::error("glewInit failed with code(%d) while CreateGLContext.", ret);
            return false;
        }
        return true;
    }

    GLContext::~GLContext()
    {
        if (_hRC != NULL)
        {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(_hRC);
            _hRC = NULL;
            _hWnd = NULL;
            _hDC = NULL;
        }
    }

    inline void GLContext::MakeCurrent()
    {
        wglMakeCurrent(_hDC, _hRC);
    }

    inline void GLContext::SwapBuffer()
    {
        ::SwapBuffers(_hDC);
    }

    inline void GLContext::EnableVSYNC(GLboolean enable)
    {
        wglSwapIntervalEXT(enable);
    }

}

#endif // SGE_TARGET_PLATFORM SGE_PLATFORM_WIN32

//TODO: other platform 

#endif