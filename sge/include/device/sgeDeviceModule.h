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
        /**
         * Set the input handler
         */
        virtual void setInputModule(InputSystem* inputSystem) = 0;

        /**
         * Get the input handler
         */
        virtual InputSystem* getInputModule() const = 0;
    };
    
    #ifdef MODULE_DEVICE_EXPORTS
    #define SGE_DEVICE_API SGE_EXPORT
    #else
    #define SGE_DEVICE_API SGE_IMPORT
    #endif

    /**
     * Create device module object
     */
    SGE_DEVICE_API DeviceModule* createDeviceModule();

    /**
     * Destory device module object
     */
    SGE_DEVICE_API void destoryDeviceModule(DeviceModule* object);

}
