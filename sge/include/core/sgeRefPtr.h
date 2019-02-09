/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeRefPtr.h
 * date: 2019/01/13
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

#ifndef SGE_REF_PTR_H
#define SGE_REF_PTR_H

#include <core/sgePlatform.h>
#include <core/sgeLog.h>
#include <memory>

namespace sge
{

    /**
     * Class RefPtr for manage referenced ptr
     * The managed ptr will deleted on lost last reference
     */
    template<class T>
    class RefPtr
    {
    public:
        /**
         * Constructor with a pointer created by 'new' method
         */
        explicit RefPtr(T* ptr = NULL)
            : mPtr(ptr)
            , mRefCount(ptr ? new size_t(1) : NULL)
        {
        }

        /**
         * Destructor, decrease the reference count and delete ptr if count equal zero
         */
        ~RefPtr()
        {
            if (mRefCount && --(*mRefCount) == 0)
            {
                ASSERT(mPtr);
                delete mPtr;
                delete mRefCount;
                mPtr = NULL;
                mRefCount = NULL;
            }
        }

        /**
         * Copy constructor
         */
        RefPtr(const RefPtr<T> &orig)
        {
            mPtr = orig.mPtr;
            mRefCount = orig.mRefCount;
            if(mRefCount) ++(*mRefCount);
        }

        /**
         * Set form other RefPtr object
         */
        RefPtr<T>& operator=(const RefPtr<T> &rhs)
        {
            if (rhs.mRefCount) ++(*rhs.mRefCount);
            if (mRefCount && --(*mRefCount) == 0)
            {
                ASSERT(mPtr);
                delete mPtr;
                delete mRefCount;
            }
            mPtr = rhs.mPtr;
            mRefCount = rhs.mRefCount;
            return *this;
        }

        /**
         * Swap pointer with other object
         */
        void swap(RefPtr<T> &rhs)
        {
            T* myPtr = mPtr;
            size_t* myRefCount = mRefCount;
            mPtr = rhs.mPtr;
            mRefCount = rhs.mRefCount;
            rhs.mPtr = myPtr;
            rhs.mRefCount = myRefCount;
        }

        /**
         * Reset this object
         */
        void reset() { swap(RefPtr<T>(NULL)); }

        /**
         * Get the pointer
         * @note you should not delete the pointer
         */
        T* get() const { return mPtr; }
        T& operator*() const { return *get(); }
        T* operator->() const { return get(); }

        /**
         * Compare the pointer
         * @param rhs The right hand side object
         * @return true if same with rhs
         */
        bool operator==(const RefPtr<T> &rhs) const { return mPtr == rhs.mPtr; }
    private:
        T*      mPtr;
        size_t* mRefCount;
    };

}

#endif // !SGE_REF_PTR_H
