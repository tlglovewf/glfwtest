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
        //! 方向(指向光源方向)
        vec3    dir;
        //! 类型
        virtual LightType type()const { return LightType::DirLight;}
    };

    //! 点光源
    struct PointLight : public BaseLight
    {   
        //! 位置
        vec3 pos;

        //! 衰减强度 [0,1] 越大衰减越快
        float fade = 0.0;
        //! 类型
        virtual LightType type()const { return LightType::PointLight;}
    };
    
    //! 聚光灯
    struct SpotLight : public virtual PointLight, public virtual DirLight
    {
        //! 夹角
        float angle = 0.0;
        //! 类型
        virtual LightType type()const { return LightType::SpotLight;}
    };
}

#endif