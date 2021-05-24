#include <iostream>
#include <iomanip>
#include <vector>
#include <glad/glad.h>

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

#include <win/tlWinManager.h>

#define WIN_WIDTH   800
#define WIN_HEIGHT  600
#define SHADOW_SIZE 1024
// "/media/tu/Work/OpenGLTest/datas/images/test.png"
void save_gpuimage(const std::string &path)
{
    tl::Image image;
    uint8_t *data = new uint8_t[WIN_WIDTH * WIN_HEIGHT * 4];
    glReadPixels(0, 0, WIN_WIDTH, WIN_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, data);
    image.setData(data, WIN_WIDTH, WIN_HEIGHT, 4);
    image.save(path.c_str());
}
//! 离屏渲染
class OffScreenDrawer
{
public:
    enum class eTexType
    {
        eDepthTex,
        eColorTex
    };
    //! 创建离屏纹理并绑定
    void createTextureAndBind(int width, int height, eTexType type = eTexType::eColorTex)
    {
        if (mFboid != MINUSONE)
            return;
       
        glGenTextures(1, &mTexid);
        glBindTexture(GL_TEXTURE_2D, mTexid);

        if (type == eTexType::eDepthTex)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                         width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                         width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        }

        //! 深度比较模式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glGenFramebuffers(1, &mFboid);
        glBindFramebuffer(GL_FRAMEBUFFER, mFboid);

        if (type == eTexType::eDepthTex)
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mTexid, 0);
            glDrawBuffer(GL_NONE); //禁止渲染颜色
            glReadBuffer(GL_NONE);
        }
        else
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexid, 0);
        }

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE)
        {
            printf("bind texture failed !\n");
            throw std::runtime_error("");
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    //! 激活
    void active()
    {
        if(mFboid != MINUSONE)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, mFboid);
        }
    }

    //! 取消激活
    void unactive()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    //! 获取纹理单元
    GLuint texid()const
    {
        return mTexid;
    }
protected:
    GLuint mFboid = MINUSONE;
    GLuint mTexid = MINUSONE;
};

void renderScene(tl::Shader &shader)
{
    static const float grayclr = 0.8f;
    static tl::Drawable<tl::Box> pyramid(1.0f, tl::color_t(1.0f, 0.0f, 0.0f, 1.0f));
    static tl::Drawable<tl::Plane> plane(6.0f, tl::color_t(grayclr, grayclr, grayclr, 1.0f));

    glm::mat4 modelmtrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 0.9)) *
                           glm::rotate(glm::identity<glm::mat4>(), (float)glfwGetTime() * 2.0f, glm::vec3(0, 0, 1)) *
                           glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(0, 1, 0)) *
                           glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(1, 0, 0));
    // glm::mat4 modelmtrix = glm::mat4(1.0);

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
    static tl::Drawable<tl::ScreenPlane> screenplane(WIN_WIDTH, WIN_HEIGHT, unit);
    screen.activate();
    glm::mat4 screenmatrix = glm::ortho(0.0f, (float)WIN_WIDTH, 0.0f, (float)WIN_HEIGHT, 0.0f, 1000.0f);
    screen.bind(UNIFORM_MVP, screenmatrix);
    screenplane.render(screen);
}

