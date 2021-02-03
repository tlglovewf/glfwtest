#ifndef _TLSHAPES_H_
#define _TLSHAPES_H_
#include <geometry/basegeom.h>

namespace tl
{
    //! 金字塔
    class Pyramid : public base_geom<uint8_t>
    {
    public:
        Pyramid(float baserd) : mbase(baserd) {}

        //! 构建网格
        virtual void build(VertexVector &pts, U8IndiceVector &indices)
        {
            pts.reserve(4);
            indices.reserve(12);

            vertex vtx;
            vtx.clr = mclr;
            vtx.pos = {-1.0f * mbase, 0.0f, -0.5774f * mbase};
            pts.emplace_back(vtx);
            vtx.pos = {1.0f * mbase, 0.0f, -0.5774f * mbase};
            pts.emplace_back(vtx);
            vtx.pos = {0.0f, 0.0f, 1.154f * mbase};
            pts.emplace_back(vtx);
            vtx.pos = {0.0f, 1.732f * mbase, 0.0f};
            pts.emplace_back(vtx);

            indices = {0, 1, 3,
                       1, 2, 3,
                       2, 0, 3,
                       0, 1, 2};
        }

        //! 设置全局色彩
        virtual void setglobeColor(const ColorType &clr) override
        {
            mclr = clr;
        }

    protected:
        float           mbase;
        tl::ColorType   mclr;
    };
    
    //! 平面
    class Plane : public base_geom<uint8_t>
    {
    public:
        Plane(float length):mradius(length){}

        //! 构建网格
        virtual void build(VertexVector &pts, U8IndiceVector &indices)
        {
            pts.reserve(4);
            indices.reserve(6);
            const float half_len = (mradius / 2.0f);
            vertex vtx;
            vtx.clr = mclr;
            vtx.pos = { -half_len, -half_len, 0.0f};
            pts.emplace_back(vtx);
            vtx.pos = { -half_len,  half_len, 0.0f};
            pts.emplace_back(vtx);
            vtx.pos = {  half_len,  half_len, 0.0f};
            pts.emplace_back(vtx);
            vtx.pos = { -half_len,  half_len, 0.0f};
            pts.emplace_back(vtx);

            indices = {0, 1, 3,
                       1, 2, 3};
        }

        //! 设置全局色彩
        virtual void setglobeColor(const ColorType &clr) override
        {
            mclr = clr;
        }
    protected:
        float         mradius;
        tl::ColorType mclr;
    };
} // namespace tl

#endif