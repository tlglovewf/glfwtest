#ifndef _BASEGEOM_H_
#define _BASEGEOM_H_
#include <vector>
#include "tlHeader.h"
#include "disablecopyable.h"
namespace tl
{   
    //!基础几何对象
    template<typename INDICETYPE>
    class base_geom : public disablecopyable
    {
    public:
        using Type = INDICETYPE;
        //! 构造函数
        base_geom(float len,const vec3 &pos = {0.0f, 0.0f, 0.0f}):_axisLen(len),_pos(pos){}

        //! 构建网格
        virtual void build( VertexVector &pts, std::vector<INDICETYPE> &indices) = 0;

        //! 设置全局色彩
        virtual void setglobeColor(const color_t &v) {_color = v;}

        //! 渲染类型
        virtual uint64_t renderType()const = 0;

    protected:
        float       _axisLen;
        vec3        _pos;
        color_t     _color;
    };
} // namespace tl

#endif