#include <iostream>
#include <iomanip>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/string_cast.hpp>

#include <render/tlShader.h>
#include <render/tlConstants.h>
#include <render/tlDrawable.h>
#include <render/tlCamera.h>
#include <render/tlLight.h>
#include <render/tlTexture.h>
#include <geometry/tlShapes.h>
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// "/media/tu/Work/OpenGLTest/datas/images/test.png"
void save_gpuimage(const std::string &path)
{
    tl::Image image;
    uint8_t *data = new uint8_t[WIN_WIDTH * WIN_HEIGHT * 4];
    glReadPixels(0, 0, WIN_WIDTH, WIN_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, data);
    image.setData(data, WIN_WIDTH, WIN_HEIGHT, 4);
    image.save(path.c_str());
}

void renderScene(tl::Shader &shader)
{
  
    static const float grayclr = 0.8f;
    static tl::Drawable<tl::Box> pyramid(100.0f, tl::color_t(1.0f, 0.0f, 0.0f, 1.0f));
    static tl::Drawable<tl::Plane> plane(600.0f, tl::color_t(grayclr, grayclr, grayclr, 1.0f));

 

    glm::mat4 modelmtrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 90)) *
                           glm::rotate(glm::identity<glm::mat4>(), (float)glfwGetTime() * 2.0f, glm::vec3(0, 0, 1)) *
                           glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(0, 1, 0)) *
                           glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(1, 0, 0));

    shader.bind(UNIFORM_MODMTX, modelmtrix);
    pyramid.render(shader);

    shader.bind(UNIFORM_MODMTX, glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 0)));
    plane.render(shader);

}

void renderScreen(const std::shared_ptr<tl::TextureUnit> &unit)
{
    tl::Shader screen;
    screen.attach("screentexture.vert");
    screen.attach("screentexture.frag");
    screen.link();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //设置视口
    tl::Drawable<tl::ScreenPlane> screenplane(WIN_WIDTH, WIN_HEIGHT, unit);
    screen.activate();
    glm::mat4 screenmatrix = glm::ortho(0.0f, (float)WIN_WIDTH, 0.0f, (float)WIN_HEIGHT, 0.0f, 1000.0f);
    screen.bind(UNIFORM_MVP, screenmatrix);
    screenplane.render(screen);
}

//! 光照类型 0 平行光   1 点光源
#define LIGHTTYPE 0

int main(int argc, char **argv)
{
    GLFWwindow *window = nullptr;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "This is first glfw program", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
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

    std::shared_ptr<tl::TextureUnit> unit = std::make_shared<tl::TextureUnit>();
    if (!unit->generate("/media/tu/Work/OpenGLTest/datas/images/toy_box_disp.png"))
    {
        printf("image load error .\n");
        return -1;
    }

    tl::Shader depthshader;
    tl::Shader shader;

#if LIGHTTYPE
    //点光源
    shader.attach("pointlight.vert");
    shader.attach("pointlight.frag");
#else
    //平行光
    shader.attach("dirlight.vert");
    shader.attach("dirlight.frag");
#endif
    shader.link();

    depthshader.attach("depth.vert");
    depthshader.attach("depth.frag");
    depthshader.link();

    glEnable(GL_MULTISAMPLE);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    tl::camera cam;

    // cam.setViewMatrix(glm::vec3(0.0f, -800.0f, 120.0f), glm::vec3(0, 0, 100), glm::vec3(0, 1, 0));
  

    //! set default color
    const float rt = 0.25f;
    tl::color_t ambiclr = {rt, rt, rt, rt};

#if LIGHTTYPE
    tl::PointLight ptlight;
    ptlight.pos = {0.0, 0.0, 0.0};
    ptlight.clr = {1.0f, 1.0f, 1.0f, 1.0f};
    ptlight.fade = 1e-4;
#else
    tl::DirLight dirlight;
    dirlight.dir = {0.0, 0.0, 1.0};
    dirlight.clr = {1.0f, 1.0f, 1.0f, 1.0f};
#endif

    GLint textureMax = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &textureMax);

    if (textureMax < WIN_WIDTH ||
        textureMax < WIN_WIDTH)
    {
        throw std::runtime_error("texture size overflow.");
    }

    while (!glfwWindowShouldClose(window))
    {
        shader.activate();
        shader.bind(UNIFORM_AMBCLR, ambiclr);

        shader.bind(UNIFORM_SPSTRGTH, 0.5f);

        // depthshader.activate();

#if LIGHTTYPE
        //点光源
        shader.bind(UNIFORM_LIGHTCLR, ptlight.clr);
        shader.bind(UNIFORM_LIGHTPOS, ptlight.pos);
        shader.bind(UNIFORM_STRENGTH, ptlight.fade);
        ptlight.pos.z += 1e-2;
#else
        // dirlight.dir.x += 1e-4;
        // 平行光
        shader.bind(UNIFORM_LIGHTCLR, dirlight.clr);
        shader.bind(UNIFORM_LIGHTDIR, dirlight.dir);
#endif
        // int width  = 0;
        // int height = 0;
        // //获取长宽
        // glfwGetFramebufferSize(window, &width, &height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.0, 0.0, 0.0, 1.0);

        //设置视口
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
        cam.setProjMatrixByPrespective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 2000.0f);
        shader.bind(UNIFORM_PRJMTX, cam.getProjMatrix());

        cam.setPosition(glm::vec3(0.0f, -800.0f, 120.0f));
        cam.setLookDir(glm::vec3(0,0,0) - glm::vec3(0.0f, -800.0f, 120.0f));
        shader.bind(UNIFORM_VIEWMTX, cam.getViewMatrix());
        renderScene(shader);

        //右下  不同相机视点
        glViewport(0.5 * WIN_WIDTH, 0, 0.5 * WIN_WIDTH, 0.5 * WIN_HEIGHT);
        cam.setPosition(glm::vec3(300.0f, -800.0f, 120.0f));
        cam.setLookDir(-glm::vec3(300.0f, -800.0f, 120.0f));
        shader.bind(UNIFORM_VIEWMTX, cam.getViewMatrix());
        renderScene(shader);

        //左下 光源视角
        glViewport(0, 0, 0.5 * WIN_WIDTH, 0.5 * WIN_HEIGHT);
        auto pos = dirlight.dir * 800.0f;
        static float size = 300.0f;
        size += 1e-1;
        cam.setProjMatrixByOrtho(-size, size, -size, size,0.0f, 2000.0f);
        shader.bind(UNIFORM_PRJMTX, cam.getProjMatrix());

        cam.setPosition(pos);
        cam.setLookDir(-dirlight.dir);
        shader.bind(UNIFORM_VIEWMTX, cam.getViewMatrix());
        renderScene(shader);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    // 不注释 退出会发生崩溃
    // glfwTerminate();
    return 0;
}