/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeApplication.cpp
 * date: 2018/12/05
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

#include <core/sgeApplication.h>
#include <core/sgeScene.h>
#include <core/sgeLog.h>
#include <core/sgeContext.h>
#include <core/sgeGLX.h>
#include <core/sgeTimer.h>
#include <core/sgeGUIRenderer.h>
#include <core/sgeTextureManager.h>
#include <core/sgeShaderManager.h>

namespace sge
{
    int Application::applicationCount   =   0;

    static void _nativeErrorCallback(int error, const char* description)
    {
        Log::error("glfw error (%d): %s", error, description);
    }

    void _nativeFrameBufferSizeCallback(GLFWwindow* window, int w, int h)
    {
        Application*    app =   (Application*)glfwGetWindowUserPointer(window);
        app->onFrameBufferSizeEvent(w, h);
    };

    void _nativeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Application*    app =   (Application*)glfwGetWindowUserPointer(window);
        app->onKeyEvent(key, scancode, action, mods);
    }

    void _nativeMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        Application*    app =   (Application*)glfwGetWindowUserPointer(window);
        app->onMouseButtonEvent(button, action, mods);
    }

    void _nativeMouseMoveCallback(GLFWwindow* window, double x, double y)
    {
        Application*    app =   (Application*)glfwGetWindowUserPointer(window);
        app->onMouseMoveEvent(x, y);
    }

    void _nativeMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        Application*    app =   (Application*)glfwGetWindowUserPointer(window);
        app->onMouseScrollEvent(xoffset, yoffset);
    }

    void _nativeCloseCallback(GLFWwindow* window)
    {
        Application*    app =   (Application*)glfwGetWindowUserPointer(window);
        assert(app);
        app->quit();
    }

    Application::Application(int width, int height, int samples, bool resizable)
        : _curScene(NULL)
    {
        _context._app = this;

        if (applicationCount == 0)
        {
            if (GLFW_TRUE != glfwInit())
            {
                Log::error("glfwInit failed");
                return;
            }
            glfwSetErrorCallback(_nativeErrorCallback);
        }

        glfwWindowHint(GLFW_SAMPLES, samples);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // mac os needed.
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif // _DEBUG


        _window =   glfwCreateWindow(width, height, "sge", NULL, NULL);
        if (NULL == _window)
        {
            Log::error("glfwCreateWindow failed");
            return;
        }

        glfwSetWindowUserPointer(_window, this);
        glfwSetKeyCallback(_window, _nativeKeyCallback);
        glfwSetMouseButtonCallback(_window, _nativeMouseButtonCallback);
        glfwSetScrollCallback(_window, _nativeMouseScrollCallback);
        glfwSetCursorPosCallback(_window, _nativeMouseMoveCallback);
        glfwSetFramebufferSizeCallback(_window, _nativeFrameBufferSizeCallback);
        glfwSetWindowCloseCallback(_window, _nativeCloseCallback);

        glfwMakeContextCurrent(_window);

        if (applicationCount == 0)
        {
            // glewExperimental    =   GL_TRUE;
            GLenum ret = glewInit();
            if (GLEW_OK != ret)
            {
                Log::error("glewInit failed, %s", glewGetErrorString(ret));
                return;
            }
            glEnable(GL_MULTISAMPLE);
            Log::info("GPUInfo:\n%s", getGPUInfo().c_str());
        }
        ++applicationCount;

        _context._guiRenderer   =   new GUIRenderer();
        _context._textureManager    =   new TextureManager();
        _context._shaderManager =   new ShaderManager();

        // load base resources
        if (0 > _context._guiRenderer->loadFont("default", "fonts/default.ttf"))
            Log::error("GUIRenderer load fonts/default.ttf failed");
        
    }


    Application::~Application()
    {
        if (_curScene)
        {
            loadScene(NULL);
            assert(_curScene == NULL);
        }
        _context._app = NULL;
        if (_context._textureManager)
        {
            delete _context._textureManager;
            _context._textureManager    =   NULL;
        }
        if (_context._guiRenderer)
        {
            delete  _context._guiRenderer;
            _context._guiRenderer =   NULL;
        }
        if (_context._shaderManager)
        {
            delete _context._shaderManager;
            _context._shaderManager =   NULL;
        }
        if (_window)
        {
            glfwDestroyWindow(_window);
            _window =   NULL;
        }
        --applicationCount;
        if (applicationCount <= 0)
        {
            glfwTerminate();
        }
    }

    Application* Application::getCurrent()
    {
        GLFWwindow* window  =   glfwGetCurrentContext();
        if (window)
        {
            return  (Application*)glfwGetWindowUserPointer(window);
        }
        return  NULL;
    }

    void Application::run()
    {
        assert(_window);
        glfwShowWindow(_window);
        
        Timer timer;
        timer.elapsed();

        while (!glfwWindowShouldClose(_window))
        {
            _context._frameTime =   timer.elapsed();

            glfwMakeContextCurrent(_window);
            if (_curScene)
            {
                _curScene->onRender(_context);
                glfwSwapBuffers(_window);
            }

            glfwPollEvents();
        }
    }


    void Application::loadScene(Scene* scene)
    {
        Scene*  oldScene    =   _curScene;
        if (scene)
        {
            scene->onLoad(_context);
        }
        _curScene   =   scene;

        if (oldScene)
        {
            oldScene->onUnLoad(_context);
            //TODO: check all oldScene resouces released.
            oldScene->release();
        }
    }

    void Application::quit()
    {
        if (! onCloseEvent())
        {
            glfwSetWindowShouldClose(_window, GLFW_TRUE);
        }
    }

    inline bool Application::onCloseEvent()
    {
        // unload the scene
        loadScene(NULL);
        return  false;
    }

    inline void Application::onFrameBufferSizeEvent(int w, int h)
    {
        if (h == 0)
            h = 1;
        
        _context._frameBufferWidth  =   w;
        _context._frameBufferHeight =   h;
        if (_curScene)
        {
            _curScene->onResizeEvent(w, h);
        }
    }

    inline void Application::onKeyEvent(int key, int scancode, int action, int mods)
    {
        if (_curScene)
        {
            _curScene->onKeyEvent(key, scancode, action, mods);
        }
    }

    inline void Application::onMouseButtonEvent(int button, int action, int mods)
    {
        if (_curScene)
        {
            _curScene->onMouseButtonEvent(button, action, mods);
        }
    }

    inline void Application::onMouseMoveEvent(double x, double y)
    {
        if (_curScene)
        {
            _curScene->onMouseMoveEvent(x, y);
        }
    }

    inline void Application::onMouseScrollEvent(double dx, double dy)
    {
        if (_curScene)
        {
            _curScene->onMouseMoveEvent(dx, dy);
        }
    }
}
