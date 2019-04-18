#pragma once

#include <core/sgeSubSystem.h>

namespace sge
{
    
    class IScene;

    class ISceneSystem : public ISubSystem
    {
    public:
        virtual int         loadScene(const char* scene_file) = 0;
        virtual IScene*     getSceneForRender() = 0;
        virtual IScene*     getCurrentScene() = 0;
    };
    
}