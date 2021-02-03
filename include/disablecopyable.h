#ifndef _DISABLECOPYABLE_H_
#define _DISABLECOPYABLE_H_

namespace tl
{
    //! 禁止拷贝类
    class disablecopyable
    {
    public:
        disablecopyable() = default;
        virtual ~disablecopyable() = default;
        disablecopyable(const disablecopyable&) = delete;
        disablecopyable& operator=(const disablecopyable&) = delete;
    };
}

#endif