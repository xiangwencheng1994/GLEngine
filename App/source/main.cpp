#include <win32/sgePlatformNativeWin32.h>
#include <core/sgeLog.h>
#include <core/sgeApplication.h>
#include <core/sgeScene.h>

using namespace sge;

class MyScene : public Scene
{
    virtual void OnLoad(Application* app) {}

    virtual void OnUnLoad(Application* app) {}

    virtual void OnRender(Application* app) 
    {
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

int main()
{
    Application app;
    app.LoadScene(new MyScene());
    app.Run();
    return 0;
}