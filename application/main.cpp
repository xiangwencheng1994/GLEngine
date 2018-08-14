#include <sgeGLApp.h>
#include <sgeLog.h>
#include <sgeGLSLProgram.h>
#include <sgeGLX.h>
#include <sgeCamera.h>
#include <shapes/cube.h>
#include <imgui/imgui.h>

#include <sgeGround.h>
#include <sgeSkybox.h>

using namespace sge;

class MyApp : public GLApp
{
public:
    PROGRAM_P3C4 prg;
    Ground  ground;

    GLuint  vbo;

    bool    keyMap[256];
    Camera  camera;

    vec3f           color;
    vec3f           bgColor;
public:
    MyApp()
        : camera(vec3f(0, 0, 10), vec3f(0, 0, 0))
    {
        setTitle("App");

        bgColor = float3(0.1f, 0.1f, 0.1f);
    }

    ~MyApp() {}

    virtual void onRender(float elapsed) override
    {
        glClearColor(bgColor.x, bgColor.y, bgColor.z, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        
        mat4f mvp = camera.ProjectionMatrix() * camera.ViewMatrix();
        
        ground.render(mvp, prg);

        prg.begin();
        {
            glUniformMatrix4fv(prg._mvp, 1, false, mvp * mat4f::createTranslation(0, 1, 0) * mat4f::createScale(2, 2, 2));
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glVertexAttribPointer(prg._position, 3, GL_FLOAT, false, 12, 0);
            glDisableVertexAttribArray(prg._color);
            glVertexAttrib4fv(prg._color, &color.x);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, CubeTrianglesIndices);
            glVertexAttrib4f(prg._color, 1, 1, 1, 1);
            glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, CubeLinesIndices);
        }
        prg.end();
    }

    virtual void onRenderUI(float elapsed) override
    {
        if (keyMap[VK_F1])
        {
            ImGui::Begin("SceneInfo");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Eye:%8.3f,%8.3f,%8.3f", camera.Position().x, camera.Position().y, camera.Position().z);
            ImGui::Text("TGT:%8.3f,%8.3f,%8.3f", camera.Target().x, camera.Target().y, camera.Target().z);
            ImGui::Text("Up :%8.3f,%8.3f,%8.3f", camera.UpDir().x, camera.UpDir().y, camera.UpDir().z);
            ImGui::ColorEdit3("BgColor", &bgColor.x);
            ImGui::ColorEdit3("BoxColor", &color.x);
            ImGui::End();
        }
    }

private:

    virtual void onCreate() override
    {
        GLX::LogGLVersion();
        
        if (!prg.create()) 
        {
            Log::error("Create prg failed");
        }
        
        if (!ground.create())
        {
            Log::error("Create ground failed");
        }

        vbo = GLX::CreateBuffer(VertexBuffer, StaticDraw, sizeof(CubeVertices), CubeVertices);
        
        this->getGLContext()->EnableVSYNC(false);
    }

    virtual void onDestory() override
    {
        prg.destory();
        glDeleteBuffers(1, &vbo);
    }

    virtual bool onKeyEvent(const KeyEvent & event) override
    {
        keyMap[event.keyCode] = event.type == KeyEvent::KeyDown;
        if (VK_F11 == event.keyCode && event.type == KeyEvent::KeyDown)
        {
            HWND   hDesk;
            RECT   rc;
            hDesk = GetDesktopWindow();
            GetWindowRect(hDesk, &rc);
            SetWindowLong(getHWND(), GWL_STYLE, WS_BORDER);
            SetWindowPos(getHWND(), HWND_TOPMOST, 0, 0, rc.right, rc.bottom, SWP_SHOWWINDOW);
        }
        if (VK_ESCAPE == event.keyCode)
        {
            this->destroy();
        }
        return true;
    }

    virtual bool onMouseEvent(const MouseEvent & event) override
    {
        static bool leftDown = false, midDown = false;
        static int2 mousePt;
        switch (event.type)
        {
        case MouseEvent::LeftBtnDown:
            leftDown = true;
            camera.beginDrag(event.pos);
            break;
        case MouseEvent::LeftBtnUp:
            camera.endDrag();
            leftDown = false;
            break;
        case MouseEvent::RightBtnDown:
            midDown = true;
            mousePt = event.pos;
            break;
        case MouseEvent::RightBtnUp:
            midDown = false;
            break;
        case MouseEvent::MouseMove:
        {
            if (leftDown)
            {
                camera.onDrag(event.pos);
            }
            else if(midDown)
            {
                vec2i offset = event.pos - mousePt;
                mousePt = event.pos;

                //TODO: move scence
            }
        }break;
        case MouseEvent::MouseWheel:
        {
            if (!leftDown)
            {
                vec3f dir = camera.Target() - camera.Position();
                int x = event.pos.x / WHEEL_DELTA;
                camera.setPosition(camera.Position() + dir * x * 0.1);
            }
        }break;
        }

        return false;
    }

    virtual void onSizeChanged(int width, int height)
    {
        glViewport(0, 0, width, height);
        camera.setPerspective(45.0f, (float)width / (float)height, 0.001f, 2000.0f);
    }

};

int main()
{
    MyApp app;
    return app.run();
}