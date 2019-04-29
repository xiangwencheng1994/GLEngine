#include <graphics/sgeGraphicsDevice.h>

#include "sgeOpenGL.h"

namespace sge
{
    static GLenum prefectVBOUsage(BufferPlace place)
    {
        GLenum usage = GL_STATIC_DRAW;
        switch (place)
        {
        case sge::NOCARE:
            usage = GL_DYNAMIC_COPY;
            break;
        case sge::GPU:
            usage = GL_STATIC_DRAW;
            break;
        case sge::AGP:
            usage = GL_DYNAMIC_DRAW;
            break;
        default:
            break;
        }
        return usage;
    }

    void* GraphicsDevice::createVertexBuffer(size_t size, void * data, BufferPlace place)
    {
        GLuint id, oldBind;
        glGenBuffers(1, &id);
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&oldBind);
        glBindBuffer(GL_VERTEX_ARRAY, id);
        glBufferData(GL_VERTEX_ARRAY, size, data, prefectVBOUsage(place));
        glBindBuffer(GL_VERTEX_ARRAY, oldBind);
        return (void*)id;
    }

}
