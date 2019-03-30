#include <core/sgeApplication.h>
#include <core/sgeScene.h>

class MyScene : public sge::Scene
{

};

int main()
{
    sge::Scene* scene = new sge::Scene();
    sge::Application app(800, 600);
    app.loadScene(scene);
    app.run();
    return 0;
}