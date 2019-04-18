#pragma once

#ifdef __cplusplus

#include <core/sgeDefs.h>

namespace sge 
{

    /**
     * Class Log is a tool to record logs
     */
    class SGE_CORE_API Log
    {
    public:
        enum    Level
        {
            Debug,
            Info,
            Warn,
            Error,
            User
        };

        typedef void(*Output)(Level lv, char *msg);

    public:
        /**
         * The real output function pointer.
         * @note You can redistribution this pointer to yours
         */
        static Output   _output;

        /**
         * This is the default function for output
         * It just format string and print to stdout, 
         * and extra OutputDebugString for win32 
         */
        static void defaultOutput(Level lv, char *msg);

        /**
         * Output a debug log with string format
         * @param fmt The format
         * @... The Var for format string
         */
        static void debug(const char* fmt, ...);

        /**
         * Output a info log with string format
         * @param fmt The format
         * @... The Var for format string
         */
        static void info(const char* fmt, ...);

        /**
         * Output a warn log with string format
         * @param fmt The format
         * @... The Var for format string
         */
        static void warn(const char* fmt, ...);

        /**
         * Output a error log with string format
         * @param fmt The format
         * @... The Var for format string
         */
        static void error(const char* fmt, ...);
    };

} // !namespace

#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


    /**
     * Output a debug log with string format
     * @param fmt The format
     * @... The Var for format string
     */
    void    LogDebug(const char* fmt, ...);

    /**
     * Output a info log with string format
     * @param fmt The format
     * @... The Var for format string
     */
    void    LogInfo(const char* fmt, ...);

    /**
     * Output a warn log with string format
     * @param fmt The format
     * @... The Var for format string
     */
    void    LogWarn(const char* fmt, ...);

    /**
     * Output a error log with string format
     * @param fmt The format
     * @... The Var for format string
     */
    void    LogError(const char* fmt, ...);


#ifdef __cplusplus
}
#endif // __cplusplus

