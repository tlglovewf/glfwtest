#include <stdio.h>
#include <geometry/tlShapes.h>
namespace tl
{
    //! 构建网格
    void Pyramid::build(VertexVector &pts, U8IndiceVector &indices)
    {
        pts.reserve(4);
        indices.reserve(12);

        vertex vtx;
        vtx.clr = _color;
        vtx.pos = {-1.0f * _axisLen, 0.0f, -0.5774f * _axisLen};
        pts.emplace_back(vtx);
        vtx.pos = {1.0f * _axisLen, 0.0f, -0.5774f * _axisLen};
        pts.emplace_back(vtx);
        vtx.pos = {0.0f, 0.0f, 1.154f * _axisLen};
        pts.emplace_back(vtx);
        vtx.pos = {0.0f, 1.732f * _axisLen, 0.0f};
        pts.emplace_back(vtx);

        indices = {0, 1, 3,
                   0, 2, 3,
                   1, 2, 3,
                   0, 3, 2};
    }

    //! 构建网格
    void Plane::build(VertexVector &pts, U8IndiceVector &indices)
    {
        pts.reserve(4);
        indices.reserve(6);
        const float half_len = (_axisLen / 2.0f);
        vertex vtx;
        vtx.clr = _color;
        vtx.pos = {-half_len, -half_len, -0.0f};
        pts.emplace_back(vtx);
        vtx.pos = {half_len, -half_len, -0.0f};
        pts.emplace_back(vtx);
        vtx.pos = {half_len, half_len, -0.0f};
        pts.emplace_back(vtx);
        vtx.pos = {-half_len, half_len, -0.0f};
        pts.emplace_back(vtx);

        indices = {0, 1, 2,
                   0, 2, 3};
    }

    //! 构建网格
    void Box::build(VertexVector &pts, U8IndiceVector &indices)
    {
        pts.reserve(8);
        indices.reserve(12);

        const float half_len = (_axisLen / 2.0f);

        vertex vtx;
        vtx.clr = _color;

        //build vertices buffer 
        vtx.pos = {-half_len, -half_len, half_len};
        pts.emplace_back(vtx);

        vtx.pos = { half_len, -half_len, half_len};
        pts.emplace_back(vtx);

        vtx.pos = { half_len,  half_len, half_len};
        pts.emplace_back(vtx);

        vtx.pos = {-half_len,  half_len, half_len};
        pts.emplace_back(vtx);

        vtx.pos = {-half_len, -half_len,-half_len};
        pts.emplace_back(vtx);

        vtx.pos = { half_len, -half_len,-half_len};
        pts.emplace_back(vtx);

        vtx.pos = { half_len,  half_len,-half_len};
        pts.emplace_back(vtx);

        vtx.pos = {-half_len,  half_len,-half_len};
        pts.emplace_back(vtx);

        //build indices buffer
        indices = {//前方
                   0, 1, 2,
                   2, 3, 0,
                   //右方
                   1, 5, 6,
                   6, 2, 1,
                   //后方
                   6, 5, 4,
                   7, 6, 4,
                   //左方
                   4, 0, 3,
                   3, 7, 4,
                   //上方
                   3, 2, 6,
                   6, 7, 3,
                   //下方
                   4, 5, 1,
                   1, 0, 4
                   };

    }

    //! 构建网格
    void Axis::build(VertexVector &pts, U8IndiceVector &indices)
    {
        pts.reserve(4);
        indices.reserve(6);

        vertex vtx;
        vtx.clr = ColorType(1.0f, 0.0f, 0.0f, 1.0f);
        vtx.pos = {0.0f, 0.0f, 0.0f};
        pts.emplace_back(vtx);
        vtx.clr = ColorType(0.0f, 1.0f, 0.0f, 1.0f);
        vtx.pos = {0.0f, 0.0f, 0.0f};
        pts.emplace_back(vtx);
        vtx.clr = ColorType(0.0f, 0.0f, 1.0f, 1.0f);
        vtx.pos = {0.0f, 0.0f, 0.0f};
        pts.emplace_back(vtx);

        vtx.clr = ColorType(1.0f, 0.0f, 0.0f, 1.0f);
        vtx.pos = {_axisLen, 0.0f, 0.0f};
        pts.emplace_back(vtx);

        vtx.clr = ColorType(0.0f, 1.0f, 0.0f, 1.0f);
        vtx.pos = {0.0f, _axisLen, 0.0f};
        pts.emplace_back(vtx);

        vtx.clr = ColorType(0.0f, 0.0f, 1.0f, 1.0f);
        vtx.pos = {0.0f, 0.0f, _axisLen};
        pts.emplace_back(vtx);
        
        indices = {0, 3, 1, 4, 2, 5};
    }

    //! 构建网格
    void Line::build(VertexVector &pts, U8IndiceVector &indices)
    {
        float half_len = _axisLen / 2.0f;

      
    }
} // namespace tl
