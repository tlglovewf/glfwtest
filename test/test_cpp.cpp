#include<iostream>
#include<tlWindow.h>
using namespace std;


class test
{
public:
    void display()const
    {
        static int idx = 0;
        std::cout << idx++ << std::endl;
    }
};

int main(int argc, char **argv)
{
    test test1;
    test test2;
    test1.display();
    test2.display();
    return 0;
}