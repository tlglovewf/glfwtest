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
#include <render/tlLight.h>
#include <geometry/tlShapes.h>
#define WIN_WIDTH 800
#define WIN_HEIGHT 600


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
    const float grayclr = 0.5f;
    tl::Drawable< tl::Box  > pyramid(100.0f, tl::color_t(1.0f, 0.0f, 0.0f, 1.0f));
    tl::Drawable< tl::Plane> plane  (600.0f, tl::color_t(grayclr, grayclr, grayclr, 1.0f));

    tl::Shader shader;
    shader.attach("pointlight.vert");
    shader.attach("pointlight.frag");
    shader.link();

    glEnable(GL_MULTISAMPLE);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    tl::camera cam;
    cam.setProjMatrixByPrespective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 2000.0f);
    cam.setViewMatrix(glm::vec3(0.0f, -800.0f, 120.0f), glm::vec3(0, 0, 100), glm::vec3(0, 1, 0));

    //! set default color
    const float rt = 0.5f;
    tl::color_t ambiclr = {rt, rt, rt, rt};
    
    tl::PointLight ptlight;
    ptlight.pos = {0.0, 0.0, 500.0};
    ptlight.clr = {1.0f, 1.0f, 1.0f, 1.0f};
    

    while (!glfwWindowShouldClose(window))
    {

        shader.bind(UNIFORM_AMBCLR, ambiclr);
        shader.bind(UNIFORM_LIGHTPOS, ptlight.pos);
        shader.bind(UNIFORM_LIGHTCLR, ptlight.clr);

        int width  = 0;
        int height = 0;
        //获取长宽
        glfwGetFramebufferSize(window, &width, &height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 206.0f / 255.0f, 1.0f);  lightblue
        glClearColor(0.0, 0.0, 0.0, 1.0);

        glm::mat4 modelmtrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 150)) *
                               glm::rotate(glm::identity<glm::mat4>(), (float)glfwGetTime() * 2.0f, glm::vec3(0, 0, 1)) *
                               glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(0, 1, 0)) *
                               glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(1, 0, 0));

        cam.setModelMatrix(modelmtrix);

        //设置视口
        glViewport(0, 0, width, height);

        // shader.bind(UNIFORM_MVP, cam.getMVP());
        shader.bind(UNIFORM_MODMTX, cam.getModelMatrix());
        shader.bind(UNIFORM_VIEWMTX, cam.getViewMatrix());
        shader.bind(UNIFORM_PRJMTX, cam.getProjMatrix());
        
        pyramid.render(shader);

        cam.setModelMatrix(glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 0)));

        // shader.bind(UNIFORM_MVP, cam.getMVP());
        shader.bind(UNIFORM_MODMTX, cam.getModelMatrix());
        plane.render(shader);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    // glfwTerminate();
    return 0;
}