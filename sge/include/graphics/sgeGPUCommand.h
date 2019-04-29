#pragma once

#include <core/sgeDefs.h>

namespace sge
{
    
    class GraphicsSystem;

    class SGE_API GPUCommand
    {
    public:
        virtual void doTask(GraphicsSystem* graphicsDevice) = 0;

    private:
        DISABLE_COPY(GPUCommand)
    };

}
