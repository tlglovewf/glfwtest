#ifndef _HANDLE_H_
#define _HANDLE_H_

#include <memory>


class impl;
class handle
{
public:
    explicit handle();
    ~handle();

protected:

   const std::unique_ptr<impl> mpImpl;
};


#endif