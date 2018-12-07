#include <win32/sgePlatformNativeWin32.h>
#include <core/sgeLog.h>
#include <core/sgeApplication.h>
#include <core/sgeScene.h>

using namespace sge;

class MyScene : public Scene
{
    virtual bool OnLeftButtonUpEvent(const MouseButtonEvent& event) override
    {
        return Scene::OnLeftButtonUpEvent(event);
    }

    virtual void OnRender(Application* app) 
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        __super::OnRender(app);
    }

    virtual void Release()
    {
    }
};

int main()
{
    Application app;
    MyScene scene;
    app.LoadScene(&scene);
    app.Run();
    return 0;
}