#include <core/sgeApplication.h>
#include <core/sgeScene.h>
#include <core/sgeGUIRenderer.h>

class MyScene : public sge::Scene
{
public:
    virtual void onRenderUI(sge::Context& context) override
    {
        sge::GUIRenderer* renderer = context.guiRenderer();
        char    fpsStr[64];
        sprintf(fpsStr, "%3.0f", 1 / context.frameTime());
        renderer->setFont("default");
        renderer->setFontSize(24);
        renderer->setFillColor(sge::vec4f(1,0,0,1));
        renderer->drawText(20, 20, fpsStr);
    }
};

int main()
{
    MyScene* scene = new MyScene();
    sge::Application app(800, 600);
    app.loadScene(scene);
    app.run();
    return 0;
}