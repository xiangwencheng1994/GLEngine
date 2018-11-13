/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeSemaphore.cpp
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

#include <core/sgeSemaphore.h>

#ifdef _WIN32

#include <Windows.h>

namespace sge
{
    class SemaphorePrivate
    {
        HANDLE hSem;

        friend class Semaphore;
    };

    Semaphore::Semaphore(long lInit, long lMax)
        : d(new SemaphorePrivate())
    {
        d->hSem = ::CreateSemaphore(0, lMax, lInit, 0);
        ASSERT(d->hSem && "CreateSemaphore failed!");
    }

    Semaphore::~Semaphore()
    {
        if (d)
        {
            if (d->hSem)
            {
                ::CloseHandle(d->hSem);
                d->hSem = 0;
            }
            delete d;
            d = NULL;
        }
    }

    inline bool Semaphore::Wait(unsigned long ms)
    {
        switch (::WaitForSingleObject(d->hSem, ms))
        {
        case WAIT_OBJECT_0:
            return true;
            break;
        case WAIT_TIMEOUT:
            break;
        default:
            break;
        }
        return false;
    }

    inline bool Semaphore::Set(long number)
    {
        return TRUE == ::ReleaseSemaphore(d->hSem, number, 0);
    }

}

#else

#include <semaphore.h>
#include <time.h>

namespace sge
{
	class SemaphorePrivate
	{
		sem_t hSem;

		friend class Semaphore;
	};

	Semaphore::Semaphore(long lInit, long unused)
		: d(new SemaphorePrivate())
	{
		int ret = sem_init(&d->hSem, 0, lInit);
		assert(ret == 0 && "sem_init failed!");
	}

	Semaphore::~Semaphore()
	{
		if (d)
		{
			sem_destroy(d->hSem);
			delete d;
			d = NULL;
		}
	}

    inline bool Semaphore::Wait(unsigned long ms)
	{
		struct timespec abstime;
		struct timeval tv;
		gettimeofday(&tv, 0);
		abstime.tv_sec = tv.tv_sec + ms / 1000;
		abstime.tv_nsec = tv.tv_usec * 1000 + (ms % 1000) * 1000000;
		if (abstime.tv_nsec >= 10000000000)
		{
			abstime.tv_nsec -= 10000000000;
			abstime.tv_sec++;
		}
		return 0 == sem_timedwait(&d->hSem, abstime);
	}

    inline bool Semaphore::Set(long number)
	{
		bool ret = true;
		for (long i = 0; i < number; ++i)
		{
			if (0 != sem_post(&d->hSem))
			{
				ret = false;
				break;
			}
		}
		return ret;
	}

}

#endif