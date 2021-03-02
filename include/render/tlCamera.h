#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <tlHeader.h>
namespace tl
{
    class camera : public moveable
    {
    public:
        //! 获取世界变换矩阵
        glm::mat4 getMVP() const { return _projMatrix * _viewMatrix * _modelMatrix; }

        //! 获取投影矩阵
        glm::mat4 getProjMatrix() const
        {
            return _projMatrix;
        }
        //! 设置投影矩阵
        void setProjMatrix(const glm::mat4 &matrix)
        {
            _projMatrix = matrix;
        }

        //! 设置投影矩阵
        void setProjMatrixByPrespective(float fov, float ratio, float fNear, float fFar)
        {
            _projMatrix = glm::perspective(fov, ratio, fNear, fFar);
        }

        //! 设置投影矩阵
        void setProjMatrixByOrtho(float left, float right, float bottom, float top, float near = 0.0f, float far = 100.0f)
        {
            _projMatrix = glm::ortho(left, right, bottom, top, near, far);
        }

        //! 获取视图矩阵
        glm::mat4 getViewMatrix() const
        {
            return _viewMatrix;
        }

        //! 设置视图矩阵
        void setViewMatrix(const glm::mat4 &matrix)
        {
            _viewMatrix = matrix;
        }

        //! 设置视图矩阵
        void setViewMatrix(const glm::vec3 &eye, const glm::vec3 &target, const glm::vec3 &up)
        {
            _viewMatrix = glm::lookAt(eye, target, up);
        }
        //! 设置观察方向
        void setLookDir(const glm::vec3& dir)
        {
            glm::vec3 target = mPos + dir;
            //默认设置y向上为正方向
            setViewMatrix(mPos, target, glm::vec3(0, 1, 0));
        }

        //! 获取模型矩阵
        glm::mat4 getModelMatrix() const
        {
            return _modelMatrix;
        }

        //! 设置模型矩阵
        void setModelMatrix(const glm::mat4 &matrix)
        {
            _modelMatrix = matrix;
        }

    protected:
        glm::mat4 _modelMatrix = glm::identity<glm::mat4>();

        glm::mat4 _viewMatrix = glm::identity<glm::mat4>();

        glm::mat4 _projMatrix = glm::identity<glm::mat4>();
    };
} // namespace tl

#endif