#include <iostream>
#include <iomanip>
#include <vector>
#include <glad/glad.h>
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

#include <win/tlWinManager.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//! 光照类型 0 平行光   1 点光源
#define LIGHTTYPE  1 




int main(int argc, char **argv)
{
    tl::GlfwManager window(WIN_WIDTH, WIN_HEIGHT);
    if(!window.init())
        return -1;
    const float grayclr = 0.8f;
    tl::Drawable< tl::Box  > pyramid(100.0f, tl::color_t(1.0f, 0.0f, 0.0f, 1.0f));
    tl::Drawable< tl::Plane> plane  (600.0f, tl::color_t(grayclr, grayclr, grayclr, 1.0f));

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

    glEnable(GL_MULTISAMPLE);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);


    tl::camera cam;
    cam.setProjMatrixByPrespective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 2000.0f);
    cam.setViewMatrix(glm::vec3(0.0f, -800.0f, 120.0f), glm::vec3(0, 0, 100), glm::vec3(0, 1, 0));

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
    dirlight.dir = {0.0,0.0,1.0};
    dirlight.clr = {1.0f, 1.0f, 1.0f, 1.0f};
#endif
    window.renderLoop([&]()->void
    {
        shader.bind(UNIFORM_AMBCLR, ambiclr);
        
        shader.bind(UNIFORM_SPSTRGTH, 0.5f);

#if LIGHTTYPE
        //点光源
        shader.bind(UNIFORM_LIGHTCLR, ptlight.clr);
        shader.bind(UNIFORM_LIGHTPOS, ptlight.pos);
        shader.bind(UNIFORM_STRENGTH, ptlight.fade);
        ptlight.pos.z += 1e-2;
#else
        dirlight.dir.x += 1e-4;
        // 平行光
        shader.bind(UNIFORM_LIGHTCLR, dirlight.clr);
        shader.bind(UNIFORM_LIGHTDIR, dirlight.dir);
#endif
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 206.0f / 255.0f, 1.0f);  lightblue
        glClearColor(0.0, 0.0, 0.0, 1.0);

        glm::mat4 modelmtrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 150)) *
                               glm::rotate(glm::identity<glm::mat4>(), (float)glfwGetTime() * 2.0f, glm::vec3(0, 0, 1)) *
                               glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(0, 1, 0)) *
                               glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(1, 0, 0));

        cam.setModelMatrix(modelmtrix);

        //设置视口
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

        // shader.bind(UNIFORM_MVP, cam.getMVP());
        shader.bind(UNIFORM_MODMTX, cam.getModelMatrix());
        shader.bind(UNIFORM_VIEWMTX, cam.getViewMatrix());
        shader.bind(UNIFORM_PRJMTX, cam.getProjMatrix());
        
        pyramid.render(shader);

        cam.setModelMatrix(glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 0)));

        // shader.bind(UNIFORM_MVP, cam.getMVP());
        shader.bind(UNIFORM_MODMTX, cam.getModelMatrix());
        plane.render(shader);
    });

    return 0;
}