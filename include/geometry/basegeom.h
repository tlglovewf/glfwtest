#ifndef _BASEGEOM_H_
#define _BASEGEOM_H_
#include <vector>
#include "tlHeader.h"
#include "disablecopyable.h"
namespace tl
{   
    //! 定点坐标
    struct vertex
    {
        glm::vec3 pos;
        glm::vec3 clr;
        glm::vec3 nor;
        glm::vec2 uv;
    };
    //定点缓存
    typedef std::vector<vertex>     VertexVector;
    //索引缓冲
    typedef std::vector<uint8_t>    U8IndiceVector;
    typedef std::vector<uint16_t>   U16IndiceVector;
    typedef std::vector<uint32_t>   U32IndiceVector;

    typedef glm::vec4 ColorType;
    //!基础几何对象
    template<typename INDICETYPE>
    class base_geom : public disablecopyable
    {
    public:
        //! 构建网格
        virtual void build( VertexVector &pts, std::vector<INDICETYPE> &indices) = 0;

        //! 设置全局色彩
        virtual void setglobeColor(const ColorType &) = 0;
    protected:

    };
} // namespace tl

#endif