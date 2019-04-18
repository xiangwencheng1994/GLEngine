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
        d->hSem =   ::CreateSemaphore(0, lMax, lInit, 0);
        ASSERT(d->hSem);
    }

    Semaphore::~Semaphore()
    {
        if (d)
        {
            if (d->hSem)
            {
                ::CloseHandle(d->hSem);
                d->hSem =   0;
            }
            delete  d;
            d   =   NULL;
        }
    }

    inline bool Semaphore::wait(unsigned long ms)
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

    inline bool Semaphore::set(long number)
    {
        return  TRUE == ::ReleaseSemaphore(d->hSem, number, 0);
    }

}

#else

#include <semaphore.h>
#include <time.h>
#include <sys/time.h>

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
		int ret =   sem_init(&d->hSem, 0, lInit);
		ASSERT(ret == 0);
	}

	Semaphore::~Semaphore()
	{
		if (d)
		{
			sem_destroy(&d->hSem);
			delete  d;
			d   =   NULL;
		}
	}

    inline bool Semaphore::wait(unsigned long ms)
	{
		struct timespec abstime;
		struct timeval  tv;
		gettimeofday(&tv, 0);
		abstime.tv_sec  =   tv.tv_sec + ms / 1000;
		abstime.tv_nsec =   tv.tv_usec * 1000 + (ms % 1000) * 1000000;
		if (abstime.tv_nsec >= 10000000000)
		{
			abstime.tv_nsec -= 10000000000;
            ++abstime.tv_sec;
		}
		return  0 == sem_timedwait(&d->hSem, &abstime);
	}

    inline bool Semaphore::set(long number)
	{
		bool    ret =   true;
		for (long i = 0; i < number; ++i)
		{
			if (0 != sem_post(&d->hSem))
			{
				ret =   false;
				break;
			}
		}
		return  ret;
	}

}

#endif