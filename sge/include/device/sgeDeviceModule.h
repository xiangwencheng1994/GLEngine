#pragma once

#include <core/sgeRuntimeModule.h>
#include <input/sgeInputSystem.h>

#ifdef MODULE_DEVICE_EXPORTS
    #define SGE_DEVICE_API SGE_EXPORT
#else
    #define SGE_DEVICE_API SGE_IMPORT
#endif

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
         * Swap buffer
         */
        virtual void swapBuffer() = 0;

        /**
         * Set the input handler
         */
        virtual void setInputModule(InputSystem* inputSystem) = 0;

        /**
         * Get the input handler
         */
        virtual InputSystem* getInputModule() const = 0;
    };


    /**
     * Create device module object
     */
    SGE_DEVICE_API DeviceModule* newDeviceModule();

    /**
     * Destory device module object
     */
    SGE_DEVICE_API void deleteDeviceModule(DeviceModule* object);

}

