/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeScene.h
 * date: 2018/12/04
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

#ifndef SGE_SCENE_H
#define SGE_SCENE_H

#include <core/sgePlatform.h>
#include <core/sgePlatformNative.h>

namespace sge
{

    class Application;

    /**
     * Class scene, execute by Application
     * @note must use 'new' method to create instance, it will be deleted after unload.
     */
    class SGE_API IScene
    {
    protected:
        friend class Application;

        /**
         * Call by application when need load this scene
         * @param app The application which need load this scene
         */
        virtual void OnLoad(Application* app) = 0;

        /**
         * Call by application when need unload this scene
         * @param app The application which need unload this scene
         */
        virtual void OnUnLoad(Application* app) = 0;

        /**
         * Call by application when need render this scene
         * @param app The application which need render this scene
         */
        virtual void OnRender(Application* app) = 0;

        /**
         * Release this object
         */
        virtual void Release() = 0;
    };


    namespace ui
    {
        class IView;
    }

    /**
     * The base scene
     */
    class SGE_API Scene : public IScene
    {
    public:
        /**
         * Constructor
         */
        Scene();
        
        /**
         * Destructor
         */
        virtual ~Scene();

    protected:
        
        /**
         * Load the base scene
         */
        virtual void OnLoad(Application* app) override;

        /**
         * Unload the base scene
         */
        virtual void OnUnLoad(Application* app) override;

        /**
         * Render the base scene
         */
        virtual void OnRender(Application* app) override;
        
        /**
         * Callback while mouse left button down
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnLeftButtonDownEvent(const MouseDownEvent& event);

        /**
         * Callback while mouse left button up
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnLeftButtonUpEvent(const MouseUpEvent& event);

        /**
         * Callback while mouse left button click
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnLeftButtonClickEvent(const MouseClickEvent& event);

        /**
         * Callback while mouse right button down
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnRightButtonDownEvent(const MouseDownEvent& event);

        /**
         * Callback while mouse right button up
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnRightButtonUpEvent(const MouseUpEvent& event);

        /**
         * Callback while mouse right button click
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnRightButtonClickEvent(const MouseClickEvent& event);

        /**
         * Callback while mouse middle button down
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnMiddleButtonDownEvent(const MouseDownEvent& event);

        /**
         * Callback while mouse middle button up
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnMiddleButtonUpEvent(const MouseUpEvent& event);

        /**
         * Callback while mouse middle button click
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnMiddleButtonClickEvent(const MouseClickEvent& event);

        /**
         * Callback while mouse move
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnMouseMoveEvent(const MouseMoveEvent& event);

        /**
         * Callback while mouse wheel wheeled
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnMouseWheelEvent(const MouseWheelEvent& event);

        /**
         * Callback while key down
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnKeyDownEvent(const KeyDownEvent& event);

        /**
         * Callback while key up
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnKeyUpEvent(const KeyUpEvent& event);

        /**
         * Callback while wanted set size
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool OnResizeEvent(const ResizeEvent& event);

        /**
         * Callback while wanted close application
         * @return true if you want not close.
         */
        virtual bool OnCloseEvent();

    private:
        ui::IView*      _gui;
    };

}

#endif // !SGE_SCENE_H
