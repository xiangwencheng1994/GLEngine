#pragma once

#include <core/sgeRuntimeModule.h>

namespace sge
{

    /**
     * Class ModuleLoader
     */
    class SGE_CORE_API RuntimeModuleManager : public IRuntimeModuleManager
    {
    public:
        ModuleLoader();
        virtual ~ModuleLoader();
        virtual void loadModule(const char* lib);
        virtual bool registerModule(IRuntimeModule* module) = 0;
    }

}