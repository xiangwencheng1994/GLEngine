/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeView.h
 * date: 2018/12/05
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

#ifndef SGE_VIEW_H
#define SGE_VIEW_H

#include <core/sgePlatform.h>
#include <core/sgePlatformNative.h>

namespace sge
{
    class IScene;

    namespace ui
    {
        /**
         * Interface of GUI view
         */
        class SGE_API IView
        {
        public:
            enum Flags
            {
                FLAG_VISIBLE    =   1 << 0,
                FLAG_ENABLE     =   1 << 1        
            };

        public:
            /**
             * Constructor
             */
            IView() {}

            /**
             * Virtual destructor
             */
            virtual ~IView() {}

            /**
             * Get the visible
             */
            bool    Visible() { return HAS_FLAG(_flags, FLAG_VISIBLE); }

            /**
             * Set the visible
             */
            void    Visible(bool visible) { SET_FLAG(_flags, FLAG_VISIBLE, visible); }

            /**
             * Get the enable
             */
            bool    Enable() { return HAS_FLAG(_flags, FLAG_ENABLE); }

            /**
             * Set the enable
             */
            void    Enable(bool enable) { SET_FLAG(_flags, FLAG_ENABLE, enable); }

            /**
             * Set a new size for this view
             * @param size The new size
             * @return true if set success
             */
            virtual bool SetSize(const int2& size) = 0;

            /**
             * Get the size of this view
             * @return the size of this view
             */
            virtual int2 Size() = 0;

            /**
             * Callback while need render
             */
            virtual void OnRender() = 0;

            /**
             * Callback while mouse left button down
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnLeftButtonDownEvent(const MouseDownEvent& event) = 0;

            /**
             * Callback while mouse left button up
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnLeftButtonUpEvent(const MouseUpEvent& event) = 0;

            /**
             * Callback while mouse left button click
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnLeftButtonClickEvent(const MouseClickEvent& event) = 0;
            
            /**
             * Callback while mouse right button down
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnRightButtonDownEvent(const MouseDownEvent& event) = 0;

            /**
             * Callback while mouse right button up
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnRightButtonUpEvent(const MouseUpEvent& event) = 0;

            /**
             * Callback while mouse right button click
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnRightButtonClickEvent(const MouseClickEvent& event) = 0;
            
            /**
             * Callback while mouse middle button down
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnMiddleButtonDownEvent(const MouseDownEvent& event) = 0;

            /**
             * Callback while mouse middle button up
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnMiddleButtonUpEvent(const MouseUpEvent& event) = 0;

            /**
             * Callback while mouse middle button click
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnMiddleButtonClickEvent(const MouseClickEvent& event) = 0;

            /**
             * Callback while mouse move
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnMouseMoveEvent(const MouseMoveEvent& event) = 0;

            /**
             * Callback while mouse wheel wheeled
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnMouseWheelEvent(const MouseWheelEvent& event) = 0;
            
            /**
             * Callback while key down
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnKeyDownEvent(const KeyDownEvent& event) = 0;

            /**
             * Callback while key up
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnKeyUpEvent(const KeyUpEvent& event) = 0;

        protected:
            friend class Scene;
            /**
             * view flags
             */
            int         _flags;

        private:
            DISABLE_COPY(IView)
        };
        
        /**
         * The base view
         */
        class SGE_API View : public IView
        {
        public:
            /**
             * Constructor
             */
            View();

            /**
             * Destructor
             */
            virtual ~View();

            /**
             * Set size
             */
            virtual bool SetSize(const int2& size) override;

            /**
             * Get size
             */
            int2    Size() override { return _size; }

            /**
             * Set background view
             */
            void    BackgroundView(IView* view);

            /**
             * Get background view
             */
            IView*  BackgroundView() { return _bgView; }

            /**
             * Take the background view
             * @return The backgroud view need delete it by your self or add to a parent view
             */
            IView*  TakeBackgroudView() { IView* v = _bgView; _bgView = NULL; return v; }

        protected:
            /**
             * Callback while need render
             */
            virtual void OnRender() override;

            /**
             * Callback while mouse left button down
             * @param event The event data
             * @return true if the backgroud view has processed
             */
            virtual bool OnLeftButtonDownEvent(const MouseDownEvent& event) override;
            
            /**
             * Callback while mouse left button up
             * @param event The event data
             * @return true if the backgroud view has processed
             */
            virtual bool OnLeftButtonUpEvent(const MouseUpEvent& event) override;
            
            /**
             * Callback while mouse left button click
             * @param event The event data
             * @return true if the backgroud view has processed
             */
            virtual bool OnLeftButtonClickEvent(const MouseClickEvent& event) override;
            
            /**
             * Callback while mouse right button down
             * @param event The event data
             * @return true if the backgroud view has processed
             */
            virtual bool OnRightButtonDownEvent(const MouseDownEvent& event) override;
            
            /**
             * Callback while mouse right button up
             * @param event The event data
             * @return true if the backgroud view has processed
             */
            virtual bool OnRightButtonUpEvent(const MouseUpEvent& event) override;
            
            /**
             * Callback while mouse right button click
             * @param event The event data
             * @return true if the backgroud view has processed
             */
            virtual bool OnRightButtonClickEvent(const MouseClickEvent& event) override;
            
            /**
             * Callback while mouse middle button down
             * @param event The event data
             * @return true if the backgroud view has processed
             */
            virtual bool OnMiddleButtonDownEvent(const MouseDownEvent& event) override;
            
            /**
             * Callback while mouse middle button up
             * @param event The event data
             * @return true if the backgroud view has processed
             */
            virtual bool OnMiddleButtonUpEvent(const MouseUpEvent& event) override;
            
            /**
             * Callback while mouse middle button click
             * @param event The event data
             * @return true if the backgroud view has processed
             */
            virtual bool OnMiddleButtonClickEvent(const MouseClickEvent& event) override;
            
            /**
             * Callback while mouse move
             * @param event The event data
             * @return true if the backgroud view has processed
             */
            virtual bool OnMouseMoveEvent(const MouseMoveEvent& event) override;
            
            /**
             * Callback while mouse wheel wheeled
             * @param event The event data
             * @return true if the backgroud view has processed
             */
            virtual bool OnMouseWheelEvent(const MouseWheelEvent& event) override;

            /**
             * Callback while key down
             * @param event The event data
             * @return true if the backgroud view has processed
             */
            virtual bool OnKeyDownEvent(const KeyDownEvent& event) override;

            /**
             * Callback while key up
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool OnKeyUpEvent(const KeyUpEvent& event) override;

        private:
            IView*      _bgView;
            int2        _size;

            DISABLE_COPY(View)
        };

    }

}

#endif
