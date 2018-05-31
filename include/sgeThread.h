/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeThread.h
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

#ifndef SGE_THREAD_H
#define SGE_THREAD_H

#include <sge.h>

#include <sgeDelegate.h>

namespace sge
{
    class ThreadPrivate;

    typedef Delegate0<int>  Runable;

    typedef unsigned long TID;

    /**
     * Class Thread
     */
    class SGE_API Thread
    {
    public:

        /**
         * Make current thread sleep some times.
         * @param ms Sleep time base on milliseconds
         */
        static void Sleep(unsigned int ms);

		/**
		 * Get the current thread id.
		 */
		static TID	currentThreadId();

        /**
         * Constructor
         */
        Thread();

        /**
         * Constructor with a runable delegate
         * @param runable will called by run after thread started
         */
        Thread(Runable runable);

        /**
         * Destructor£¬will wait for thread exit
         */
        ~Thread();

        /**
         * Start this thread
         */
        bool start();

        /**
         * Wait for thread exit, if thread is finished it will return immediately
         * @return The run function result.
         */
        int join();

        /**
         * Get thread id, NULL if not started
         */
        TID threadId() const;

#ifdef _WIN32
        typedef void * HANDLE;

        /**
         * Get the Thread Handle, windows only
         */
        HANDLE handle() const;
#endif

        /**
         * The executable of this thread
         */
        virtual int run();
    protected:
        ThreadPrivate* d;

        friend class ThreadPrivate;
        DISABLE_COPY(Thread)
    };

}


#endif // !SGE_THREAD_H