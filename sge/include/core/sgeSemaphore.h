/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeSemaphore.h
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

#ifndef SGE_SEMAPHORE_H
#define SGE_SEMAPHORE_H

#include <core/sgePlatform.h>

namespace sge
{
    class SemaphorePrivate;

    /**
     * Class Semaphore
     */
    class SGE_API  Semaphore
    {
    public:
        /**
         * Constructor
         * @param lInit The init semaphore count
         * @param lMax The max semaphore count, pthread(linux) is unused.
         */
        Semaphore(long lInit = 1, long lMax = 0x7FFFFFFF);
        
        /**
         * Destructor
         */
        ~Semaphore();

        /**
         * Wait semaphore for some time.
         * @param ms Time to wait, based on milliseconds
         * @return true if get semaphore success, return false when faild or timeout
         */
        bool wait(unsigned long ms = 0xFFFFFFFF);

        /**
         * Post semaphore
         * @param number The semaphore count.
         */
        bool set(long number = 1);

    protected:
        SemaphorePrivate* d;
        DISABLE_COPY(Semaphore)
    };


}

#endif //! SGE_SEMAPHORE_H