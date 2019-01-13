/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeViewGroup.cpp
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

#include <ui/sgeViewGroup.h>
#include <ui/sgeLayoutParam.h>

namespace sge
{
    namespace ui
    {
        ViewGroup::ViewGroup(Application* app_not_null)
            : View(app_not_null)
        {
        }

        ViewGroup::~ViewGroup()
        {
            for (size_t i = 0; i < mChildren.size(); ++i)
            {
                RefPtr<View> child = getChildAt(i);
                child->setParent(NULL);
            }
        }

        void ViewGroup::addChild(RefPtr<View> view)
        {
            ASSERT(getChildIndex(view.get()) == -1);
            RefPtr<LayoutParams> oldParams = view->getLayoutParams();
            if (!acceptChildLayoutParams(oldParams.get()))
            {
                RefPtr<LayoutParams> params = generateDefaultLayoutParams();
                if (oldParams.get())
                {
                    params->mWidth = oldParams->mWidth;
                    params->mHeight = oldParams->mHeight;
                }
                view->setLayoutParams(params);
            }
            view->setParent(this);
            mChildren.push_back(view);
        }

        void ViewGroup::removeChild(View* view)
        {
            removeChild(getChildIndex(view));
        }

        void ViewGroup::removeChild(int index)
        {
            if (index < 0 || index >= getChildCount())
                return;
            RefPtr<View> child = getChildAt(index);
            mChildren.erase(mChildren.begin() + index);
            child->setParent(NULL);
            requestMeasure();
        }

        inline RefPtr<View> ViewGroup::getChildAt(int index) { return mChildren[index]; }
        inline int ViewGroup::getChildCount() { return mChildren.size(); }
        inline int ViewGroup::getChildIndex(View* view)
        {
            int ret = -1;
            int count = getChildCount();
            for (int i = 0; i < count; ++i)
            {
                if (getChildAt(i).get() == view)
                {
                    ret = i;
                }
            }
            return ret;
        }

        int2 ViewGroup::onMeasure(MeasureMode wMode, int wSize, MeasureMode hMode, int hSize)
        {
            int2 size = View::onMeasure(wMode, wSize, hMode, hSize);

            if (size.x == FILL_PARENT || size.x == MATCH_PARENT)
                size.x = wSize;
            if (size.y == FILL_PARENT || size.y == MATCH_PARENT)
                size.y = hSize;

            int childWSize = getMeasuredWidth();
            int childHSize = getMeasuredHeight();
            if (childWSize <= 0) childWSize = wSize;
            if (childHSize <= 0) childHSize = hSize;
            int count = getChildCount();
            for (int i = 0; i < count; ++i)
            {
                RefPtr<View> view = getChildAt(i);
                view->doMeasure(MeasureMode::UNSPECIFIED, childWSize, MeasureMode::UNSPECIFIED, childHSize);
            }
            if (size.x == WRAP_CONTENT)
            {
                for (int i = 0; i < count; ++i)
                {
                    RefPtr<View> view = getChildAt(i);
                    int childWidth = view->getMeasuredWidth();
                    size.x = MAX(size.x, childWidth);
                }
            }
            if (size.y == WRAP_CONTENT)
            {
                for (int i = 0; i < count; ++i)
                {
                    RefPtr<View> view = getChildAt(i);
                    int childHeight = view->getMeasuredHeight();
                    size.y = MAX(size.y, childHeight);
                }
            }
            return size;
        }

        void ViewGroup::onLayout(bool changed, int left, int top, int width, int height)
        {
            int count = getChildCount();
            for (int i = 0; i < count; ++i)
            {
                RefPtr<View> view = getChildAt(i);
                if (changed)
                {
                    RefPtr<LayoutParams> params = view->getLayoutParams();
                    if (params->mWidth < 0 || params->mHeight < 0)
                        view->requestMeasure();
                }
                int childWidth = view->getMeasuredWidth();
                int childHeight = view->getMeasuredHeight();
                view->doLayout(left, top, childWidth, childHeight);
            }
        }

        RefPtr<LayoutParams> ViewGroup::generateDefaultLayoutParams()
        {
            return RefPtr<LayoutParams>(new LayoutParams(WRAP_CONTENT, WRAP_CONTENT));
        }

        inline bool ViewGroup::acceptChildLayoutParams(LayoutParams * params)
        {
            if (params)
            {
                if (params->mWidth < MIN_LAYOUT_SIZE
                    || params->mHeight < MIN_LAYOUT_SIZE)
                {
                    return false;
                }
                return true;
            }
            return false;
        }

        inline void ViewGroup::onDraw()
        {
            int count = getChildCount();
            for (int i = 0; i < count; i++)
            {
                RefPtr<View> view = getChildAt(i);
                // if (view.isVisible())
                view->doDraw();
            }
        }

    }
}