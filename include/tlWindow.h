#ifndef _HANDLE_H_
#define _HANDLE_H_

#include <memory>
#include "disablecopyable.h"
namespace tl
{
    class WindowImpl;
    //! glfw窗口
    class Window final : public disablecopyable
    {
    public:
        explicit Window(const std::string &name, uint16_t width, uint16_t height);
        ~Window();

        //渲染循环
        void renderLoop();
    protected:
        const std::unique_ptr<WindowImpl> mpImpl;
    };

} // namespace tl
#endif