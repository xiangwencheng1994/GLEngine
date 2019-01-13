/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeLayoutParam.h
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

#ifndef SGE_LAYOUT_PARAM_H
#define SGE_LAYOUT_PARAM_H

#include <core/sgeMath.h>

namespace sge
{

    namespace ui
    {


        /**
         * The margin layout params
         */
        class MarginLayoutParams : public LayoutParams
        {
        public:
            int     mMarginLeft;
            int     mMarginTop;
            int     mMarginRight;
            int     mMarginBottom;

        public:
            MarginLayoutParams(int width = WRAP_CONTENT, int height = WRAP_CONTENT,
                int marginLeft = 0, int marginTop = 0, int marginRight = 0, int marginBottom = 0)
                : LayoutParams(width, height)
                , mMarginLeft(marginLeft)
                , mMarginTop(marginTop)
                , mMarginRight(marginRight)
                , mMarginBottom(marginBottom)
            {}
        };

    }

}

#endif // !SGE_LAYOUT_PARAM_H
