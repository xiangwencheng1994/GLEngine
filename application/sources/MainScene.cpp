#include "MainScene.h"
#include <sgeLog.h>
#include <sgeGLX.h>

#include <imgui/imgui.h>

using namespace sge;

#define STR(x)  _GlobalResources.GetStr(x)

MainScene::MainScene()
    : _Camera(vec3f(10, 10, 10), vec3f(-1, -1, -1))
    , _BgColor(0.1f, 0.1f, 0.1f)
    , _SceneInfor(false)
    , _ModelManger("mesh/")
    , _GlobalResources(this)
{
    SetTitle("3D Builder ++");

    std::fill(_KeyMap, _KeyMap + 256, false);
}

MainScene::~MainScene()
{
}

void MainScene::OnCreate()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowBorderSize = 0;
    ImGuiIO& io = ImGui::GetIO();
    io.FontDefault = io.Fonts->AddFontFromFileTTF("font/YaHei.Consolas.ttf", 28.0f);

    GLX::LogGLVersion();
    
    if (!_GlobalResources.Init())
        Log::error("GlobalResources init failed");
    
    if (!_Ground.Create())
        Log::error("Create Ground failed");
    
    if (!_ModelManger.Create())
        Log::error("Create ModelManger failed");


    _ModelManger.Reserve(1000 /*00*/);
    for (size_t i = 0; i < 1000 /*00*/; i++)
    {
        uint instId = _ModelManger.AddInstance(0);
        vec3f vt = vec3f((rand() % 200) / 10.0f - 10, (rand() % 200) / 10.0f - 10, (rand() % 200) / 10.0f - 10);
        vec3f vr = vec3f(rand() % 1000 + 1, rand() % 1000, rand() % 1000);
        vec3f vs = vec3f((rand() % 10 + 2) * 0.05, (rand() % 10 + 2) * 0.05, (rand() % 10 + 2) * 0.05);
        vr.normalize();
        mat4f instLocal = mat4f::createTranslation(vt)
            * mat4f::createRotationAroundAxis(rand() % 360, vr)
            * mat4f::createScale(vs.x, vs.y, vs.z);
        _ModelManger.SetInstanceLocal(instId, instLocal);
        _ModelManger.SetInstanceMatId(instId, 0);
    }
    this->GLContext()->EnableVSYNC(false);
}

void MainScene::OnDestory()
{
    _ModelManger.Destory();
    _Ground.Destroy();
    _GlobalResources.Destory();
}

bool MainScene::OnKeyEvent(const KeyEvent & event) 
{
    _KeyMap[event.keyCode] = event.type == KeyEvent::KeyDown;
    if (event.type == KeyEvent::KeyDown)
    {
        switch (event.keyCode)
        {
        case VK_F1:
            _SceneInfor = !_SceneInfor;
            break;
        case VK_F11:
            //TODO: toggle full screen
            break;
        }
    }
    return true;
}

bool MainScene::OnMouseEvent(const MouseEvent & event) 
{
    return OnCameraMouseEvent(event);
}

bool MainScene::OnCameraMouseEvent(const MouseEvent & event)
{
    static bool leftDown = false, rightDown = false;
    static int2 _lastPt;
    switch (event.type)
    {
        case MouseEvent::LeftBtnDown: leftDown = true; _lastPt = event.pos; break;
        case MouseEvent::LeftBtnUp: leftDown = false; break;
        case MouseEvent::RightBtnDown: rightDown = true; _lastPt = event.pos; break;
        case MouseEvent::RightBtnUp: rightDown = false; break;
        case MouseEvent::MouseMove:
        {
            if (leftDown)
            {
                vec2i offset = event.pos - _lastPt;
                _lastPt = event.pos;
                double speed = 0.5;
                _Camera.rotateViewYByCenter(-offset.x * speed, vec3f(0, 0, 0));
                _Camera.rotateViewXByCenter(-offset.y * speed, vec3f(0, 0, 0));
                return true;
            }
            else if (rightDown)
            {
                vec2i offset = event.pos - _lastPt;
                _lastPt = event.pos;
                _Camera.moveScene(vec3f(0, 0, 0), offset, Size());
                return true;
            }
        }break;
        case MouseEvent::MouseWheel:
        {
            float   scaler = event.pos.x > 0 ? 0.8f : 1.2f;
            vec3f dir = vec3f(0, 0, 0) - _Camera.Position();
            _Camera.SetPosition(vec3f(0, 0, 0) - dir * scaler);
            return true;
        }break;
    }

    return false;
}

void MainScene::OnRender(float elapsed)
{
    vec2i size = GLApp::Size();
    glViewport(0, 0, size.x, size.y);
    _Camera.SetPerspective(45.0f, (float)size.x / (float)size.y, 0.001f, 100.0f);

    glClearColor(_BgColor.x, _BgColor.y, _BgColor.z, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    // draw models
    _Ground.OnRender(_GlobalResources._PROGRAM_P3C4, _Camera);
    _ModelManger.OnRender(_GlobalResources, _Camera);
}

void MainScene::OnRenderUI(float elapsed)
{
#ifdef PER_FPS
    int fps = int(float(1) / elapsed);
#else
    static int fps = 0;
    static float timeLeft = 1.0f;
    static int frameCount = 0;
    ++frameCount;
    timeLeft -= elapsed;
    if (timeLeft < 0)
    {
        fps = frameCount;
        frameCount = 0;
        timeLeft = 1;
    }
#endif
    
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu(STR("File")))
    {
        ImGui::MenuItem(STR("Open"));
        if (ImGui::MenuItem(STR("Exit")))
        {
            this->Close();
        }
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
    
    if (_SceneInfor)
    {
        ImGui::SetNextWindowPos(ImVec2(20, 50), ImGuiCond_Once);
        ImGui::Begin(STR("SceneInfo"), &_SceneInfor, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text(STR("Application average %d FPS/s"), fps);
        ImGui::Text(STR("Eye:%8.3f,%8.3f,%8.3f"), _Camera.Position().x, _Camera.Position().y, _Camera.Position().z);
        ImGui::Text(STR("Dir:%8.3f,%8.3f,%8.3f"), _Camera.FrontDir().x, _Camera.FrontDir().y, _Camera.FrontDir().z);
        ImGui::Text(STR("Up :%8.3f,%8.3f,%8.3f"), _Camera.UpDir().x, _Camera.UpDir().y, _Camera.UpDir().z);
        ImGui::ColorEdit3(STR("BgColor"), &_BgColor.x);
        ImGui::End();
    }
}
