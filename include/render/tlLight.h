#ifndef _LIGHT_H_
#define _LIGHT_H_
#include <tlHeader.h>
namespace tl
{
    enum class LightType
    {
        DirLight,
        PointLight,
        SpotLight,
        UnknowLight
    };

    //! 灯光
    struct BaseLight
    {
        BaseLight() = default;
        virtual ~BaseLight() = default;
        //! 颜色
        color_t     clr;

        //! 类型
        virtual LightType type()const { return LightType::UnknowLight;}
    };

    //! 平行光
    struct DirLight : public BaseLight
    {
        //! 方向
        vec3    dir;
        //! 类型
        virtual LightType type()const { return LightType::DirLight;}
    };

    //! 点光源
    struct PointLight : public BaseLight
    {   
        //! 位置
        vec3 pos;

        //! 类型
        virtual LightType type()const { return LightType::PointLight;}
    };
    
    //! 聚光灯
    struct SpotLight : public PointLight
    {
        //add more data
        //! 类型
        virtual LightType type()const { return LightType::SpotLight;}
    };
}

#endif