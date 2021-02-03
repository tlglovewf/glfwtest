#pragma once

// System Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Headers
#include <string>

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
        bool attach(std::string const & filename);
        GLuint   create(std::string const & filename);
        GLuint   get() { return mProgram; }
        bool link();

        // Wrap Calls to glUniform
        void bind(unsigned int location, float value);
        void bind(unsigned int location, glm::mat4 const & matrix);
        template<typename T> 
        Shader & bind(std::string const & name, T&& value)
        {
            int location = glGetUniformLocation(mProgram, name.c_str());
            if (location == -1) fprintf(stderr, "Missing Uniform: %s\n", name.c_str());
            else bind(location, std::forward<T>(value));
            return *this;
        }
        GLuint uniformloc(const std::string &name)
        {
            return glGetUniformLocation(mProgram, name.c_str());
        }

        GLuint attriloc(const std::string &name)
        {
            return glGetAttribLocation(mProgram,name.c_str());
        }
    private:

        // Disable Copying and Assignment
        Shader(Shader const &) = delete;
        Shader & operator=(Shader const &) = delete;

        // Private Member Variables
        GLuint mProgram;
        GLint  mStatus;
        GLint  mLength;

    };
};
