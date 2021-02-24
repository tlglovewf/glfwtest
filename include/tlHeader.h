#ifndef _TL_HEADER_H_
#define _TL_HEADER_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
namespace tl
{
    typedef glm::vec2 vec2;
    typedef glm::vec3 vec3;
    
    //! 定点坐标
    struct vertex
    {
        vec3 pos;
        vec3 clr;
        vec3 nor;
        vec2 uv;
    };
    //定点缓存
    typedef std::vector<vertex>     VertexVector;
    //索引缓冲
    typedef std::vector<uint8_t>    U8IndiceVector;
    typedef std::vector<uint16_t>   U16IndiceVector;
    typedef std::vector<uint32_t>   U32IndiceVector;
    typedef glm::vec4               color_t;
}
#endif