/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeThread.cpp
 * date: 2017/12/06
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

#include <sgeThread.h>

#ifdef _WIN32

#include <Windows.h>

namespace sge
{

    class ThreadPrivate
    {
        TID     tid;
        HANDLE  handle;
        int     retCode;

        Runable* run;

        ThreadPrivate()
            : tid(NULL), handle(NULL), retCode(0), run(NULL) 
        {
        }

        ThreadPrivate(Runable runable)
            : tid(NULL), handle(NULL), retCode(0), run(new Runable(runable))
        {
        }

        ~ThreadPrivate()
        {
            if (run)
            {
                delete run;
                run = NULL;
            }
        }

        friend class Thread;

        static DWORD WINAPI ThreadEntry(LPVOID lpParam)
        {
            Thread* pThis = (Thread*)lpParam;
            if (pThis)
            {
                pThis->d->retCode = pThis->Run();
            }
            return 0;
        }
    };

    void Thread::Sleep(unsigned int ms)
    {
        ::Sleep(ms);
    }

	TID Thread::CurrentThreadId()
	{
		return GetCurrentThreadId();
	}

    Thread::Thread()
        : d(new ThreadPrivate())
    {
    }

    Thread::Thread(Runable runable)
        : d(new ThreadPrivate(runable))
    {
    }

    Thread::~Thread()
    {
        if (d)
        {
            Join();
            delete d;
            d = NULL;
        }
    }

    bool Thread::Start()
    {
        if (d->tid || d->handle)
        {
            ASSERT("Can not start a thread again.");
            return false;
        }
        
        d->handle = ::CreateThread(NULL, 0, 
            &ThreadPrivate::ThreadEntry, this, 0, &d->tid);
        return d->handle != NULL;
    }

    int Thread::Join()
    {
        if (d->handle)
        {
            ::WaitForSingleObject(d->handle, 0xFFFFFFFF);
            ::CloseHandle(d->handle);
            d->handle = NULL;
        }
        return d->retCode;
    }

    TID Thread::ThreadId() const
    {
        return d->tid;
    }

    HANDLE Thread::Handle() const
    {
        return d->handle;
    }

    int Thread::Run()
    {
        if (d->run)
        {
            return (*d->run)();
        }
        return 0;
    }

}

#else

#include <pthread.h>
#include <unistd.h>

namespace sge
{

	class ThreadPrivate
	{
		pthread_t tid;
		int     retCode;

		Runable* run;

		ThreadPrivate()
			: tid(NULL), retCode(0), run(NULL)
		{
		}

		ThreadPrivate(Runable runable)
			: tid(NULL), retCode(0), run(new Runable(runable))
		{
		}

		~ThreadPrivate()
		{
			if (run)
			{
				delete run;
				run = NULL;
			}
		}

		friend class Thread;

		static void ThreadEntry(void* lpParam)
		{
			Thread* pThis = (Thread*)lpParam;
			if (pThis)
			{
				pThis->d->retCode = pThis->run();
			}
		}
	};

	void Thread::Sleep(unsigned int ms)
	{
		usleep(1000 * (ms));
	}

	TID Thread::CurrentThreadId()
	{
		return pthread_self();
	}

	Thread::Thread()
		: d(new ThreadPrivate())
	{
	}

	Thread::Thread(Runable runable)
		: d(new ThreadPrivate(runable))
	{
	}

	Thread::~Thread()
	{
		if (d)
		{
			Join();
			delete d;
			d = NULL;
		}
	}

	bool Thread::Start()
	{
		if (d->tid)
		{
			assert("Can not start a thread again.");
			return false;
		}

		return 0 == pthread_create(d->tid, NULL, &ThreadPrivate::ThreadEntry, this);
	}

	int Thread::Join()
	{
		if (d->tid)
		{
			void* result = NULL;
			if (pthread_join(d->tid, &result))
			{
				assert("pthread_join Can not join thread.");
			}
			pthread_detach(d->tid);
			d->tid = NULL;
		}
		return d->retCode;
	}

	TID Thread::ThreadId() const
	{
		return d->tid;
	}

	int Thread::Run()
	{
		if (d->run)
		{
			return (*d->run)();
		}
		return 0;
	}

}

#endif
