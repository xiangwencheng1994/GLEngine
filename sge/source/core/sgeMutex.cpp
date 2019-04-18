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
