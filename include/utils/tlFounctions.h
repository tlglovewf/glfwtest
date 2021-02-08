#ifndef _FOUNCTION_H_
#define _FOUNCTION_H_

namespace tl
{

    //! 工具函数类
    class Founctions final
    {
    public:
       /*
        * 计算三角面片法线
        * @param  a b c 三角片逆时针顺序三个点
        * @return 单位化法线
        */
       static glm::vec3 calcnor(const glm::vec3 &a,
                          const glm::vec3 &b,
                          const glm::vec3 &c)
        {
            glm::vec3 ab = b - a;

            glm::vec3 bc = c - b;

            return glm::normalize(glm::cross(ab, bc));
        }

    private:
        Founctions() = delete;
    };

} // namespace tl

#endif