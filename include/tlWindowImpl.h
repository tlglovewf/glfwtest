#ifndef _IMPL_H_
#define _IMPL_H_
#include <string>
#include <disablecopyable.h>
struct GLFWwindow;
namespace tl
{
    class WindowImpl : public disablecopyable
    {
    public:
        WindowImpl(const std::string &name, uint16_t width, uint16_t height);
        virtual ~WindowImpl();
        //渲染循环
        void renderLoop();
    protected:
        //! 初始化
        virtual void initilize(); 
        //! 键盘消息回调
        void keycb(GLFWwindow *window, int, int, int, int);
        //! 鼠标消息回调    
        void mousecb(GLFWwindow *window, int, int, int);
    protected:
        GLFWwindow *mpWin = nullptr;
    };
} // namespace tl

#endif