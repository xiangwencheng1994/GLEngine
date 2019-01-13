/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeTimerWin.cpp
 * date: 2017/12/05
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

#include <core/sgeTimer.h>

#ifdef _WIN32

#include <core/sgeLog.h>

namespace sge 
{

    class TimerPrivate
    {
        float liQPF;
        LONGLONG liLastTime;

        friend class Timer;
    };


    Timer::Timer()
        : d(new TimerPrivate())
    {
        LARGE_INTEGER cpuQPF;
        bool ret = QueryPerformanceFrequency(&cpuQPF);
        if (ret)
        {
            d->liQPF = (float)cpuQPF.QuadPart;
        }
        else
        {
            Log::error("Timer can not work, becase QueryPerformanceFrequency failed.");
        }
    }

    Timer::~Timer()
    {
        if (d)
        {
            delete d;
            d = NULL;
        }
    }


    inline float Timer::elapsed()
    {
        LARGE_INTEGER nowTime;
        QueryPerformanceCounter(&nowTime);
        float elapsed = (nowTime.QuadPart - d->liLastTime) / d->liQPF;
        d->liLastTime = nowTime.QuadPart;
        return elapsed;
    }

}

#else

#include <sys/time.h>

namespace sge
{

	class TimerPrivate
	{
		struct timeval time;

		friend class Timer;
	};


	Timer::Timer()
		: d(new TimerPrivate())
	{
	}

	Timer::~Timer()
	{
		if (d)
		{
			delete d;
			d = NULL;
		}
	}

	float Timer::elapsed()
	{
		timeval current;
		gettimeofday(&current, NULL);
		int offsev = current.tv_sec - d->time.tv_sec;
		int offusev = current.tv_usec - d->time.tv_usec;
		float elapsed = ((offsev * 1000000) + offusev) * 0.0000001f;
		time = current;
		return elapsed;
	}

}

#endif
