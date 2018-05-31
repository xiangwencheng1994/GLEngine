/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeLog.h
 * date: 2017/12/04
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

#ifndef SGE_LOG_H
#define SGE_LOG_H

#include <sge.h>

namespace sge {

    /**
     * Class Log is a tool to record logs
     */
    class SGE_API Log
    {
    public:
        typedef int Level;

        typedef void(*Output)(Level lv, char *msg);

        static const Level Debug    = 0;
        static const Level Info     = 10;
        static const Level Error    = 20;

    public:
        /**
         * The real output function pointer.
         * @note You can redistribution this pointer to yours
         */
        static Output output;

        /**
         * This is the default function for output
         * It just format string and print to stdout, 
         * and extra OutputDebugString for win32 
         */
        static void defaultOutput(Level lv, char *msg);

        /**
         * Output a debug log with string format
         * @param fmt The format
         * @... The Var for format string
         */
        static void debug(const char* fmt, ...);

        /**
         * Output a info log with string format
         * @param fmt The format
         * @... The Var for format string
         */
        static void info(const char* fmt, ...);

        /**
         * Output a error log with string format
         * @param fmt The format
         * @... The Var for format string
         */
        static void error(const char* fmt, ...);

    };

} // !namespace

#endif // !SGE_LOG_H