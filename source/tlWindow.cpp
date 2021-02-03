#include "tlWindow.h"
#include "tlWindowImpl.h"

namespace tl
{
    Window::Window(const std::string &name, uint16_t width, uint16_t height) : mpImpl(new WindowImpl(name, width, height))
    {
    }
    Window::~Window()
    {
    }

    void Window::renderLoop()
    {
        mpImpl->renderLoop();
    }
} // namespace tl