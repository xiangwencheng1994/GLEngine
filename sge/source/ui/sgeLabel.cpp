﻿#include "..\..\include\ui\sgeLabel.h"
#include "..\..\include\ui\sgeLabel.h"
/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeLabel.cpp
 * date: 2018/01/11
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

#include <ui/sgeLabel.h>
#include <core/sgeApplication.h>
#include <core/sgeRenderer.h>
#include <ui/sgeViewGroup.h>

namespace sge
{

    namespace ui
    {

        class LabelPrivate
        {
        public:
            String      mText;
            bool        mMuiltLine;
            String      mFont;
            float       mFontSize;
            float       mLineHeight;
            float4      mFontColor;
            Alignment   mAlign;

            LabelPrivate()
                : mFont("default")
                , mFontSize(24)
                , mFontColor(1, 1, 1, 1)
                , mAlign(Alignment::TopLeft)
                , mMuiltLine(false)
                , mText("Text")
                , mLineHeight(1)
            {
            }
        };

        Label::Label(Application * app_not_null)
            : View(app_not_null), d(new LabelPrivate())
        {
        }

        Label::~Label()
        {
            if (d)
            {
                delete d;
                d = NULL;
            }
        }

        void Label::setText(const char* text)
        {
            if (text == NULL)
                text = "";

            if (strcmp(text, d->mText.c_str()) != 0)
            {
                d->mText = text;
                RefPtr<ui::LayoutParams> params = getLayoutParams();
                if (params.get() &&
                    (params->mWidth == WRAP_CONTENT || params->mHeight == WRAP_CONTENT))
                {
                    requestMeasure();
                }
            }
        }

        inline const char * Label::getText() { return d->mText.c_str(); }

        void Label::setMuiltLine(bool enable)
        {
            if (d->mMuiltLine != enable)
            {
                d->mMuiltLine = enable;
                RefPtr<ui::LayoutParams> params = getLayoutParams();
                if (params.get() &&
                    (params->mWidth == WRAP_CONTENT || params->mHeight == WRAP_CONTENT))
                {
                    requestMeasure();
                }
            }
        }

        inline bool Label::isMuiltLine()
        {
            return d->mMuiltLine;
        }

        void Label::setLineHeight(float lineHeight)
        {
            if (lineHeight != d->mLineHeight)
            {
                d->mLineHeight = lineHeight;
                RefPtr<ui::LayoutParams> params = getLayoutParams();
                if (params.get() &&
                    (params->mWidth == WRAP_CONTENT || params->mHeight == WRAP_CONTENT))
                {
                    requestMeasure();
                }
            }
        }

        inline float Label::getLineHeight()
        {
            return d->mLineHeight;
        }

        void Label::setFont(const char * fontName)
        {
            if (fontName == NULL)
                fontName = "default";

            if (strcmp(fontName, d->mFont.c_str()) != 0)
            {
                d->mFont = fontName;
                RefPtr<ui::LayoutParams> params = getLayoutParams();
                if (params.get() &&
                    (params->mWidth == WRAP_CONTENT || params->mHeight == WRAP_CONTENT))
                {
                    requestMeasure();
                }
            }
        }

        inline const char * Label::getFont()
        {
            return d->mFont.c_str();
        }


        inline void Label::setFontSize(float size)
        {
            if (size > 0 && size != d->mFontSize)
            {
                d->mFontSize = size;
                RefPtr<ui::LayoutParams> params = getLayoutParams();
                if (params.get() &&
                    (params->mWidth == WRAP_CONTENT || params->mHeight == WRAP_CONTENT))
                {
                    requestMeasure();
                }
            }
        }
        inline float Label::getFontSize()
        {
            return d->mFontSize;
        }

        inline void Label::setFontColor(const float4 & color)
        {
            d->mFontColor = color;
        }

        inline float4 Label::getFontColor()
        {
            return d->mFontColor;
        }

