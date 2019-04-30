#pragma once

#include <core/sgeMath.h>
#include <graphics/sgeGraphicsSystem.h>


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
        GpuBuffer(GraphicsSystem* mgr, size_t size, BufferPlace place, const void * data = 0)
            : _mgr(NULL)
            , _id(0)
            , _size(0)
        {
            ASSERT(mgr && size > 0);
            if (mgr && size)
            {
                GraphicsDevice* device = mgr->getDevice();
                ASSERT(device);
                _id = device->createBuffer(BufferType::VBO, size, data, place);
                if (_id)
                {
                    _size = (uint)size;
                    _mgr = mgr;
                }
            }
        }

        /**
         * Destructor
         */
        ~GpuBuffer()
        {
            release();
        }

        /**
         * Get the buffer id
         */
        NativeBufferId  getId() const { return _id; }

        /**
         * Check the buffer valid status
         */
        bool        isValid() const { return _id != InvalidBufferId; }

        /**
         * Get buffer type
         */
        BufferType  getType() const { return T; }

        /**
         * Get the buffer size
         */
        uint        getSize() const { return _size; }

        /**
         * Release the buffer
         */
        void        release()
        {
            if (_id)
            {
                ASSERT(_mgr && _size > 0);
                GraphicsDevice* device = _mgr->getDevice();
                ASSERT(device);
                device->destoryBuffer(_id);
                _mgr = NULL;
                _id = NULL;
                _size = 0;
            }
        }

        /**
         * Update data
         */
        void        updateData(size_t offset, size_t size, const void* data)
        {
            if (_id && data && size)
            {
                ASSERT(_mgr && _size >= offset + size);
                GraphicsDevice* device = _mgr->getDevice();
                ASSERT(device);
                device->updateBuffer(_id, offset, size, data);
            }
        }

        /**
         * Get buffer data
         */
        void        getData(void* outData, size_t size = 0, size_t offset = 0)
        {
            if (outData)
            {
                if (size == 0) size = _size - offset;
                ASSERT(size > 0 && _size >= offset + size);
                GraphicsDevice* device = _mgr->getDevice();
                ASSERT(device);
                device->getBufferData(_id, offset, outData, size);
            }
        }

    private:
        NativeBufferId      _id;
        uint                _size;
        GraphicsSystem*     _mgr;
    };


    using VetexBuffer = GpuBuffer<BufferType::VBO>;
    using IndexBuffer = GpuBuffer<BufferType::IBO>;

    using VBO = SharedPtr<VetexBuffer>;
    using IBO = SharedPtr<IndexBuffer>;

}
