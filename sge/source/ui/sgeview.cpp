/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeView.cpp
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

#include <ui/sgeView.h>
#include <core/sgeApplication.h>
#include <core/sgeRenderer.h>
#include <ui/sgeViewGroup.h>

namespace sge
{
    namespace ui
    {
        enum PrivateFlag
        {
            PFLAG_VISIBLE   = 1 << 0,
            PFLAG_MEASURE   = 1 << 1,
            PFLAG_RELAYOUT  = 1 << 2,
        };

        class ViewPrivate
        {
        public:
            Application*    mApp;
            ViewGroup*      mParent;
            RefPtr<LayoutParams> mLayoutParam;

        public:
            int         mFlag;
            int         mLeft;
            int         mTop;
            int         mWidth;
            int         mHeight;

            ViewPrivate(Application* app_not_null)
                : mApp(app_not_null), mFlag(PFLAG_MEASURE | PFLAG_RELAYOUT),
                mLeft(0), mTop(0), mWidth(0), mHeight(0),
                mParent(NULL), mLayoutParam(NULL)
            {}

            ~ViewPrivate()
            {
                ASSERT(mParent == NULL && "release but not remove from parent");
            }
        };

        View::View(Application* app_not_null)
            : d(new ViewPrivate(app_not_null))
        {
            ASSERT(app_not_null && "while create a new view");
        }

        View::~View()
        {
            if (d)
            {
                if (d->mParent)
                {
                    d->mParent->removeChild(this);
                    d->mParent = NULL;
                }
                delete d;
                d = NULL;
            }
        }
        
        inline Application* View::getApplication() const { return d->mApp; }
        inline int View::getMeasuredWidth() const { return d->mWidth; }
        inline int View::getMeasuredHeight() const { return d->mHeight; }
        inline RefPtr<LayoutParams> View::getLayoutParams() const { return d->mLayoutParam; }
        inline bool View::setLayoutParams(RefPtr<LayoutParams> params) 
        {
            if (d->mParent)
            {
                if (!d->mParent->acceptChildLayoutParams(params.get()))
                    return false;
            }
            d->mLayoutParam = params;
            return true;
        }
        inline ViewGroup* View::getParent() const { return d->mParent; }
        inline void View::setParent(ViewGroup* parent)
        {
            ASSERT(parent == NULL || d->mParent == NULL);
            d->mParent = parent;
        }
        inline void View::requestMeasure() 
        {
            ADD_FLAG(d->mFlag, PFLAG_MEASURE);
            if (d->mParent)
            {
                ADD_FLAG(d->mParent->d->mFlag, PFLAG_RELAYOUT);
                d->mParent->requestMeasure();
            }
        }
        inline void View::onLayout(bool changed, int left, int top, int right, int bottom) {}
        inline void View::onSizeChanged(int newWidth, int newHeight, int oldWidth, int oldHeight) {}
        inline int View::getLeft() { return d->mLeft; }
        inline int View::getTop() { return d->mTop; }
        inline int View::getWidth() { return d->mWidth; }
        inline int View::getHeight() { return d->mHeight; }

        inline int2 View::onMeasure(MeasureMode wMode, int wSize, MeasureMode hMode, int hSize)
        {
            int2 ret = int2(getDefaultSize(d->mLayoutParam->mWidth, wMode, wSize),
                getDefaultSize(d->mLayoutParam->mHeight, hMode, hSize));
            if (ret.x == MATCH_PARENT || ret.x == FILL_PARENT) ret.x = wSize;
            if (ret.y == MATCH_PARENT || ret.y == FILL_PARENT) ret.y = hSize;
            return ret;
        }

        inline void View::doMeasure(MeasureMode wMode, int wSize, MeasureMode hMode, int hSize)
        {
            if (HAS_FLAG(d->mFlag, PFLAG_MEASURE))
            {
                int2 ret = onMeasure(wMode, wSize, hMode, hSize);
                if (ret.x < WRAP_CONTENT) ret.x = wSize;
                if (ret.y < WRAP_CONTENT) ret.y = hSize;
                d->mWidth = ret.x;
                d->mHeight = ret.y;
                if (d->mWidth < 0)
                    d->mWidth = 0;
                if (d->mHeight < 0)
                    d->mHeight = 0;
                REMOVE_FLAG(d->mFlag, PFLAG_MEASURE);
            }
        }

        void View::doLayout(int left, int top, int width, int height)
        {
            bool changed = setFrame(left, top, width, height);
            if ( changed || HAS_FLAG(d->mFlag, PFLAG_RELAYOUT))
            {
                onLayout(changed, left, top, width, height);
                REMOVE_FLAG(d->mFlag, PFLAG_RELAYOUT);
            }
        }

        void View::doDraw()
        {
            Renderer* renderer = d->mApp->getRenderer();
            int saveCount = renderer->save();
            renderer->doTranslate((float)d->mLeft, (float)d->mTop);
            renderer->addIntersectScissor((float)d->mLeft, (float)d->mTop, (float)d->mWidth, (float)d->mHeight);
            onDraw();
#ifdef _DEBUG
            renderer->beginPath();            
            renderer->rect(0, 0, (float)d->mWidth, (float)d->mHeight);
            renderer->setStrokeColor(0, 0.6f, 0, 1.0f);
            renderer->setStrokeWidth(4);
            renderer->strokePath();
            renderer->beginPath();
#endif // _DEBUG
            renderer->restore(saveCount);
        }

        bool View::setFrame(int left, int top, int width, int height)
        {
            bool changed = false;

            bool sizeChanged = d->mWidth != width || d->mHeight != height;
            if (sizeChanged || d->mLeft != left || d->mTop != top)
            {
                changed = true;
                int oldWidth = d->mWidth;
                int oldHeight = d->mHeight;
                d->mLeft = left;
                d->mTop = top;
                d->mWidth = width;
                d->mHeight = height;
                if (sizeChanged) 
                {
                    // parent need relayout items while any child size has changed
                    onSizeChanged(width, height, oldWidth, oldHeight);
                }
            }

            return changed;
        }

        int View::getDefaultSize(int size, MeasureMode mode, int specSize)
        {
            int result = 0;
            switch (mode)
            {
            case MeasureMode::UNSPECIFIED:
                result = size;
                break;
            case MeasureMode::EXACTLY:
            case MeasureMode::AT_MOST:
                result = specSize;
                break;
            }
            return result;
        }

    }
}