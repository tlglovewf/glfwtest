#include "tlWindowImpl.h"
#include <stdexcept>
#include <functional>
#include <GLFW/glfw3.h>
namespace tl
{
    WindowImpl::WindowImpl(const std::string &name, uint16_t width, uint16_t height)
    {
        if(!glfwInit())
            throw std::runtime_error("glfw initilize failed!");
        //多重采样
        glfwWindowHint(GLFW_SAMPLES, 4);
        //深度缓冲区大小
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
        mpWin = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        glfwMakeContextCurrent(mpWin);
        glfwSwapInterval(1); //垂直同步

        initilize();
    }

    WindowImpl::~WindowImpl()
    {
        if (nullptr != mpWin)
        {
            glfwTerminate();
            glfwDestroyWindow(mpWin);
        }
    }
    typedef struct gltest gltest;

    WindowImpl *impl = nullptr;
    //! 初始化
    void WindowImpl::initilize()
    {
        impl = this;
        glfwSetErrorCallback([](int error, const char *description)->void
        {
            printf("error code : %d, error info : %s \n", error, description);
        });

        glfwSetMouseButtonCallback(mpWin,[](GLFWwindow *window, int x, int y, int z)
        {
            impl->mousecb(window,x, y, z);
        });

        glfwSetKeyCallback(mpWin,[](GLFWwindow *win, int key,int scancode, int action,int mods)->void
        {
            impl->keycb(win,key,scancode,action,mods);
        });
    }

    //渲染循环
    void WindowImpl::renderLoop()
    {

        while (!glfwWindowShouldClose(mpWin))
        {
            int width, height;
            //获取长宽
            glfwGetFramebufferSize(mpWin, &width, &height);

            // glClear(GL_COLOR_BUFFER_BIT);

            // glClearColor(1.0, 0, 0, 1.0);
     

            glfwSwapBuffers(mpWin);

            glfwPollEvents();
        }
    }

    void WindowImpl::keycb(GLFWwindow *window, int key,int scancode, int action,int mods)
    {
        printf("key cb\n");
    }

    void WindowImpl::mousecb(GLFWwindow *window, int x, int y, int z)
    {
        printf(" mouse x = %d, y = %d, z = %d\n", x, y, z);
    }
} // namespace tl