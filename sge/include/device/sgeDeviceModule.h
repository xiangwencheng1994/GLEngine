#pragma once

#include <core/sgeRuntimeModule.h>
#include <core/sgeIInputHandler.h>

namespace sge
{

    /**
     * The device module
     */
    class SGE_API DeviceModule : public IRuntimeModule
    {
    public:
        /**
         * Constructor
         */
        DeviceModule();

        /**
         * Destructor
         */
        ~DeviceModule();

        /**
         * Get enum type
         */
        ModuleType moduleType() const override final { return ModuleType::kModuleTypeDevice; }

        /**
         * Swap buffer
         */
        void swapBuffer();

        /**
         * Set the input handler
         */
        void setInputModule(IInputHandler* inputSystem);

        /**
         * Get the input handler
         */
        IInputHandler* getInputModule() const;

    public:
        int     initialize() override;
        void    finalize() override;
        void    tick() override;

    protected:
        friend class DeviceModulePrivate;
        DeviceModulePrivate* d;
    };

}

