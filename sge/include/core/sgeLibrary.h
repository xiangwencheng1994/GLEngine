#pragma once

#include <core/sgeDefs.h>

#ifdef SGE_WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#else
#include <dlfcn.h>
typedef void*   HMODULE;
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

namespace sge
{

    /**
     *  Class for load dynamic library
     */
    class SGE_CORE_API sgeLibrary
    {
    public:
        sgeLibrary(const char* file);
        ~sgeLibrary();

        /**
         * Load a dynamic library
         * @return NULL if failed
         */
        static sgeLibrary* load(const char* file);
        
        /**
         *  Get library path
         */
        const char* getPathName() { return _path.c_str(); }

        /**
         *  Get module handule
         */
        HMODULE  getModule() { return _module; }

        /**
         *  Check is loaded
         */
        bool     isLoaded() { return getModule() != 0; }

        /**
         *  Unload the module
         */
        bool            unload();

        /**
         *  find function in module
         */
        void*           getFunction(const char* funName);

        /**
         *  release module
         */
        void            release();
    private:
        sgeString       _path;
        HMODULE         _module;
        bool            _needDelete;

        DISABLE_COPY(sgeLibrary)
    };

}

