#include <win32/sgePlatformNativeWin32.h>
#include <core/sgeLog.h>
#include <core/sgeScene.h>
#include <core/sgeApplication.h>
#include <core/sgeRenderer.h>
#include <ui/sgeLabel.h>
#include <ui/sgeLinearLayout.h>

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
    MyScene(Application* app): Scene(app) {}

    virtual void onLoad() override
    {
        Scene::onLoad();

        ui::LinearLayout* group = new ui::LinearLayout(getApplicaton());
        setRootView(RefPtr<ui::View>(group));
        group->setLayoutParams(RefPtr<ui::LayoutParams>(new ui::LayoutParams(MATCH_PARENT, WRAP_CONTENT)));


        ui::Label* topleft = new ui::Label(getApplicaton());
        group->addChild(RefPtr<ui::View>(topleft));
        topleft->setLayoutParams(RefPtr<ui::LayoutParams>(new ui::LinearLayoutParams(200, 200)));
        topleft->setText("[Size:200,200]\n[TopLeft]");
        topleft->setAlignment(Alignment::TopLeft);
        topleft->setFontColor(float4(1, 0, 0, 1));
        topleft->setMuiltLine(true);
        
        ui::Label* topright = new ui::Label(getApplicaton());
        group->addChild(RefPtr<ui::View>(topright));
        topright->setLayoutParams(RefPtr<ui::LayoutParams>(new ui::LinearLayoutParams(MATCH_PARENT, 500, 2.0f)));
        topright->setText("[Size:MatchParent,500]\n[BottomCenter]\n[Weight:2.0]");
        topright->setAlignment(Alignment::BottomCenter);
        topright->setFontColor(float4(0, 0, 1, 1));
        topright->setMuiltLine(true);

        ui::Label* middlecenter = new ui::Label(getApplicaton());
        group->addChild(RefPtr<ui::View>(middlecenter));
        middlecenter->setLayoutParams(RefPtr<ui::LayoutParams>(new ui::LinearLayoutParams(MATCH_PARENT, MATCH_PARENT, 1.0f)));
        middlecenter->setText("[Size:MatchParent,MatchParent]\n[MiddleCenter]\n[Weight:1.0]");
        middlecenter->setAlignment(Alignment::MiddleCenter);
        middlecenter->setFontColor(float4(1, 0, 1, 1));
        middlecenter->setFontSize(48);
        middlecenter->setMuiltLine(true);


        ui::Label* topcenter = new ui::Label(getApplicaton());
        group->addChild(RefPtr<ui::View>(topcenter));
        topcenter->setLayoutParams(RefPtr<ui::LayoutParams>(new ui::LinearLayoutParams(200, 300)));
        topcenter->setText("[Size:200,300]\n[MiddleLeft]");
        topcenter->setAlignment(Alignment::MiddleLeft);
        topcenter->setFontColor(float4(0, 1, 0, 1));
        topcenter->setMuiltLine(true);
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