#include <iostream>
#include <iomanip>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/string_cast.hpp>

#include <render/tlShader.h>
#include <render/tlConstants.h>
#include <render/tlDrawable.h>
#include <render/tlCamera.h>

#include <geometry/tlShapes.h>

#define WIN_WIDTH  800
#define WIN_HEIGHT 600

tl::camera cam;
glm::mat4  changematrix = glm::identity<glm::mat4>();
int main(int argc, char **argv)
{
    GLFWwindow *window = nullptr;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    window = glfwCreateWindow(800, 600, "This is first glfw program", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) //!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "load glad failed!" << std::endl;
        return -1;
    }

    glfwSwapInterval(1); //垂直同步
    glfwSetErrorCallback([](int error, const char *description) -> void {
        std::cout << "error : " << error << " " << description << std::endl;
    });

    if (!window)
    {
        std::cout << "Create window failed." << std::endl;
        glfwTerminate();
        return -1;
    }

    tl::Drawable<tl::Axis > pyramid(100.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    tl::Drawable<tl::Box  > box(100.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    tl::Drawable<tl::Plane> plane(600.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    tl::Drawable<tl::Axis > axis(100.0f, glm::vec4());
    tl::Drawable<tl::Line > tline(100.0f, glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

    tl::Shader shader;
    shader.attach("normal.vert");
    shader.attach("normal.frag");
    shader.link();

    glEnable(GL_MULTISAMPLE);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(3.0f);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    cam.setProjMatrixByPrespective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 2000.0f);
    cam.setViewMatrix(glm::vec3(0.0f, -800.0f, 110.0f), glm::vec3(0, 0, 100), glm::vec3(0, 1, 0));


    glfwSetKeyCallback(window,[](GLFWwindow*,int key,int scancode,int action,int mods)->void
    {
        std::cout << key << " " << scancode << " " << action << " " << mods << std::endl;
        
        static glm::mat4 modelmtrix = glm::identity<glm::mat4>();
        std::cout << glm::to_string(changematrix) << std::endl;
        static float deg = 90.0f;
        if(action != GLFW_RELEASE)
        {
            return ;
        }
        if( key == GLFW_KEY_W )
        {
            changematrix = glm::rotate(glm::identity<glm::mat4>(),glm::radians(deg),glm::vec3(1, 0, 0)) * changematrix;
        }
        else if( key == GLFW_KEY_S)
        {
            changematrix = glm::rotate(glm::identity<glm::mat4>(),glm::radians(deg),glm::vec3(0, 1, 0)) * changematrix;
        }
        else if( key == GLFW_KEY_A)
        {
            changematrix = glm::rotate(glm::identity<glm::mat4>(),glm::radians((float)glfwGetTime() * 2.0f),glm::vec3(1, 0, 1)) * changematrix;
        }
        else if (key == GLFW_KEY_D)
        {
           changematrix = glm::rotate(glm::identity<glm::mat4>(), glm::radians(deg), glm::vec3(1, 0, 1)) * changematrix;
        }
        else 
        {
            changematrix = glm::identity<glm::mat4>();
        }
        // deg += 10.0f;
    });

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        //获取长宽
        glfwGetFramebufferSize(window, &width, &height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 206.0f / 255.0f, 1.0f);

                            //  glm::rotate(glm::identity<glm::mat4>(), (float)glfwGetTime() * 2.0f, glm::vec3(1, 1, 1)) *

        // glm::mat4 modelmtrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 150)) *
                            
        //                        glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(0, 1, 0));

        glm::mat4 modelmtrix = glm::identity<glm::mat4>();

        cam.setModelMatrix(modelmtrix);

        //设置视口
        glViewport(0, 0, width, height);

        cam.setModelMatrix(glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 100)) * changematrix);
        shader.bind(UNIFORM_MVP, cam.getMVP());

        pyramid.render(shader);
        box.render(shader);

        cam.setModelMatrix(glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 0)));
        shader.bind(UNIFORM_MVP, cam.getMVP());

        plane.render(shader);

        cam.setModelMatrix(glm::translate(glm::identity<glm::mat4>(), glm::vec3(-250,-250,0)));
        shader.bind(UNIFORM_MVP, cam.getMVP());

        axis.render(shader);
        tline.render(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    // glfwTerminate();
    return 0;
}