/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeLog.cpp
 * date: 2017/12/05
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

#include <core/sgeLog.h>

#include <time.h>
#include <stdio.h>
#include <stdarg.h>

namespace sge 
{
    // format string by args
    #define FORMAT(out, fmtStr) char out[512] = { 0 };          \
                            va_list __vl;                       \
                            va_start(__vl, fmtStr);             \
                            vsnprintf(out, 512, fmtStr, __vl);  \
                            va_end(__vl)

    Log::Output Log::output = Log::defaultOutput;

    void Log::defaultOutput(Log::Level lv, char *msg)
    {
        char buf[4096];
        const char* fmt[5] = 
        {
            "[D]:%s\n",
            "[I]:%s\n",
            "[W]:%s\n",
            "[E]:%s\n",
            "[U]:%s\n"
        };
        sprintf_s(buf, fmt[lv], msg);
#if _WIN32 && _DEBUG
        OutputDebugStringA(buf);
#endif
        printf(buf);
    }

    void Log::debug(const char* fmt, ...)
    {
        FORMAT(strBuffer, fmt);
        if (output) (*output)(Log::Debug, strBuffer);
    }

    void Log::info(const char* fmt, ...)
    {
        FORMAT(strBuffer, fmt);
        if (output) (*output)(Log::Info, strBuffer);
    }

    void Log::warn(const char* fmt, ...)
    {
        FORMAT(strBuffer, fmt);
        if (output) (*output)(Log::Warn, strBuffer);
    }

    void Log::error(const char* fmt, ...)
    {
        FORMAT(strBuffer, fmt);
        if (output) (*output)(Log::Error, strBuffer);
    }

}