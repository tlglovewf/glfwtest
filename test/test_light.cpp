#include <iostream>
#include <iomanip>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <render/tlshader.h>

#define WIN_WIDTH    800
#define WIN_HEIGHT   600

struct vertex
{
    glm::vec3 pos;
    glm::vec3 clr;
};

std::vector<vertex> vertices = {{{-50.0f,   0.0f,  -28.87f},{1.0f,0.0f,0.0f}},
                                {{ 50.0f,   0.0f,  -28.87f},{1.0f,1.0f,0.0f}},
                                {{  0.0f,   0.0f,   57.70f},{0.0f,0.0f,1.0f}},
                                {{  0.0f,86.602f,     0.0f},{1.0f,1.0f,0.0f}}};

std::vector<uint8_t> idices = {0, 1, 3, 
                               1, 2, 3, 
                               2, 0, 3,
                               0, 1, 2};

int main(int argc, char **argv)
{
    GLFWwindow *window = nullptr;

    if(!glfwInit())
        return -1;
    glm::vec2 vt = {0.6,0.3};
    glfwWindowHint(GLFW_SAMPLES,4);
    glfwWindowHint(GLFW_DEPTH_BITS,24);

    window = glfwCreateWindow( 800, 600, "This is first glfw program", NULL, NULL);

    glfwMakeContextCurrent(window);

    if(/*!gladLoadGL())*/!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
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

    double time = glfwGetTime();
    GLuint vertex_buffer = 0;
    glGenBuffers(1,&vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex) * vertices.size(),&vertices[0],GL_STATIC_DRAW);
     
    GLuint index_buffer = 0;
    glGenBuffers(1,&index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idices), &idices[0], GL_STATIC_DRAW);

    tl::Shader shader;
    shader.attach("triangle.vert");
    shader.attach("triangle.frag");
    shader.link();

    GLuint mvp_location = shader.uniformloc("MVP");
    GLuint vpos_location= shader.attriloc("vPos");
    GLuint vcol_location= shader.attriloc("vCol");

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(float) * 3));

    glEnable(GL_MULTISAMPLE);
    glDisable(GL_CULL_FACE);
    while( !glfwWindowShouldClose(window))
    {
        shader.activate();
        int width, height;
        //获取长宽
        glfwGetFramebufferSize(window, &width, &height); 

        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 206.0f / 255.0f, 1.0f);

        glm::mat4 mvp = glm::identity<glm::mat4>();

        glm::mat4 modelmtrix = glm::rotate(glm::identity<glm::mat4>(), (float)glfwGetTime() * 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projmatrix = glm::perspective(glm::radians(60.0f), (float)width / (float)height,0.0f,100.0f);

        glm::mat4 viewmatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -200.0f), glm::vec3(0,0,0),glm::vec3(0,1,0));

        mvp = projmatrix * viewmatrix * modelmtrix;

        GLuint loc = shader.uniformloc("fade");
        static float fade = 1e-4;
        glUniform1f(loc,fade);
        fade += 1e-4;

        shader.bind("MVP", mvp);
        //设置视口
        glViewport(0, 0, width, height);

        glDrawElements(GL_TRIANGLES, idices.size(), GL_UNSIGNED_BYTE, NULL);

        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    
    // glfwTerminate();
    return 0;
}