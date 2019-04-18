#pragma once

#include <core/sgeDefs.h>

#include <core/sgeDelegate.h>

namespace sge
{
    class   ThreadPrivate;

    typedef Delegate0<int>  Runable;

    typedef unsigned long   TID;

    /**
     * Class Thread
     */
    class SGE_CORE_API Thread
    {
    public:

        /**
         * Make current thread sleep some times.
         * @param ms Sleep time base on milliseconds
         */
        static void sleep(unsigned int ms);

		/**
		 * Get the current thread id.
		 */
		static TID  getCurrentThreadId();

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
         * Destructor, will wait for thread exit
         */
        ~Thread();

        /**
         * Start this thread
         */
        bool    start();

        /**
         * Wait for thread exit, if thread is finished it will return immediately
         * @return The run function result.
         */
        int     join();

        /**
         * Get thread id, NULL if not started
         */
        TID     getThreadId() const;

#ifdef _WIN32
        typedef void *  HANDLE;

        /**
         * Get the Thread Handle, windows only
         */
        HANDLE  getHandle() const;
#endif

        /**
         * The executable of this thread
         */
        virtual int run();
    protected:
        ThreadPrivate*  d;

        friend class    ThreadPrivate;
        DISABLE_COPY(Thread)
    };

}

