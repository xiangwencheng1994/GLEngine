#pragma once

#include <core/sgeRuntimeModule.h>
#include <input/sgeInputSystem.h>

namespace sge
{

    /**
     * The device module interface
     */
    class DeviceModule : public IRuntimeModule
    {
    public:
        ModuleType moduleType() const override final { return ModuleType::kModuleTypeDevice; }

        /**
         * Set the input handler
         */
        virtual void setInputModule(InputSystem* inputSystem) = 0;

        /**
         * Get the input handler
         */
        virtual InputSystem* getInputModule() const = 0;
    };
    
}

#ifdef MODULE_DEVICE_EXPORTS
#define SGE_DEVICE_API extern "C" SGE_EXPORT
#else
#define SGE_DEVICE_API extern "C" SGE_IMPORT
#endif

/**
 * Create device module object
 */
SGE_DEVICE_API sge::DeviceModule* newDeviceModule();

/**
 * Destory device module object
 */
SGE_DEVICE_API void deleteDeviceModule(sge::DeviceModule* object);