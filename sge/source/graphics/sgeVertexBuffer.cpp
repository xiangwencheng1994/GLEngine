#include <graphics/sgeVertexBuffer.h>
#include <graphics/sgeGraphicsSystem.h>

namespace sge
{

    VertexBuffer::VertexBuffer(GraphicsSystem * mgr, size_t size, void * data, BufferPlace place)
        : _mgr(NULL)
        , _id(0)
        , _size(0)
    {
        ASSERT(mgr && size > 0);
        if (mgr && size)
        {
            //TODO: _id = mgr->device.createVertexBuffer(size, data, place);
            if (_id)
            {
                _size = size;
                _mgr = mgr;
            }
        }
    }

    VertexBuffer::~VertexBuffer()
    {
    }


}
