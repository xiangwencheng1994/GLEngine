/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeLabel.h
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

#ifndef SGE_LABEL_H
#define SGE_LABEL_H

#include <ui/sgeView.h>
#include <core/sgeRenderer.h>

namespace sge
{

    namespace ui
    {
        class LabelPrivate;

        /**
         * Class label view
         */
        class SGE_API Label : public View
        {
        public:
            /**
             * Constructor
             */
            Label(Application* app_not_null);
            
            /**
             * Destructor
             */
            virtual ~Label();
            
            /**
             * Set text
             * @param text will be seted, "" will be set if null
             */
            void setText(const char* text);

            /**
             * Get text
             * @return never be null
             */
            const char* getText();

            /**
             * Set enable muiltline
             * @param enable
             */
            void setMuiltLine(bool enable);

            /**
             * Get muiltline enable state
             */
            bool isMuiltLine();

            /**
             * Set line height
             * @notes only used for muiltLine enabled
             * @param lineHeight The default is 1
             */
            void setLineHeight(float lineHeight);

            /**
             * Get the line height
             */
            float getLineHeight();

            /**
             * Set font
             * @param text will be seted, "default" will be set if null
             */
            void setFont(const char* fontName);

            /**
             * Get font
             * @return never be null
             */
            const char* getFont();

            /**
             * Set font size
             * @param size Must bigger than zero
             */
            void setFontSize(float size);

            /**
             * Get font size
             * @return never less/equal than zero
             */
            float getFontSize();

            /**
             * Set font color
             */
            void setFontColor(const float4& color);

            /**
             * Get font color
             */
            float4 getFontColor();

            /**
             * Set text alignment
             */
            void setAlignment(Alignment align);

            /**
             * Get text alignment
             */
            Alignment getAlignment();

        protected:
            /**
             * Override measure label content
             */
            virtual int2 onMeasure(MeasureMode wMode, int wSize, MeasureMode hMode, int hSize) override;

            /**
             * Override draw label
             */
            virtual void onDraw(Renderer* renderer) override;

        private:
            LabelPrivate* d;
            DISABLE_COPY(Label)
        };

    }

}

#endif // !SGE_LABEL_H
