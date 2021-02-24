#ifndef _TLSHAPES_H_
#define _TLSHAPES_H_
#include <geometry/basegeom.h>
#include <utils/tlFounctions.h>

namespace tl
{
#define L_LINES        0x0001
#define L_LINE_LOOP    0x0002
#define L_LINE_STRIP   0x0003
#define L_TRIANGLES    0x0004
    //! 金字塔
    class Pyramid : public base_geom<uint8_t>
    {
    public:
        //! 构造函数
        Pyramid(float baserd) : base_geom<uint8_t>(baserd) {}

        //! 构建网格
        virtual void build(VertexVector &pts, U8IndiceVector &indices);

        //! 渲染类型
        virtual uint64_t renderType()const {return L_TRIANGLES;}
    };
    
    //! 平面
    class Plane : public base_geom<uint8_t>
    {
    public:
        //! 构造函数
        Plane(float length) : base_geom<uint8_t>(length) {}

        //! 构建网格
        virtual void build(VertexVector &pts, U8IndiceVector &indices);

        //! 渲染类型
        virtual uint64_t renderType()const {return L_TRIANGLES;}
    };

    //! 正方体
    class Box : public base_geom<uint8_t>
    {
    public:
        //! 构造函数
        Box(float length) : base_geom<uint8_t>(length) {}

        //! 构建网格
        virtual void build(VertexVector &pts, U8IndiceVector &indices);

        //! 渲染类型
        virtual uint64_t renderType()const {return L_TRIANGLES;}
    };

    //! 坐标轴
    class Axis : public base_geom<uint8_t>
    {
    public:
       //! 构造函数
       Axis(float length) : base_geom<uint8_t>(length) {}

       //! 构建网格
       virtual void build(VertexVector &pts, U8IndiceVector &indices); 

       //! 渲染类型
       virtual uint64_t renderType()const {return L_LINES;}
    };

    //! 线
    class Line : public base_geom<uint8_t>
    {
    public:
       //! 构造函数
       Line(float length) : base_geom<uint8_t>(length) {}

       //! 构建网格
       virtual void build(VertexVector &pts, U8IndiceVector &indices); 

       //! 渲染类型
       virtual uint64_t renderType()const {return L_TRIANGLES;}
    };

    //! 法线自动生成
    class ShapeNorAutoGenerator final
    {
    public:
        //! 生成
        template<typename T>
        static void generate(VertexVector &pts, const T &indices);
    };
} // namespace tl

#endif