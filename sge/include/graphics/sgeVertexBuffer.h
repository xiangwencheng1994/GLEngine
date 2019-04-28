#pragma once

#include <graphics/sgeGpuBuffer.h>
#include <graphics/sgeGraphicsSystem.h>

namespace sge
{
    
    /**
     * The vertex buffer
     */
    class VertexBuffer : public GpuBuffer
    {
    public:
        /**
         * Get the buffer id
         */
        uint64_t    getId() const final { _id; }

        /**
         * Get buffer type
         */
        BufferType getType() const final { return BufferType::VBO; }

        /**
         * Get the buffer size
         */
        uint    getSize() const final { return _size; }
    protected:
        VertexBuffer() = default;
        uint64_t        _id;
        uint            _size;
        GraphicsSystem* _mgr;
    };

    typedef sgeSharedPtr<VertexBuffer> VBO;

}
