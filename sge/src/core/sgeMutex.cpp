/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeMutex.cpp
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

#include <core/sgeMutex.h>

#ifdef _WIN32

#include <Windows.h>

namespace sge
{

	class   MutexPrivate
	{
		CRITICAL_SECTION cs;
		friend class Mutex;
	};

	Mutex::Mutex()
		: d(new MutexPrivate())
	{
		::InitializeCriticalSection(&d->cs);
	}

	Mutex::~Mutex()
	{
		if (d)
		{
			::DeleteCriticalSection(&d->cs);
			delete  d;
			d   =   NULL;
		}
	}

	inline void Mutex::lock() const
	{
		::EnterCriticalSection(&d->cs);
	}

    inline void Mutex::unlock() const
	{
		::LeaveCriticalSection(&d->cs);
	}

    inline bool Mutex::tryLock() const
	{
		return  TRUE == ::TryEnterCriticalSection(&d->cs);
	}

}

#else

#include <pthread.h>

namespace sge
{

    class   MutexPrivate
    {
        pthread_mutex_t _mutex;
        friend class Mutex;
    };

    Mutex::Mutex()
        : d(new MutexPrivate())
    {
        pthread_mutex_init(&d->_mutex, NULL);
    }

    Mutex::~Mutex()
    {
        if (d)
        {
            pthread_mutex_destroy(&d->_mutex);
            delete  d;
            d   =   NULL;
        }
    }

    inline void Mutex::lock() const
    {
        int ret =   pthread_mutex_lock(&d->_mutex);
		ASSERT(ret == 0);
    }

    inline void Mutex::unlock() const
    {
        int ret =   pthread_mutex_unlock(&d->_mutex);
        ASSERT(ret == 0);
    }

    inline bool Mutex::tryLock() const
    {
        return  0 == pthread_mutex_trylock(&d->_mutex);
    }

}

#endif
