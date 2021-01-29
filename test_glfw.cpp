#include <iostream>
#include <iomanip>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct vertex
{
    float x,y;
    float r,g,b;
};

// vertex vertices[] = {{-0.6f, -0.4f,1.0f,0.0f,0.0f},
//                      { 0.6f, -0.4f,0.0f,1.0f,0.0f},
//                      { 0.0f,  0.6f,0.0f,0.0f,1.0f}};

std::vector<vertex> vertices = {{-0.6f, -0.4f,1.0f,0.0f,0.0f},
                                { 0.6f, -0.4f,0.0f,1.0f,0.0f},
                                { 0.0f,  0.6f,0.0f,0.0f,1.0f}};

constexpr char* vertex_shader_str = 
"uniform mat4 MVP;\
attribute vec3 vCol;\
attribute vec3 vPos;\
varying vec3 color;\
void main()\
{\
   gl_Position = vec4(vPos,1.0);\
   color = vCol;\
}";
constexpr char* fragment_shader_str = 
"varying vec3 color;\n"
"void main()\n"
"{\n"
"   gl_FragColor = vec4(color, 0.0);\n"
"}\n";


int main(int argc, char **argv)
{
    GLFWwindow *window = nullptr;

    if(!glfwInit())
        return -1;
    glfwWindowHint(GLFW_SAMPLES,4);
    glfwWindowHint(GLFW_DEPTH_BITS,24);

    window = glfwCreateWindow( 800, 600, "This is first glfw program", NULL, NULL);

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "load glad failed!" << std::endl;
        return -1;
    }

    glfwSwapInterval(1); //垂直同步
    glfwSetErrorCallback([](int error, const char *description)->void
    {
        std::cout << "error : " << error << " " << description << std::endl;
    });

    if(!window)
    {
        std::cout << "Create window failed." << std::endl;
        glfwTerminate();
        return -1;
    }
    // glfwWindowHint()
    glfwSetMouseButtonCallback(window,[](GLFWwindow *window, int x, int y, int z){
        std::cout << "x = " << x << " y = " << y << " z = " << z << std::endl;
    });

    //a 键值    b 次数   c : 1按下  2连续按   d 组合按键
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if( key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    });

    // double time = glfwGetTime();
    GLuint vertex_buffer = 0;
    glGenBuffers(1,&vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex) * vertices.size(),&vertices[0],GL_STATIC_DRAW);

    GLuint vertex_shader    = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_str, NULL);
    glCompileShader(vertex_shader);
    int status = 0;
    glGetShaderiv(vertex_shader,GL_COMPILE_STATUS,&status);
    if(!status)
    {
        int maxlength = 0;
        GLsizei length = 0;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxlength);
        std::unique_ptr<char> info(new char[maxlength]);
        glGetShaderInfoLog(vertex_shader, maxlength, &length, info.get());
        std::cout << "shader compile error is " << info.get() << std::endl;
    }

    GLuint fragment_shader  = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_str,NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(vertex_shader,GL_COMPILE_STATUS,&status);

    glEnable(GL_MULTISAMPLE);
    if(!status)
    {
        int maxlength = 0;
        GLsizei length = 0;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxlength);
        std::unique_ptr<char> info(new char[maxlength]);
        glGetShaderInfoLog(vertex_shader, maxlength, &length, info.get());
        std::cout << "shader compile error is " << info.get() << std::endl;
    }
    GLuint program = glCreateProgram();


    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
     

    GLuint mvp_location = glGetUniformLocation(program, "MVP" );
    GLuint vpos_location= glGetAttribLocation (program, "vPos");
    GLuint vcol_location= glGetAttribLocation (program, "vCol");

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location,3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 2));


    while( !glfwWindowShouldClose(window))
    {
        int width, height;
        //获取长宽
        glfwGetFramebufferSize(window, &width, &height); 

        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(1.0,0,0,1.0);

        //设置视口
        glViewport(0, 0, width, height);

        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES,0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}