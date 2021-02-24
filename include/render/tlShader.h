#pragma once

// System Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Headers
#include <string>
#include <render/tlConstants.h>
// Define Namespace
namespace tl
{
    class Shader
    {
    public:
        // Implement Custom Constructor and Destructor
        Shader() { mProgram = glCreateProgram(); }
        ~Shader() { glDeleteProgram(mProgram); }

        // Public Member Functions
        void activate();
        bool attach(std::string const &filename);
        GLuint create(std::string const &filename);
        GLuint get() { return mProgram; }
        bool link();

        template <typename T>
        void bind(unsigned int location, const T &value)
        {
            if(std::is_same<T, glm::vec4>::value)
            {
                glUniform4fv(location, 1, glm::value_ptr(value));
            }
        }

        template <typename T>
        Shader &bind(std::string const &name, T &&value)
        {
            int location = glGetUniformLocation(mProgram, name.c_str());
            if (location == -1)
                fprintf(stderr, "Missing Uniform: %s\n", name.c_str());
            else
                bind(location, std::forward<T>(value));
            return *this;
        }
        GLuint uniformloc(const std::string &name)
        {
            return glGetUniformLocation(mProgram, name.c_str());
        }

        inline GLuint attriloc(const std::string &name)
        {
            return glGetAttribLocation(mProgram, name.c_str());
        }

        //! 世界矩阵坐标
        inline GLint mvpLoc()
        {
            if (mMvpLoc < 0)
            {
                mMvpLoc = uniformloc(UNIFORM_MVP);
            }
            return mMvpLoc;
        }

        //! 获取定点位置
        inline GLint vertexLoc()
        {
            if (mVtxLoc < 0)
            {
                mVtxLoc = attriloc(ATTR_VERTEX);
            }
            return mVtxLoc;
        }

        //! 获取颜色位置
        inline GLint colorLoc()
        {
            if (mClrLoc < 0)
            {
                mClrLoc = attriloc(ATTR_COLOR);
            }
            return mClrLoc;
        }

        //! 获取纹理位置
        inline GLint textureLoc()
        {
            if (mUvLoc < 0)
            {
                mUvLoc = attriloc(ATTR_TEXTURE0);
            }
            return mUvLoc;
        }

        //! 获取法线位置
        inline GLint normalLoc()
        {
            if (mNorLoc < 0)
            {
                mNorLoc = attriloc(ATTR_NORMAL);
            }
            return mNorLoc;
        }

    private:
        // Disable Copying and Assignment
        Shader(Shader const &) = delete;
        Shader &operator=(Shader const &) = delete;

        // Private Member Variables
        GLuint mProgram;
        GLint mStatus;
        GLint mLength;

        GLint mMvpLoc = -1;
        GLint mVtxLoc = -1;
        GLint mClrLoc = -1;
        GLint mUvLoc = -1;
        GLint mNorLoc = -1;
    };
}; // namespace tl
