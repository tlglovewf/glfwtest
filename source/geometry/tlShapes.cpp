#include <stdio.h>
#include <utils/tlFounctions.h>
#include <geometry/tlShapes.h>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
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
        vtx.pos += _pos;
        pts.emplace_back(vtx);
        vtx.pos = {1.0f * _axisLen, 0.0f, -0.5774f * _axisLen};
        vtx.pos += _pos;
        pts.emplace_back(vtx);
        vtx.pos = {0.0f, 0.0f, 1.154f * _axisLen};
        vtx.pos += _pos;
        pts.emplace_back(vtx);
        vtx.pos = {0.0f, 1.732f * _axisLen, 0.0f};
        vtx.pos += _pos;
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
        vtx.pos += _pos;
        pts.emplace_back(vtx);
        vtx.pos = {half_len, -half_len, -0.0f};
        vtx.pos += _pos;
        pts.emplace_back(vtx);
        vtx.pos = {half_len, half_len, -0.0f};
        vtx.pos += _pos;
        pts.emplace_back(vtx);
        vtx.pos = {-half_len, half_len, -0.0f};
        vtx.pos += _pos;
        pts.emplace_back(vtx);

        indices = {0, 1, 2,
                   0, 2, 3};

        ShapeNorAutoGenerator::generate(pts,indices);
    }

    //! 构建网格
    void ScreenPlane::build(VertexVector &pts, U8IndiceVector &indices)
    {
        pts.reserve(4);
        assert(_width > 0 && _height > 0);
        vertex vtx;
        vtx.pos = {0.0f, 0.0f, 0.0f};
        vtx.uv = {0.0f, 1.0f};
        pts.emplace_back(vtx);
        vtx.pos = {_width, 0.0f, 0.0f};
        vtx.uv = {1.0f, 1.0f};
        pts.emplace_back(vtx);
        vtx.pos = {_width, _height, 0.0f};
        vtx.uv = {1.0f, 0.0f};
        pts.emplace_back(vtx);
        vtx.pos = {0.0f, _height, 0.0f};
        vtx.uv = {0.0f, 0.0f};
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
        vtx.pos += _pos;
        pts.emplace_back(vtx);

        vtx.pos = { half_len, -half_len, half_len};
        vtx.pos += _pos;
        pts.emplace_back(vtx);

        vtx.pos = { half_len,  half_len, half_len};
        vtx.pos += _pos;
        pts.emplace_back(vtx);

        vtx.pos = {-half_len,  half_len, half_len};
        vtx.pos += _pos;
        pts.emplace_back(vtx);

        vtx.pos = {-half_len, -half_len,-half_len};
        vtx.pos += _pos;
        pts.emplace_back(vtx);

        vtx.pos = { half_len, -half_len,-half_len};
        vtx.pos += _pos;
        pts.emplace_back(vtx);

        vtx.pos = { half_len,  half_len,-half_len};
        vtx.pos += _pos;
        pts.emplace_back(vtx);

        vtx.pos = {-half_len,  half_len,-half_len};
        vtx.pos += _pos;
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
        ShapeNorAutoGenerator::generate(pts,indices);
    }

    //! 构建网格
    void Axis::build(VertexVector &pts, U8IndiceVector &indices)
    {
        pts.reserve(4);
        indices.reserve(6);

        vertex vtx;
        vtx.clr = color_t(1.0f, 0.0f, 0.0f, 1.0f);
        vtx.pos = {0.0f, 0.0f, 0.0f};
        vtx.pos += _pos;
        pts.emplace_back(vtx);
        vtx.clr = color_t(0.0f, 1.0f, 0.0f, 1.0f);
        vtx.pos = {0.0f, 0.0f, 0.0f};
        vtx.pos += _pos;
        pts.emplace_back(vtx);
        vtx.clr = color_t(0.0f, 0.0f, 1.0f, 1.0f);
        vtx.pos = {0.0f, 0.0f, 0.0f};
        vtx.pos += _pos;
        pts.emplace_back(vtx);

        vtx.clr = color_t(1.0f, 0.0f, 0.0f, 1.0f);
        vtx.pos = {_axisLen, 0.0f, 0.0f};
        vtx.pos += _pos;
        pts.emplace_back(vtx);

        vtx.clr = color_t(0.0f, 1.0f, 0.0f, 1.0f);
        vtx.pos = {0.0f, _axisLen, 0.0f};
        vtx.pos += _pos;
        pts.emplace_back(vtx);

        vtx.clr = color_t(0.0f, 0.0f, 1.0f, 1.0f);
        vtx.pos = {0.0f, 0.0f, _axisLen};
        vtx.pos += _pos;
        pts.emplace_back(vtx);
        
        indices = {0, 3, 1, 4, 2, 5};
    }

    //! 构建网格
    void Line::build(VertexVector &pts, U8IndiceVector &indices)
    {
        float half_len = _axisLen / 2.0f;

      
    }
    template<typename T>
    void ShapeNorAutoGenerator::generate(VertexVector &pts, const T &indices)
    {
        static_assert( std::is_same<T,U8IndiceVector>::value |
                       std::is_same<T,U16IndiceVector>::value|
                       std::is_same<T,U32IndiceVector>::value,"indices type error.");

        if(!pts.empty() && 
           !indices.empty())
           {
               for(size_t i = 0; i < indices.size(); i += 3)
               {
                    vec3 nor = std::move(tl::Founctions::calcnor(pts[indices[i + 0]].pos, 
                                                                 pts[indices[i + 1]].pos,
                                                                 pts[indices[i + 2]].pos));
                    pts[indices[i + 0]].nor += nor;
                    pts[indices[i + 1]].nor += nor;
                    pts[indices[i + 2]].nor += nor;

               }
           }

    }
} // namespace tl
