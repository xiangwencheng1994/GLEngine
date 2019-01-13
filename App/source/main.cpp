#include <win32/sgePlatformNativeWin32.h>
#include <core/sgeLog.h>
#include <core/sgeScene.h>
#include <core/sgeApplication.h>
#include <core/sgeRenderer.h>
#include <ui/sgeLabel.h>
#include <ui/sgeViewGroup.h>

using namespace sge;

char*   asiccToUtf8(const char* utf8)
{
    int len = ::MultiByteToWideChar(CP_ACP, 0, utf8, -1, NULL, 0);
    if (len == 0)
        return "";

    wchar_t     unicode[1024] = { 0 };
    ::MultiByteToWideChar(CP_ACP, 0, utf8, -1, unicode, len);

    static  char    szAs[1024] = { 0 };
    memset(szAs, 0, sizeof(szAs));

    WideCharToMultiByte(CP_UTF8, 0, unicode, (int)wcslen(unicode), szAs, sizeof(szAs), 0, 0);

    return szAs;
}

class MyScene : public Scene
{
public:

public:
    MyScene(Application* app): Scene(app) {}

    virtual void onLoad() override
    {
        Scene::onLoad();

        ui::ViewGroup* group = new ui::ViewGroup(getApplicaton());
        setRootView(RefPtr<ui::View>(group));

        group->setLayoutParams(RefPtr<ui::LayoutParams>(new ui::LayoutParams(FILL_PARENT, 500)));

        ui::Label* label = new ui::Label(getApplicaton());
        label->setLayoutParams(RefPtr<ui::LayoutParams>(new ui::LayoutParams(FILL_PARENT, WRAP_CONTENT)));
        label->setText("%123#$&*?\n%123#$&*?\n%123#$&*?");
        label->setAlignment(Alignment::TopRight);
        label->setMuiltLine(true);
        group->addChild(RefPtr<ui::View>(label));

        ui::Label* label2 = new ui::Label(getApplicaton());
        label2->setLayoutParams(RefPtr<ui::LayoutParams>(new ui::LayoutParams(WRAP_CONTENT, 300)));
        label2->setAlignment(Alignment::BottomLeft);
        label2->setText("%ABCDEFGHIJKLMNOPQRSTUVWXYZ#$&*?");
        group->addChild(RefPtr<ui::View>(label2));
    }

    virtual void OnRenderModel() 
    {
    }

    virtual void Release()
    {
    }
};

int main()
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG
    
    Application app;
    MyScene scene(&app);
    app.loadScene(&scene);
    app.run();
    return 0;
}