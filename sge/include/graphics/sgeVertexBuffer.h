#pragma once

#include <graphics/sgeGpuBuffer.h>

namespace sge
{
    class GraphicsSystem;

    /**
     * The vertex buffer
     */
    class SGE_API VertexBuffer : public GpuBuffer
    {
    public:
        /**
         * Constructor
         * @param mgr The device
         */
        VertexBuffer(GraphicsSystem* mgr, size_t size, void * data, BufferPlace place);

        /**
         * Destructor
         */
        ~VertexBuffer();

        /**
         * Get the buffer id
         */
        void*       getId() const { return _id; }

        /**
         * Get buffer type
         */
        BufferType getType() const { return BufferType::VBO; }

        /**
         * Get the buffer size
         */
        uint    getSize() const { return _size; }
    protected:
        void*           _id;
        uint            _size;
        GraphicsSystem* _mgr;
    };

}
