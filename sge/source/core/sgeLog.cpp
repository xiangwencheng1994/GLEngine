#include <core/sgeLog.h>

#include <time.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef WIN32
#include <Windows.h>
#endif // WIN32


namespace sge 
{
    // format string by args
    #define FORMAT(out, fmtStr) char out[512] = { 0 };          \
                            va_list __vl;                       \
                            va_start(__vl, fmtStr);             \
                            vsnprintf(out, 512, fmtStr, __vl);  \
                            va_end(__vl)

    Log::Output Log::_output    =   Log::defaultOutput;

    void Log::defaultOutput(Log::Level lv, char *msg)
    {
        char    buf[4096];
        const char* fmt[5]  = 
        {
            "[D]:%s\n",
            "[I]:%s\n",
            "[W]:%s\n",
            "[E]:%s\n",
            "[U]:%s\n"
        };
        sprintf(buf, fmt[lv], msg);
#if _WIN32 && _DEBUG
        OutputDebugStringA(buf);
#endif
        printf(buf);
    }

    void Log::debug(const char* fmt, ...)
    {
        FORMAT(strBuffer, fmt);
        if (_output) (*_output)(Log::Debug, strBuffer);
    }

    void Log::info(const char* fmt, ...)
    {
        FORMAT(strBuffer, fmt);
        if (_output) (*_output)(Log::Info, strBuffer);
    }

    void Log::warn(const char* fmt, ...)
    {
        FORMAT(strBuffer, fmt);
        if (_output) (*_output)(Log::Warn, strBuffer);
    }

    void Log::error(const char* fmt, ...)
    {
        FORMAT(strBuffer, fmt);
        if (_output) (*_output)(Log::Error, strBuffer);
    }

}



#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    void sgeLogDebug(const char* fmt, ...)
    {
        FORMAT(strBuffer, fmt);
        if (sge::Log::_output) (*sge::Log::_output)(sge::Log::Debug, strBuffer);
    }

    /**
     * Output a info log with string format
     * @param fmt The format
     * @... The Var for format string
     */
    void sgeLogInfo(const char* fmt, ...)
    {
        FORMAT(strBuffer, fmt);
        if (sge::Log::_output) (*sge::Log::_output)(sge::Log::Info, strBuffer);
    }

    /**
     * Output a warn log with string format
     * @param fmt The format
     * @... The Var for format string
     */
    void sgeLogWarn(const char* fmt, ...)
    {
        FORMAT(strBuffer, fmt);
        if (sge::Log::_output) (*sge::Log::_output)(sge::Log::Warn, strBuffer);
    }

    /**
     * Output a error log with string format
     * @param fmt The format
     * @... The Var for format string
     */
    void sgeLogError(const char* fmt, ...)
    {
        FORMAT(strBuffer, fmt);
        if (sge::Log::_output) (*sge::Log::_output)(sge::Log::Error, strBuffer);
    }


#ifdef __cplusplus
}
#endif // __cplusplus