        inline void Label::setAlignment(Alignment align)
        {
            if (d->mAlign != align)
            {
                d->mAlign = align;
                RefPtr<ui::LayoutParams> params = getLayoutParams();
                if (params.get() &&
                    (params->mWidth == WRAP_CONTENT || params->mHeight == WRAP_CONTENT))
                {
                    requestMeasure();
                }
            }
        }

        inline Alignment Label::getAlignment()
        {
            return d->mAlign;
        }

        int2 Label::onMeasure(MeasureMode wMode, int wSize, MeasureMode hMode, int hSize)
        {
            int2 res = View::onMeasure(wMode, wSize, hMode, hSize);
            if (res.x == WRAP_CONTENT || res.y == WRAP_CONTENT)
            {
                Renderer* renderer = getApplication()->getRenderer();
                renderer->setFontSize(d->mFontSize);
                renderer->setTextLineHeight(d->mLineHeight);
                renderer->setTextAlign(Alignment::TopLeft);
                float bounds[4];
                if (d->mMuiltLine)
                {
                    RendererTextRow row[64];
                    int lineCount = renderer->getTextBoxLineCount(d->mText.c_str(), d->mText.c_str() + d->mText.size(),
                        (float)(wSize < 0 ? INT_MAX : wSize), row, 16);
                    float lineHeight;
                    renderer->getTextMetrics(0, 0, &lineHeight);
                    lineHeight *= d->mLineHeight;
                    bounds[0] = 0.0f;
                    bounds[1] = 0.0f;
                    bounds[2] = 0.0f;
                    for (int i = 0; i < lineCount; ++i)
                    {
                        if (bounds[2] < row[i].width) bounds[2] = row[i].width;
                    }
                    bounds[3] = lineHeight * lineCount;
                }
                else
                {
                    renderer->measureText(0.0f, 0.0f, d->mText.c_str(),
                        d->mText.c_str() + d->mText.size(), bounds);
                }
                if (res.x == WRAP_CONTENT) res.x = (int)(bounds[2]/* - bounds[0]*/);
                if (res.y == WRAP_CONTENT) res.y = (int)(bounds[3]/* - bounds[1]*/);
            }
            return res;
        }

        void Label::onDraw(Renderer* renderer)
        {
            renderer->setFont(d->mFont.c_str());
            renderer->setFontSize(d->mFontSize);

            float width = (float)getWidth(), height = (float)getHeight();

            float y;
            if (d->mAlign & RendererAlign::VCenter) y = height / 2;
            else if (d->mAlign & RendererAlign::Bottom) y = height;
            else y = 0.0f;

            renderer->setTextAlign(d->mAlign);
            renderer->setFillColor(d->mFontColor);
            if (d->mMuiltLine)
            {
                float lineHeight;
                renderer->setTextLineHeight(d->mLineHeight);
                renderer->getTextMetrics(0, 0, &lineHeight);
                if (d->mAlign & RendererAlign::Top)
                {
                    renderer->drawTextBox(0.0f, 0.0f, width, d->mText.c_str(), d->mText.c_str() + d->mText.size());
                }
                else
                {
                    RendererTextRow row[64];
                    int lineCount = renderer->getTextBoxLineCount(d->mText.c_str(), d->mText.c_str() + d->mText.size(), width, row, 16);
                    float step = lineHeight;
                    if (d->mAlign & RendererAlign::VCenter) y -= lineHeight * (lineCount - 1) / 2;
                    else y -= lineHeight * lineCount - lineHeight;

                    for (int i = 0; i < lineCount; ++i)
                    {
                        if (y > height)
                            break;
                        renderer->drawTextBox(0.0f, y, width, row[i].start, row[i].next);
                        y += step;
                    }
                }
            }
            else
            {
                float x;
                if (d->mAlign & RendererAlign::HCenter) x = width / 2;
                else if (d->mAlign & RendererAlign::Right) x = width;
                else x = 0.0f;
                renderer->drawText(x, y, d->mText.c_str(), d->mText.c_str() + d->mText.size());
            }
        }
    }

}