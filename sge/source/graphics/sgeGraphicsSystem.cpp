#include <graphics/sgeGraphicsSystem.h>
#include <core/sgeLog.h>

#include "opengl/sgeOpenGL.h"

namespace sge
{

    class GraphicsSystemPrivate
    {
    public:
        
    };


    GraphicsSystem::GraphicsSystem()
        : d(new GraphicsSystemPrivate())
    {
    }

    GraphicsSystem::~GraphicsSystem()
    {
        delete d;
    }

    int GraphicsSystem::initialize()
    {
        if (! _device.initialize())
        {
            return -1;
        }
        return 0;
    }

    void GraphicsSystem::finalize()
    {
    }

    void GraphicsSystem::tick()
    {
        glClearColor(0, 0, 0, 1);

        glClear(GL_COLOR_BUFFER_BIT);
    }


}