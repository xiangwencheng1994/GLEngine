#include <core/sgeTimer.h>

#ifdef SGE_WIN32

#include <Windows.h>
#include <core/sgeLog.h>

namespace sge 
{

    class   TimerPrivate
    {
        double      _liQPF;
        LONGLONG    _liLastTime;
        friend class Timer;
    };


    Timer::Timer()
        : d(new TimerPrivate())
    {
        LARGE_INTEGER   cpuQPF;
        bool    ret =   QueryPerformanceFrequency(&cpuQPF);
        if (ret)
        {
            d->_liQPF   =   (double)cpuQPF.QuadPart;
        }
        else
        {
            Log::error("Timer can not work, becase QueryPerformanceFrequency failed.");
        }
    }

    Timer::~Timer()
    {
        if (d)
        {
            delete  d;
            d   =   NULL;
        }
    }


    inline double Timer::elapsed()
    {
        LARGE_INTEGER nowTime;
        QueryPerformanceCounter(&nowTime);
        double  elapsed =   (nowTime.QuadPart - d->_liLastTime) / d->_liQPF;
        d->_liLastTime  =   nowTime.QuadPart;
        return  elapsed;
    }

}

#else

#include <sys/time.h>

namespace sge
{

	class   TimerPrivate
	{
		struct timeval  _time;
		friend class    Timer;
	};


	Timer::Timer()
		: d(new TimerPrivate())
	{
	}

	Timer::~Timer()
	{
		if (d)
		{
			delete  d;
			d   =   NULL;
		}
	}

	double Timer::elapsed()
	{
		timeval current;
		gettimeofday(&current, NULL);
		int offsev  =   current.tv_sec - d->_time.tv_sec;
		int offusev =   current.tv_usec - d->_time.tv_usec;
		double  elapsed =   ((offsev * 1000000) + offusev) * 0.0000001;
		d->_time    =   current;
		return  elapsed;
	}

}

#endif
