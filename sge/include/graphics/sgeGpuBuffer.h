#pragma once

#include <graphics/sgeGraphicsDevice.h>

namespace sge
{
    
    /**
     * The GPU buffer
     */
    template<BufferType T>
    class GpuBuffer
    {
    public:
        /**
         * Constructor
         * @param mgr The graphics system
         * @param size The size of buffer, must bigger than 0
         * @param place The place wanted
         * @param data The initialize data
         */
        GpuBuffer(GraphicsDevice& device, size_t size, BufferPlace place, const void * data = 0)
            : _device(device)
            , _id(sge::kInvalidBufferId)
            , _size(0)
        {
            ASSERT(size > 0);
            _id = device.createBuffer(getType(), size, data, place);
            if (isValid())
            {
                _size = (uint)size;
            }
        }

        /**
         * Destructor
         */
        ~GpuBuffer()
        {
            if (isValid())
            {
                ASSERT(_size > 0);
                _device.destoryBuffer(_id);
                _id = NULL;
                _size = 0;
            }
        }

        /**
         * Get the buffer id
         */
        NativeBufferId  getId() const { return _id; }

        /**
         * Check the buffer valid status
         */
        bool        isValid() const { return _id != sge::kInvalidBufferId; }

        /**
         * Get buffer type
         */
        BufferType  getType() const { return T; }

        /**
         * Get the buffer size
         */
        size_t      getSize() const { return _size; }

        /**
         * Update data
         */
        void        updateData(size_t offset, size_t size, const void* data)
        {
            if (isValid() && data && size)
            {
                ASSERT(_size >= offset + size);
                _device.updateBuffer(_id, offset, size, data);
            }
        }

        /**
         * Get buffer data
         */
        void        getData(void* outData, size_t size = 0, size_t offset = 0)
        {
            if (isValid() && outData)
            {
                if (size == 0) size = _size - offset;
                ASSERT(size > 0 && _size >= offset + size);
                _device.getBufferData(_id, offset, outData, size);
            }
        }

    private:
        NativeBufferId      _id;
        size_t              _size;
        GraphicsDevice&     _device;
    };


    using VetexBuffer = GpuBuffer<BufferType::kVertexBufferType>;
    using IndexBuffer = GpuBuffer<BufferType::kIndexBufferType>;

}
