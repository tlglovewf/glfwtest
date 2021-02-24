#include<iostream>
#include<tlWindow.h>
#include<tlHeader.h>
#include <render/tlLight.h>
#include<utils/tlFounctions.h>
#include<glm/gtx/string_cast.hpp>
#include<vector>
using namespace std;

template<typename T>
bool juageType( T t)
{
    
}

class Te
{
public:
    template<typename T>
    void add(T a, T b)
    {
        std::cout << "T" << std::endl;
    }
};
template<>
void Te::add<int>(int a, int b)
{
    std::cout << "I" << std::endl;
}
int main(int argc, char **argv)
{
    // glm::vec3 a(0 , 0 , 0);
    // glm::vec3 b(10, 0 , 0);
    // glm::vec3 c(10, 10, 0);

    // std::cout << glm::to_string(tl::Founctions::calcnor(a, b, c)) << std::endl;

    // auto mat = glm::scale(glm::identity<glm::mat4>(),glm::vec3(1, 2, 3));
    // std::cout << glm::to_string(mat) << std::endl;

    // std::cout << glm::to_string(glm::inverse(mat)) << std::endl;
    // std::cout << glm::to_string(glm::transpose(mat)) << std::endl;

    std::cout << sizeof(glm::vec3) << std::endl;
    return 0;
}