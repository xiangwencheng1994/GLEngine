#pragma once

#include <core/sgeRuntimeModule.h>
#include <graphics/sgeGraphicsDevice.h>

namespace sge
{

    /**
     * The graphics module interface
     */
    class SGE_API GraphicsSystem : public IRuntimeModule
    {
    public:
        /**
         * Constructor
         */
        GraphicsSystem();

        /**
         * Destructor
         */
        ~GraphicsSystem();

        /**
         * Get the graphics device
         */
        GraphicsDevice& getDevice() { return _device; }

    public:
        /**
         * The module type
         */
        ModuleType moduleType() const { return ModuleType::kModuleTypeGraphics; }

        /**
         * Initialize system
         */
        int initialize();

        /**
         * Finalize system
         */
        void finalize();

        /**
         * Do a tick
         */
        void tick();

    protected:
        friend class GraphicsSystemPrivate;
        GraphicsDevice  _device;

        GraphicsSystemPrivate*  d;
        DISABLE_COPY(GraphicsSystem)
    };

}