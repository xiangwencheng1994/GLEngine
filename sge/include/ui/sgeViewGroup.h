/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeViewGroup.h
 * date: 2019/01/13
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

#ifndef SGE_VIEW_GROUP_H
#define SGE_VIEW_GROUP_H

#include <ui/sgeView.h>

namespace sge
{

    namespace ui
    {
        // Content size decide by content
        #define WRAP_CONTENT    (-1)
        // Content size decide by parent
        #define MATCH_PARENT    (-2)
        // Content size fill parent size
        #define FILL_PARENT     (-3)

        // The min layout size can seted
        #define MIN_LAYOUT_SIZE MIN(MIN(WRAP_CONTENT, MATCH_PARENT), FILL_PARENT)

        /**
         * The layout params
         */
        class LayoutParams
        {
        public:
            /**
             * The exactly width or WRAP_CONTENT/MATCH_PARENT/FILL_PARENT
             */
            int     mWidth;

            /**
             * The exactly height or WRAP_CONTENT/MATCH_PARENT/FILL_PARENT
             */
            int     mHeight;
        public:
            /**
             * Constructor
             */
            LayoutParams(int width, int height)
                : mWidth(width), mHeight(height)
            {}

        };

        /**
         * The ViewGroup class, container of views         
         */
        class SGE_API ViewGroup : public View
        {
        public:
            /**
             * Constructor
             */
            ViewGroup(Application* app_not_null);

            /**
             * Destructor
             */
            virtual ~ViewGroup();

            /**
             * Add a child view
             */
            void addChild(RefPtr<View> view);

            /**
             * Remove a child view
             */
            void removeChild(View* view);

            /**
             * Remove a child view at index
             */
            void removeChild(int index);

            /**
             * Get the child view at index
             * @return zero pointer if none view at index
             */
            RefPtr<View> getChildAt(int index);

            /**
             * Get child count
             * @return child count
             */
            int getChildCount();

            /**
             * Get the child index
             * @param view The child pointer
             * @return the index of view or -1 if none
             */
            int getChildIndex(View* view);

        protected:
            friend class View;

            /**
             * Callback on measure size and all child size
             * @seealso ui.View.onMeasure()
             */
            virtual int2 onMeasure(MeasureMode wMode, int wSize, MeasureMode hMode, int hSize);

            /**
             * Callback on layout content and all child content
             * @seealse ui.View.onLayout()
             */
            virtual void onLayout(bool changed, int left, int top, int right, int bottom);

            /**
             * Generate a default LayoutParams for this layout
             * @return a referenced LayoutParams
             */
            virtual RefPtr<LayoutParams> generateDefaultLayoutParams();

            /**
             * Try accept a LayoutParams for a view in this layout
             * @return ture if veiw can set params in this layout
             */
            virtual bool acceptChildLayoutParams(LayoutParams* params);

            /**
             * Callback on draw content and all child content
             */
            virtual void onDraw();

        protected:
            // The child list
            Vector<RefPtr<View>> mChildren;
            // The foused children
            RefPtr<View>         mFousedChildren;
        };

    }

}


#endif // !SGE_VIEW_GROUP_H
