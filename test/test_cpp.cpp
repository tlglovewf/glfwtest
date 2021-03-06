#include<iostream>
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

inline float CalcDepth(float z, float near, float far)
{
   return z;
    // float zdiff = far - near;
    // float interpolatedepth = z * far * near / zdiff + 0.5 * (far + near) / zdiff + 0.5;
    // return pow(interpolatedepth, 15.0);
    // float win_depth = (z + 1.0) / 2.0;
    // return zdiff * win_depth + near;

    // return (( (far - near) * z ) + near + far) * 0.5; 
}




int main(int argc, char **argv)
{
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 4.0f, -1.0f),glm::vec3(0.0f),glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 prj  = glm::perspective(glm::radians(45.0), 800.0 / 600.0, 0.0, 1000.0);
    glm::mat4 modelmtrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 90)) *
                       glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(0, 1, 0)) *
                       glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(1, 0, 0));

    glm::mat4  mvp = prj * view ;
    const float half_len = (600.0f / 2.0f);
    tl::vertex vtx;
    glm::vec4 temp;
    glm::vec3 ret ;
    float near = 0.0;
    float far  = 2.0f;
    vtx.pos = {-half_len, -half_len, -0.0f};
    temp = mvp * glm::vec4(vtx.pos,1.0);
    ret = temp / temp.w;
    ret.z = CalcDepth(ret.z, near, far);
    std::cout << glm::to_string(ret) << std::endl;
    vtx.pos = {half_len, -half_len, -0.0f};
    temp = mvp * glm::vec4(vtx.pos,1.0);
    ret = temp / temp.w;
    ret.z = CalcDepth(ret.z, near, far);
    std::cout << glm::to_string(ret) << std::endl;
    vtx.pos = {half_len, half_len, -0.0f};
    temp = mvp * glm::vec4(vtx.pos,1.0);
    ret = temp / temp.w;
    ret.z = CalcDepth(ret.z, near, far);
    std::cout << glm::to_string(ret) << std::endl;
    vtx.pos = {-half_len, half_len, -0.0f};
    temp = mvp * glm::vec4(vtx.pos,1.0);
    ret = temp / temp.w;
    ret.z = CalcDepth(ret.z, near, far);
    std::cout << glm::to_string(ret) << std::endl;


    return 0;
}