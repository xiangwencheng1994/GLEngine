#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <sgeGlobalResources.h>
#include <sgeGLApp.h>
#include <sgeCamera.h>
#include <sgeGround.h>
#include <sgeModelManager.h>

class MainScene : public sge::GLApp
{
public:
    MainScene();
    virtual ~MainScene();
    
    sge::Camera     _Camera;
    sge::vec3f      _BgColor;
    bool            _KeyMap[256];
    bool            _SceneInfor;

    sge::GlobalResources    _GlobalResources;

    sge::Ground         _Ground;
    sge::ModelManager   _ModelManger;
protected:
    virtual void OnCreate() override;
    virtual void OnDestory() override;
    virtual bool OnKeyEvent(const sge::KeyEvent & event) override;
    virtual bool OnMouseEvent(const sge::MouseEvent & event) override;
    virtual void OnRender(float elapsed) override;
    virtual void OnRenderUI(float elapsed) override;

    virtual bool OnCameraMouseEvent(const sge::MouseEvent & event);
private:
    DISABLE_COPY(MainScene)
};

#endif // !MAIN_SCENE_H
