#pragma once

#include <core/sgeDefs.h>

namespace sge
{
    class   SemaphorePrivate;

    /**
     * Class Semaphore
     */
    class SGE_CORE_API Semaphore
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
        bool    wait(unsigned long ms = 0xFFFFFFFF);

        /**
         * Post semaphore
         * @param number The semaphore count.
         */
        bool    set(long number = 1);

    protected:
        SemaphorePrivate*   d;
        DISABLE_COPY(Semaphore)
    };


}

