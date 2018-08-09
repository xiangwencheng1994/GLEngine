#include <sgeGLApp.h>
#include <sgeLog.h>
#include <sgeGLSLProgram.h>
#include <sgeGLX.h>
#include <sgeCamera.h>
#include <shapes/cube.h>
#include <imgui/imgui.h>

using namespace sge;

class GLSL_Test : public GLSLProgram
{
public:
    attribute   vertex;
    uniform     color;
    uniform     mvp;
    uniform     model;

    void begin() const override
    {
        __super::begin();
        glEnableVertexAttribArray(vertex);
    }

    void end() const override
    {
        glDisableVertexAttribArray(vertex);
        __super::begin();
    }

private:

    const char * getVertexShaderSrc() const override
    {
        return "#version 430 core \n\
            in vec3 vertex;\n\
            uniform mat4 mvp;\n\
            uniform mat4 model;\n\
            void main()\n\
            {\n\
                gl_Position = mvp * model * vec4(vertex, 1);\n\
            }\n";
    }

    virtual const char * getFragmentShaderSrc() const override
    {
        return "#version 430 core \n\
            uniform vec3 color = vec3(1, 0, 0);\n\
            out vec4 fragColor;\n\
            void main()\n\
            {\n\
                fragColor = vec4(color, 1);\n\
            }\n";
    }

    virtual void onCreateAfter() override
    {
        vertex = getAttribLocation("vertex");
        color = getUniformLocation("color");
        mvp = getUniformLocation("mvp");
        model = getUniformLocation("model");
    }
};

class MyApp : public GLApp
{
public:
    GLSL_Test prog;

    GLuint  vbo;

    PerspectiveCamera<float>    camera;
    Matrix4<float>  model;
    float3          color;
    float3          bgColor;
public:
    MyApp()
        : camera(float3(0, 0, 10), float3(0, 0, 0), float3(0, 1, 0))
    {
        setTitle("Demo2");

        camera.setFovy(60);
        camera.setZNear(0.001f);
        camera.setZFar(2000);
        bgColor = float3(0, 0.5f, 0.5f);
    }

    ~MyApp() {}

    virtual void onRender(float elapsed) override
    {
        glClearColor(bgColor.x, bgColor.y, bgColor.z, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        static float time = 0;
        //time += elapsed * 20;
        
        mat4f mvp = camera.getProjectionMatrix()
            * camera.getViewMatrix()
            * mat4f::createRotationAroundAxis(time, time, time);

        prog.begin();
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(prog.vertex, 3, GL_FLOAT, false, 0, 0);
            
            glUniformMatrix4fv(prog.mvp, 1, false, mvp);
            glUniformMatrix4fv(prog.model, 1, false, model);
            glUniform3f(prog.color, color.x, color.y, color.z);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, CubeTrianglesIndices);

            glEnable(GL_DEPTH_TEST);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glUniform3f(prog.color, 1, 1, 1);
            glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, CubeLinesIndices);
            glDisable(GL_DEPTH_TEST);
        }
        prog.end();
    }
    virtual void onRenderUI(float elapsed) override
    {
        ImGui::NewFrame();
        ImGui::Begin("SceneInfo");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Eye:%8.3f,%8.3f,%8.3f", camera.getEye().x, camera.getEye().y, camera.getEye().z);
        ImGui::Text("Tgt:%8.3f,%8.3f,%8.3f", camera.getTarget().x, camera.getTarget().y, camera.getTarget().z);
        ImGui::Text("Up :%8.3f,%8.3f,%8.3f", camera.getUp().x, camera.getUp().y, camera.getUp().z);
        ImGui::ColorEdit3("BgColor", &bgColor.x);
        ImGui::ColorEdit3("BoxColor", &color.x);
        ImGui::End();
        ImGui::EndFrame();
    }

private:

    virtual void onCreate() override
    {
        GLX::LogGLVersion();

        bool ret = prog.create();
        assert(ret && "Create Shader failed, check your GPU version on logger.");
        
        Cube<float> cube;
        vbo = GLX::CreateBuffer(VertexBuffer, StaticDraw, sizeof(cube.vertices), cube.vertices);      
        
        model = mat4f::createScale(5, 5, 5);

        this->getGLContext()->EnableVSYNC(false);
    }

    virtual void onDestory() override
    {
        prog.destory();
    }

    virtual bool onKeyEvent(const KeyEvent & event) override
    {
        return true;
    }

    virtual bool onMouseEvent(const MouseEvent & event) override
    {
        static bool leftDown = false;
        static int2 mousePt;
        switch (event.type)
        {
        case MouseEvent::LeftBtnDown:
            mousePt = event.pos;
            leftDown = true;
            break;
        case MouseEvent::LeftBtnUp:
            leftDown = false;
            break;
        case MouseEvent::MouseMove:
        {
            if (leftDown)
            {
                int2 offset = mousePt - event.pos;
                mousePt = event.pos;
                camera.rotateViewX(-offset.y * 0.3f);
                camera.rotateViewY(offset.x * 0.3f);
            }
        }break;
        case MouseEvent::MouseWheel:
        {
            float3 dir = camera.getEye() - camera.getTarget();
            float len = dir.length();
            dir.normalize();
            dir = dir * (len - event.pos.x * 0.01f);
            camera.setEye(camera.getTarget() + dir);
        }break;
        }

        return false;
    }

    virtual void onSizeChanged(int width, int height)
    {
        glViewport(0, 0, width, height);
        camera.setViewSize(float2((float)width, (float)height));
    }

};

int main()
{
    MyApp app;
    return app.run();
}