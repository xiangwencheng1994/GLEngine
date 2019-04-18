#include <core/sgeLibrary.h>
#include <string.h>

namespace sge
{

    sgeLibrary::sgeLibrary(const char* file)
        : _module(NULL)
        , _needDelete(false)
        , _path(file)
    {
#ifdef SGE_WIN32
        _module =   LoadLibraryA(file);
#else
        _module =   dlopen(file, RTLD_NOW);
#endif
    }

    sgeLibrary::~sgeLibrary()
    {
        unload();
    }

    sgeLibrary* sgeLibrary::load(const char* file)
    {
        sgeLibrary* lib =   new sgeLibrary(file);
        lib->_needDelete    =   true;
        if (! lib->isLoaded())
        {
            lib->release();
            lib =   NULL;
        }
        return  lib;
    }

    bool sgeLibrary::unload()
    {
        bool    ret =   true;
        if (_module)
        {            
#ifdef SGE_WIN32
            ret =   (TRUE == FreeLibrary(_module));
#else
            dlclose(_module); //TODO: check return            
#endif
            _module =   NULL;
        }
        return  ret;
    }

    void* sgeLibrary::getFunction(const char* funName)
    {
        if (NULL == _module)
            return NULL;

#ifdef SGE_WIN32
        return  GetProcAddress(_module, funName);
#else
        return  dlsym(_module, funName);
#endif
    }

    void sgeLibrary::release()
    {
        if (_needDelete)
        {
            delete  this;
        }
    }

}