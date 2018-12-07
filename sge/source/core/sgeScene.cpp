/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeScene.cpp
 * date: 2018/12/08
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

#include <core/sgeApplication.h>
#include <core/sgeScene.h>
#include <ui/sgeView.h>

namespace sge
{

    Scene::Scene()
        : _gui(NULL)
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::OnLoad(Application * app)
    {
        PlatformNative* platform = app->Platform();
        platform->_OnLeftButtonDownEvent.Bind<Scene>(this, &Scene::OnLeftButtonDownEvent);
        platform->_OnLeftButtonUpEvent.Bind<Scene>(this, &Scene::OnLeftButtonUpEvent);
        platform->_OnLeftButtonClickEvent.Bind<Scene>(this, &Scene::OnLeftButtonClickEvent);
        platform->_OnRightButtonDownEvent.Bind<Scene>(this, &Scene::OnRightButtonDownEvent);
        platform->_OnRightButtonUpEvent.Bind<Scene>(this, &Scene::OnRightButtonUpEvent);
        platform->_OnRightButtonClickEvent.Bind<Scene>(this, &Scene::OnRightButtonClickEvent);
        platform->_OnMiddleButtonDownEvent.Bind<Scene>(this, &Scene::OnMiddleButtonDownEvent);
        platform->_OnMiddleButtonUpEvent.Bind<Scene>(this, &Scene::OnMiddleButtonUpEvent);
        platform->_OnMiddleButtonClickEvent.Bind<Scene>(this, &Scene::OnMiddleButtonClickEvent);
        platform->_OnMouseMoveEvent.Bind<Scene>(this, &Scene::OnMouseMoveEvent);
        platform->_OnMouseWheelEvent.Bind<Scene>(this, &Scene::OnMouseWheelEvent);
        platform->_OnKeyDownEvent.Bind<Scene>(this, &Scene::OnKeyDownEvent);
        platform->_OnKeyUpEvent.Bind<Scene>(this, &Scene::OnKeyUpEvent);
        platform->_OnResizeEvent.Bind<Scene>(this, &Scene::OnResizeEvent);
        platform->_OnCloseEvent.Bind<Scene>(this, &Scene::OnCloseEvent);
    }

    void Scene::OnUnLoad(Application * app)
    {
        PlatformNative* platform = app->Platform();
        platform->_OnLeftButtonDownEvent.Bind(NULL);
        platform->_OnLeftButtonUpEvent.Bind(NULL);
        platform->_OnLeftButtonClickEvent.Bind(NULL);
        platform->_OnRightButtonDownEvent.Bind(NULL);
        platform->_OnRightButtonUpEvent.Bind(NULL);
        platform->_OnRightButtonClickEvent.Bind(NULL);
        platform->_OnMiddleButtonDownEvent.Bind(NULL);
        platform->_OnMiddleButtonUpEvent.Bind(NULL);
        platform->_OnMiddleButtonClickEvent.Bind(NULL);
        platform->_OnMouseMoveEvent.Bind(NULL);
        platform->_OnMouseWheelEvent.Bind(NULL);
        platform->_OnKeyDownEvent.Bind(NULL);
        platform->_OnKeyUpEvent.Bind(NULL);
        platform->_OnResizeEvent.Bind(NULL);
        platform->_OnCloseEvent.Bind(NULL);
    }

    void Scene::OnRender(Application * app)
    {
        if (_gui)
        {
            _gui->OnRender();
        }
    }

    bool Scene::OnLeftButtonDownEvent(const MouseDownEvent & event)
    {
        if (_gui && _gui->OnLeftButtonDownEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnLeftButtonUpEvent(const MouseUpEvent & event)
    {
        if (_gui && _gui->OnLeftButtonUpEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnLeftButtonClickEvent(const MouseClickEvent & event)
    {
        if (_gui && _gui->OnLeftButtonClickEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnRightButtonDownEvent(const MouseDownEvent & event)
    {
        if (_gui && _gui->OnRightButtonDownEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnRightButtonUpEvent(const MouseUpEvent & event)
    {
        if (_gui && _gui->OnRightButtonUpEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnRightButtonClickEvent(const MouseClickEvent & event)
    {
        if (_gui && _gui->OnRightButtonClickEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnMiddleButtonDownEvent(const MouseDownEvent & event)
    {
        if (_gui && _gui->OnMiddleButtonDownEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnMiddleButtonUpEvent(const MouseUpEvent & event)
    {
        if (_gui && _gui->OnMiddleButtonUpEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnMiddleButtonClickEvent(const MouseClickEvent & event)
    {
        if (_gui && _gui->OnMiddleButtonClickEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnMouseMoveEvent(const MouseMoveEvent & event)
    {
        if (_gui && _gui->OnMouseMoveEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnMouseWheelEvent(const MouseWheelEvent & event)
    {
        if (_gui && _gui->OnMouseWheelEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnKeyDownEvent(const KeyDownEvent & event)
    {
        if (_gui && _gui->OnKeyDownEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnKeyUpEvent(const KeyUpEvent & event)
    {
        if (_gui && _gui->OnKeyUpEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::OnResizeEvent(const ResizeEvent & event)
    {
        if (_gui)
        {
            _gui->SetSize(event._size);
        }
        glViewport(0, 0, event._size.x, event._size.y);
        return false;
    }

    bool Scene::OnCloseEvent()
    {
        return false;
    }

}