//! 光照类型 0 平行光   1 点光源
#define LIGHTTYPE  0
//! 1:显示阴影 0:显示深度贴图
#define SHADOWMODE 1
#define DISPLAYDEPTHMAP  1 //显示深度贴图
int main(int argc, char **argv)
{
    tl::GlfwManager window(WIN_WIDTH, WIN_HEIGHT);
    if(!window.init())
        return -1;

    std::shared_ptr<tl::TextureUnit> unit = std::make_shared<tl::TextureUnit>();
    // if (!unit->generate("/media/tu/Work/OpenGLTest/datas/images/toy_box_diffuse.png"))
    // {
    //     printf("image load error .\n");
    //     return -1;
    // }

    tl::Shader depthshader;
    tl::Shader shader;

#if LIGHTTYPE
    //点光源
    shader.attach("pointlight.vert");
    shader.attach("pointlight.frag");
#else
    //平行光
    shader.attach("shadowmap.vert");
    shader.attach("shadowmap.frag");
#endif
    shader.link();

    depthshader.attach("depth.vert");
    depthshader.attach("depth.frag");

    depthshader.link();
 
    glEnable(GL_MULTISAMPLE);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);//深度截取

    //相机类定义
    tl::camera cam;

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

    OffScreenDrawer off;
    // off.createTextureAndBind( WIN_WIDTH, WIN_HEIGHT, OffScreenDrawer::eTexType::eDepthTex);
    off.createTextureAndBind( SHADOW_SIZE, SHADOW_SIZE, OffScreenDrawer::eTexType::eDepthTex);
    unit->texId = off.texid();
    window.renderLoop([&]()->void
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);       
        // glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        //设置视口
        glViewport(0, 0, SHADOW_SIZE, SHADOW_SIZE);
      
        auto pos = dirlight.dir * 8.0f;
        static float size = 8.0f;
        cam.setProjMatrixByOrtho(-size, size, -size, size,1.0f, 10.0f);
        // cam.setProjMatrixByPrespective(glm::radians(60.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 6.0f, 100.0f);
        cam.setPosition(pos);
        cam.setLookDir(-dirlight.dir);

        glm::mat4 lightspacematrix = cam.getProjMatrix() * cam.getViewMatrix();
        
// 使用阴影贴图
#if SHADOWMODE
        off.active();
        depthshader.activate();
        glClear(GL_DEPTH_BUFFER_BIT );
        depthshader.bind(UNIFORM_PRJMTX, cam.getProjMatrix());
        depthshader.bind(UNIFORM_VIEWMTX, cam.getViewMatrix());
        glCullFace(GL_FRONT);//为了消除偏移过大 悬浮的问题
        renderScene(depthshader);  
        glCullFace(GL_BACK);
        off.unactive();
        
         //设置视口
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
        cam.setProjMatrixByPrespective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 20.0f);
        cam.setPosition(glm::vec3(0.0f, -12.0f, 4.8f));
        cam.setLookDir(-glm::vec3(0.0f, -8.0f, 1.2f));
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        shader.activate();
        shader.bind(UNIFORM_AMBCLR, ambiclr);
        shader.bind(UNIFORM_SPSTRGTH, 0.5f);
        shader.bind(UNIFORM_LGTMTR, lightspacematrix);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, unit->texId);
        shader.bind(UNIFORM_TEXCOORD0, 0);
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
        shader.bind(UNIFORM_PRJMTX, cam.getProjMatrix());
        shader.bind(UNIFORM_VIEWMTX, cam.getViewMatrix());
        renderScene(shader);

#else
        off.active();
        depthshader.activate();
        glClear(GL_DEPTH_BUFFER_BIT );
        depthshader.bind(UNIFORM_PRJMTX, cam.getProjMatrix());
        depthshader.bind(UNIFORM_VIEWMTX, cam.getViewMatrix());

        renderScene(depthshader);   
        
#if DISPLAYDEPTHMAP
        off.unactive();
        glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderScreen(unit);

        //save_gpuimage("/media/tu/Work/OpenGLTest/datas/images/test.png");
#endif

#endif 

       

#if 0
        //spilt window draw diff viewpoint scene
        glViewport(0, 0,  WIN_WIDTH, 0.5 * WIN_HEIGHT);
        auto pos = dirlight.dir * 800.0f;
        static float size = 400.0f;
        cam.setProjMatrixByOrtho(-400, 400, -300, 300,0.0f, 2000.0f);
        shader.bind(UNIFORM_PRJMTX, cam.getProjMatrix());

        cam.setPosition(pos);
        cam.setLookDir(-dirlight.dir);
        shader.bind(UNIFORM_VIEWMTX, cam.getViewMatrix());
        renderScene(shader);
#endif

    });


    // 不注释 退出会发生崩溃
    // glfwTerminate();
    return 0;
}