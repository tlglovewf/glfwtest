#ifndef  _WINMGR_H_
#define  _WINMGR_H_
#include <GLFW/glfw3.h>
namespace tl{
#define DEBUGINFO std::cout
    //glfw 窗口管理
class GlfwManager final
{
public:
    GlfwManager(const GlfwManager&) = delete;
    GlfwManager& operator =(const GlfwManager&) = delete;
    
    GlfwManager(int width, int height):_win(nullptr),_width(width),_height(height)
    {
        
    }
    ~GlfwManager()
    {
        if(_win)
            glfwDestroyWindow(_win);
    }

    //初始化
    bool init()
    {
        if(!glfwInit())
        {
            DEBUGINFO << "glfw init failed.";
            return false;
        }
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);

        _win = glfwCreateWindow(_width, _height, "Hello OpenGL", NULL, NULL);

         if (!_win)
        {
            DEBUGINFO << "Create window failed." ;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(_win);

        if(!gladLoadGL())
        {
            DEBUGINFO << "glad init failed.";
            return false;
        }

         glfwSetErrorCallback([](int error, const char *description) -> void {
                DEBUGINFO << "error : " << error << " " << description ;});


        return true;
    }

    template<typename Func>
    void renderLoop(Func f)
    {
        while(!glfwWindowShouldClose(_win))
        {
            f();
            glfwSwapBuffers(_win);
            glfwPollEvents();
        }
    }
protected:
    GLFWwindow *_win;

    uint16_t _width;
    uint16_t _height;

};
}

#endif