#pragma once

#include <core/sgeRuntimeModule.h>

#ifdef MODULE_GRAPHICS_EXPORTS
    #define SGE_GRAPHICS_API SGE_EXPORT
#else
    #define SGE_GRAPHICS_API SGE_IMPORT
#endif

namespace sge
{
    
    /**
     * The graphics module interface
     */
    class GraphicsSystem : public IRuntimeModule
    {
    public:
        
    };
    
    /**
     * Create graphics module object
     */
    SGE_GRAPHICS_API GraphicsSystem* newGraphicsSystem();

    /**
     * Destory graphics module object
     */
    SGE_GRAPHICS_API deleteGraphicsSystem(GraphicsSystem* module);

}