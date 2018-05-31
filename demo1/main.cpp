#include <sgeGLApp.h>
#include <sgeLog.h>
#include <sgeGLSLProgram.h>
#include <sgeGLX.h>

using namespace sge;

class GLSL_Test : public GLSLProgram
{
public:
    attribute   vertex;
    uniform     color;
    uniform     mvp;

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
            void main()\n\
            {\n\
                gl_Position = mvp * vec4(vertex, 1);\n\
            }\n";
    }

    virtual const char * getFragmentShaderSrc() const override
    {
        return "#version 430 core \n\
            uniform vec4 color = vec4(1, 0, 0, 1);\n\
            out vec4 fragColor;\n\
            void main()\n\
            {\n\
                fragColor = color;\n\
            }\n";
    }

    virtual void onCreateAfter() override
    {
        vertex = getAttribLocation("vertex");
        color = getUniformLocation("color");
        mvp = getUniformLocation("mvp");
    }
};

class MyApp : public GLApp
{
public:
    GLSL_Test prog;
    
    GLuint  vbo;
    mat4f   matMVP;
public:
	MyApp() 
	{
		setTitle("Demo1");
        Vector3<float> a;
        
        matMVP.identity();
	}

	~MyApp() {}

	virtual void onRender(float elapsed) override
	{
		glClearColor(0, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);

        prog.begin();
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(prog.vertex, 3, GL_FLOAT, false, 0, 0);
            glUniformMatrix4fv(prog.mvp, 1, false, matMVP);            
            glUniform4f(prog.color, 0, 1, 0, 1);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        prog.end();
	}
private:

	virtual void onCreate() override
	{
        // Check GL version.
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        Log::debug("GL Vendor: %s", vendor);
        Log::debug("GL Renderer: %s", renderer);
        Log::debug("GL Version: %d.%d, GLSL%s", major, minor, glslVersion);
        
        bool ret = prog.create();
        assert(ret && "Create Shader failed, check your GPU version on logger.");
        
        const float3 verts[3] =
        {
            { -0.5, -0.5, 0 },
            { 0, 0.5, 0 },
            { 0.5, -0.5, 0 }
        };
        vbo = GLX::CreateBuffer(Vertex, StaticDraw, sizeof(verts), verts);
    }
	
	virtual void onDestory() override
	{
        prog.destory();
	}

    virtual bool onKeyEvent(const KeyEvent & event) override
    {
        switch (event.keyCode)
        {
        case 'A':
            matMVP = mat4f::createTranslation(-0.5, 0, 0);
            break;
        case 'S':
            matMVP = mat4f::createTranslation(0, -0.5, 0);
            break;
        case 'D':
            matMVP = mat4f::createTranslation(+0.5, 0, 0);
            break;
        case 'W':
            matMVP = mat4f::createTranslation(0, +0.5, 0);
            break;
        }
        return true;
    }
};


int main()
{
	MyApp app;
    return app.run();
}