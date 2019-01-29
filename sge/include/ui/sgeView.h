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

#ifndef SGE_VIEW_H
#define SGE_VIEW_H

#include <core/sgePlatform.h>
#include <core/sgePlatformNative.h>
#include <core/sgeRefPtr.h>

namespace sge
{
    class Scene;
    class Application;
    class Renderer;

    namespace ui
    {
        /**
         * Enum for measure mode
         */
        enum MeasureMode
        {
            // parent unspectified, set size for you want
            UNSPECIFIED,
            // parent set the exactly size for you
            EXACTLY,
            // parent set the max size for you
            AT_MOST,
        };

        class LayoutParams;
        class ViewGroup;



        /**
         * Base class of GUI Contorls
         */
        class SGE_API View
        {
        public:
            /**
             * Constructor
             */
            explicit View(Application* app_not_null);

            /**
             * Virtual destructor
             */
            virtual ~View();

            /**
             * Get the hold context of this view
             */
            Application* getApplication() const;

            /**
             * Get the measured width size of this view
             * @return The measured width size
             */
            int getMeasuredWidth() const;

            /**
             * Get the measured height size of this view
             * @return The measured width size
             */
            int getMeasuredHeight() const;

            /**
             * Callback while need measure this view
             * @param wMode The width measure mode
             * @param wSize The width size based
             * @param hMode The height measure mode
             * @param hSize The height size based
             * @return the result of measured size
             */
            virtual int2 onMeasure(MeasureMode wMode, int wSize, MeasureMode hMode, int hSize);
            
            /**
             * Get the layout params
             */
            RefPtr<LayoutParams> getLayoutParams() const;

            /**
             * Set the layout  params
             * @return false if has parent view and parent view can not accpet the LayoutParams
             */
            bool setLayoutParams(RefPtr<LayoutParams> params);

            /**
             * Get parent view
             * @return NULL if none parent set
             */
            ViewGroup* getParent() const;

            /**
             * Called from layout when this view should
             * assign a size and position to each of its children.
             *
             * Derived classes with children should override
             * this method and call DoLayout on each of
             * their children.
             * @param changed This is a new size or position for this view
             * @param left Left position, relative to parent
             * @param top Top position, relative to parent
             * @param width of content
             * @param height of content
             */
            virtual void onLayout(bool changed, int left, int top, int width, int height);

            /**
             * This is called during layout when the size of this view has changed. If
             * you were just added to the view hierarchy, you're called with the old
             * values of 0.
             *
             * @param w Current width of this view.
             * @param h Current height of this view.
             * @param oldw Old width of this view.
             * @param oldh Old height of this view.
             */
            virtual void onSizeChanged(int newWidth, int newHeight, int oldWidth, int oldHeight);

            /**
             * Get frame left
             */
            int getLeft();

            /**
             * Get frame top
             */
            int getTop();

            /**
             * Get frame width
             */
            int getWidth();

            /**
             * Get frame height
             */
            int getHeight();
            
#pragma region EventCallback

            /**
             * Callback while need render
             */
            virtual void onDraw(Renderer* renderer) = 0;

            /**
             * Callback while mouse left button down
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onLeftButtonDownEvent(const MouseDownEvent& event) { return false; };

            /**
             * Callback while mouse left button up
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onLeftButtonUpEvent(const MouseUpEvent& event) { return false; };

            /**
             * Callback while mouse left button click
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onLeftButtonClickEvent(const MouseClickEvent& event) { return false; };
            
            /**
             * Callback while mouse right button down
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onRightButtonDownEvent(const MouseDownEvent& event) { return false; };

            /**
             * Callback while mouse right button up
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onRightButtonUpEvent(const MouseUpEvent& event) { return false; };

            /**
             * Callback while mouse right button click
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onRightButtonClickEvent(const MouseClickEvent& event) { return false; };
            
            /**
             * Callback while mouse middle button down
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onMiddleButtonDownEvent(const MouseDownEvent& event) { return false; };

            /**
             * Callback while mouse middle button up
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onMiddleButtonUpEvent(const MouseUpEvent& event) { return false; };

            /**
             * Callback while mouse middle button click
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onMiddleButtonClickEvent(const MouseClickEvent& event) { return false; };

            /**
             * Callback while mouse move
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onMouseMoveEvent(const MouseMoveEvent& event) { return false; };

            /**
             * Callback while mouse wheel wheeled
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onMouseWheelEvent(const MouseWheelEvent& event) { return false; };
            
            /**
             * Callback while key down
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onKeyDownEvent(const KeyDownEvent& event) { return false; };

            /**
             * Callback while key up
             * @param event The event data
             * @return true if you has processed this event
             */
            virtual bool onKeyUpEvent(const KeyUpEvent& event) { return false; };

#pragma endregion

            public:
                /**
                 * Add request remeasure flag for this view
                 */
                void requestMeasure();

                /**
                 * Do measure context for this view
                 */
                void doMeasure(MeasureMode wMode, int wSize, MeasureMode hMode, int hSize);

                /**
                 * Do layout frame for this view
                 */
                void doLayout(int left, int top, int width, int height);

                /**
                 * Do render context for this view
                 */
                void doDraw(Renderer* renderer);

        protected:
            friend class Scene;
            friend class ViewGroup;

            void setParent(ViewGroup* parent);



            /**
             * Set frame for this view
             */
            bool setFrame(int left, int top, int width, int height);

            /**
             * Get the default size by suggest
             */
            static int getDefaultSize(int size, MeasureMode wMode, int wSize);

        private:
            friend class ViewPrivate;
            ViewPrivate* d;
            DISABLE_COPY(View)
        };
        
    }

}

#endif
