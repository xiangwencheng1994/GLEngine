#include <core/sgeThread.h>

#ifdef _WIN32

#include <Windows.h>

namespace sge
{

    class ThreadPrivate
    {
        TID     _tid;
        HANDLE  _handle;
        int     _retCode;

        Runable _run;

        ThreadPrivate()
            : _tid(NULL)
            , _handle(NULL)
            , _retCode(0)
        {
        }

        ThreadPrivate(Runable runable)
            : _tid(NULL)
            , _handle(NULL)
            , _retCode(0)
            , _run(runable)
        {
        }

        ~ThreadPrivate()
        {
        }

        friend class    Thread;

        static DWORD WINAPI ThreadEntry(LPVOID lpParam)
        {
            Thread* pThis   =   (Thread*)lpParam;
            if (pThis)
            {
                pThis->d->_retCode  =   pThis->run();
            }
            return 0;
        }
    };

    void Thread::sleep(unsigned int ms)
    {
        ::Sleep(ms);
    }

	TID Thread::getCurrentThreadId()
	{
		return  GetCurrentThreadId();
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
            join();
            delete  d;
            d   =   NULL;
        }
    }

    bool Thread::start()
    {
        if (d->_tid || d->_handle)
        {
            ASSERT("Can not start a thread again.");
            return  false;
        }
        
        d->_handle  =   ::CreateThread(NULL, 0, 
            &ThreadPrivate::ThreadEntry, this, 0, &d->_tid);
        return d->_handle != NULL;
    }

    int Thread::join()
    {
        if (d->_handle)
        {
            ::WaitForSingleObject(d->_handle, 0xFFFFFFFF);
            ::CloseHandle(d->_handle);
            d->_handle = NULL;
        }
        return d->_retCode;
    }

    TID Thread::getThreadId() const
    {
        return d->_tid;
    }

    HANDLE Thread::getHandle() const
    {
        return d->_handle;
    }

    int Thread::run()
    {
        return (d->_run)();
    }

}

#else

#include <pthread.h>
#include <unistd.h>

namespace sge
{

	class ThreadPrivate
	{
		pthread_t   _tid;
		int         _retCode;

		Runable     _run;

		ThreadPrivate()
			: _tid(NULL)
            , _retCode(0)
		{
		}

		ThreadPrivate(Runable runable)
			: _tid(NULL)
            , _retCode(0)
            , _run(runable)
		{
		}

		~ThreadPrivate()
		{
		}

		friend class Thread;

		static void* ThreadEntry(void* lpParam)
		{
			Thread* pThis   =   (Thread*)lpParam;
			if (pThis)
			{
				pThis->d->_retCode  =   pThis->run();
			}
			return  NULL;
		}
	};

	void Thread::sleep(unsigned int ms)
	{
		usleep(1000 * (ms));
	}

	TID Thread::getCurrentThreadId()
	{
		return  pthread_self();
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
			join();
			delete  d;
			d   =   NULL;
		}
	}

	bool Thread::start()
	{
		if (d->_tid)
		{
			ASSERT("Can not start a thread again.");
			return  false;
		}

		return  0 == pthread_create(&d->_tid, NULL, &ThreadPrivate::ThreadEntry, this);
	}

	int Thread::join()
	{
		if (d->_tid)
		{
			void*   result  =   NULL;
			if (pthread_join(d->_tid, &result))
			{
				ASSERT("pthread_join Can not join thread.");
			}
			pthread_detach(d->_tid);
			d->_tid =   NULL;
		}
		return  d->_retCode;
	}

	TID Thread::getThreadId() const
	{
		return  d->_tid;
	}

	int Thread::run()
	{
	    return (*d->_run)();
	}

}

#endif
