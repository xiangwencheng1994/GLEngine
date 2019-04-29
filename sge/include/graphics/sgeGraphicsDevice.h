#pragma once

#include <core/sgeDefs.h>
#include <graphics/sgeGpuBuffer.h>

namespace sge
{

    /**
     * Class GraphicsDevice, the graphics interface
     */
    class SGE_API GraphicsDevice
    {
    public:
        /**
         * Create vertex buffer
         */
        void* createVertexBuffer(size_t size, void* data, BufferPlace place);

    };

}
