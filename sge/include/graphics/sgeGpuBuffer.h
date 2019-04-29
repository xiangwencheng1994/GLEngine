#pragma once

#include <core/sgeMath.h>
#include <graphics/sgeGraphicsSystem.h>

namespace sge
{

    /**
     * Enum buffer type
     */
    enum BufferType
    {
        /**
         * vertex buffer type
         */
        VBO,

        /**
         * index buffer type
         */
        IBO,

        //TODO: more buffer types
    };

    /**
     * Enum buffer place
     */
    enum BufferPlace
    {
        /**
         * the buffer wanted place in cpu memory
         */
        NOCARE,

        /**
         * the buffer wanted place in gpu memory
         */
        GPU,

        /**
         * the buffer wanted place in agp memory
         */
        AGP
    };

    /**
     * The GPU buffer
     */
    class SGE_API GpuBuffer
    {
    public:
        virtual ~GpuBuffer() = 0;

        /**
         * Get buffer type
         */
        virtual BufferType  getType() const = 0;

    protected:
        GpuBuffer() = default;
    private:
        DISABLE_COPY(GpuBuffer)
    };
    
}
