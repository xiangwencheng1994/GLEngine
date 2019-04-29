#pragma once

#include <core/sgeDefs.h>


namespace sge
{
    
    /**
     * Enum module types
     */
    enum ModuleType
    {
        kModuleTypeDevice, 
        kModuleTypeInput, 
        kModuleTypeAsset, 
        kModuleTypeScene, 
        kModuleTypePhysics, 
        kModuleTypeAnimation, 
        kModuleTypeGraphics, 
        kModuleTypeAudio, 
        kModuleTypeGameLogic, 
    };

    /**
     * Interface IRuntimeModule
     */
    class SGE_API IRuntimeModule
    {
    public:
        virtual ~IRuntimeModule() = default;

        /**
         * The module type
         */
        virtual ModuleType moduleType() const = 0;

        /**
         * Initialize system
         */
        virtual int initialize() = 0;

        /**
         * Finalize system
         */
        virtual void finalize() = 0;

        /**
         * Do a tick
         */
        virtual void tick() = 0;

    protected:
        IRuntimeModule() = default;
        DISABLE_COPY(IRuntimeModule)
    };

}
