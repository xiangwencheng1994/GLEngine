#pragma once

#include <core/sgeDefs.h>

namespace sge
{

    class   TimerPrivate;

    /**
     * Class Timer for get elapsed times
     */
    class SGE_API Timer
    {
    public:

        /**
         * Constructor
         */
        Timer();

        /**
         * Destructor
         */
        ~Timer();

        /**
         * Get and update the elapsed times after last update time
         */
        double  elapsed();

    private:
        TimerPrivate*   d;
        DISABLE_COPY(Timer)
    };

} // !namespace

