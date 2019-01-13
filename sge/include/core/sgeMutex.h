/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeMutex.h
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

#ifndef SGE_MUTEX_H
#define SGE_MUTEX_H

#include <core/sgePlatform.h>

namespace sge
{
    class MutexPrivate;

    /**
     * Class Mutex
     */
    class SGE_API Mutex
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
            : mMutex(mutex)
        {
            mMutex.lock();
        }

        /**
         * Destructor, unlock the mutex.
         */
        ~ScopeLock()
        {
            mMutex.unlock();
        }

    private:
        const Mutex& mMutex;
        DISABLE_COPY(ScopeLock)
    };

}


#endif //! SGE_MUTEX_H