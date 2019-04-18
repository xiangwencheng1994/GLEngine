#pragma once

#include <core/sgeDefs.h>

namespace sge
{
    class MutexPrivate;

    /**
     * Class Mutex
     */
    class SGE_CORE_API Mutex
    {
    public:

        /**
         * Constructor, create mutex
         */
        Mutex();

        /**
         * Destructor, destory mutex
         */
        ~Mutex();

        /**
         * Lock the mutex, if mutex is locked it will blocking thread and wait it unlocked.
         */
        void lock() const;

        /**
         * Unlock th mutex
         */
        void unlock() const;

        /**
         * Try lock the mutex
         * @return true if lock success, otherwise return false
         */
        bool tryLock() const;

    protected:
        MutexPrivate* d;
        DISABLE_COPY(Mutex)
    };

    /**
     * Class ScopeLock
     * Make a scope mutex lock in current scope.
     * lock immediately and unlock when destructing.
     */
    class ScopeLock
    {
    public:

        /**
         * Constructor, lock the mutex.
         */
        ScopeLock(const Mutex& mutex)
            : _mutex(mutex)
        {
            _mutex.lock();
        }

        /**
         * Destructor, unlock the mutex.
         */
        ~ScopeLock()
        {
            _mutex.unlock();
        }

    private:
        const Mutex&    _mutex;
        DISABLE_COPY(ScopeLock)
    };

}

