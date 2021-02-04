#include <iostream>
#include <iomanip>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/string_cast.hpp>

#include <render/tlShader.h>
#include <render/tlConstants.h>
#include <geometry/tlShapes.h>
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

template <typename IdxType>
struct GpuDrawable
{
    
    GLuint                  vboIdx = ErrorValue;
    GLuint                  eboIdx = ErrorValue;
    tl::VertexVector        vertices;
    std::vector<IdxType>    indices;

    static constexpr GLuint ErrorValue = -1;
    inline bool check(GLuint v){return (v != ErrorValue);}
};

template <typename Shape, typename IdxType, typename In>
class Drawable
{
public:
    Drawable(In in, const tl::ColorType &clr)
    {
        Shape shape(in);
        shape.setglobeColor(clr);

        shape.build(_value.vertices, _value.indices);

        glGenBuffers(1, &_value.vboIdx);
        glBindBuffer(GL_ARRAY_BUFFER, _value.vboIdx);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tl::vertex) *_value.vertices.size(), &_value.vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &_value.eboIdx);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _value.eboIdx);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint8_t) * _value.indices.size(), &_value.indices[0], GL_STATIC_DRAW);
    }

    ~Drawable()
    {
        if(_value.check(_value.vboIdx))
        {
            glDeleteBuffers(1,&_value.vboIdx);
        }

        if(_value.check(_value.eboIdx))
        {
            glDeleteBuffers(1, &_value.eboIdx);
        }
    }
    //! 获取gpu渲染对象
    const GpuDrawable<IdxType> &get() const
    {
        return _value;
    }
    //! 获取渲染点数量
    inline size_t renderSize()const
    {
        return _value.indices.size(); 
    }

    //!绑定执行
    void active()
    {
        if( _value.vboIdx > 0 &&
            _value.eboIdx >0)
            {
                glBindBuffer(GL_ARRAY_BUFFER, _value.vboIdx);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _value.eboIdx);
            }
    }
    //! 绘制
    void render(tl::Shader &shader)
    {
        shader.activate();

        active();

        glEnableVertexAttribArray(shader.vertexLoc());
        glVertexAttribPointer(shader.vertexLoc(), 3, GL_FLOAT, GL_FALSE, sizeof(tl::vertex), (void *)0);
        glEnableVertexAttribArray(shader.colorLoc());
        glVertexAttribPointer(shader.colorLoc(), 3, GL_FLOAT, GL_FALSE, sizeof(tl::vertex), (void *)(sizeof(float) * 3));

        if(std::is_same<IdxType, uint8_t>::value)
        {
            glDrawElements(GL_TRIANGLES, renderSize(), GL_UNSIGNED_BYTE , NULL);
        }
        else if(std::is_same<IdxType, uint16_t>::value)
        {
            glDrawElements(GL_TRIANGLES, renderSize(), GL_UNSIGNED_SHORT, NULL);
        }
        else
        {
            glDrawElements(GL_TRIANGLES, renderSize(), GL_UNSIGNED_INT  , NULL);
        }
    }
protected:
    GpuDrawable<IdxType> _value;
};


class camera
{
public:
    //! 获取世界变换矩阵
    glm::mat4 getMVP()const { return _projMatrix * _viewMatrix * _modelMatrix ;}

    //! 获取投影矩阵
    glm::mat4 getProjMatrix()const
    {
        return _projMatrix;
    }
    //! 设置投影矩阵
    void setProjMatrix( const glm::mat4 &matrix)
    {
        _projMatrix = matrix;
    }

    //! 设置投影矩阵
    void setProjMatrixByPrespective(float fov, float ratio, float fNear, float fFar)
    {
        _projMatrix = glm::perspective( fov, ratio, fNear, fFar);
    }

    //! 设置投影矩阵
    void setProjMatrixByOrtho(float left, float right, float bottom, float top)
    {
        _projMatrix = glm::ortho(left, right, bottom, top);
    }
    
    //! 获取视图矩阵
    glm::mat4 getViewMatrix()const
    {
        return _viewMatrix;
    }

    //! 设置视图矩阵
    void setViewMatrix( const glm::mat4 &matrix ) 
    {
        _viewMatrix = matrix;
    }

    //! 设置视图矩阵
    void setViewMatrix( const glm::vec3 &eye, const glm::vec3 &target, const glm::vec3 &up)
    {
        _viewMatrix = glm::lookAt( eye, target, up);
    }

    //! 获取模型矩阵
    glm::mat4 getModelMatrix()const
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

    glm::mat4 _viewMatrix  = glm::identity<glm::mat4>();

    glm::mat4 _projMatrix  = glm::identity<glm::mat4>();
};

int main(int argc, char **argv)
{
    GLFWwindow *window = nullptr;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    window = glfwCreateWindow(800, 600, "This is first glfw program", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) //!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "load glad failed!" << std::endl;
        return -1;
    }

    glfwSwapInterval(1); //垂直同步
    glfwSetErrorCallback([](int error, const char *description) -> void {
        std::cout << "error : " << error << " " << description << std::endl;
    });

    if (!window)
    {
        std::cout << "Create window failed." << std::endl;
        glfwTerminate();
        return -1;
    }

    Drawable<tl::Pyramid, uint8_t, float>      pyramid(100.0f , glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    Drawable<tl::Plane, uint8_t, float>        plane  (600.0f , glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    
    tl::Shader shader;
    shader.attach("normal.vert");
    shader.attach("normal.frag");
    shader.link();

    glEnable(GL_MULTISAMPLE);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable()

    camera cam;
    cam.setProjMatrixByPrespective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 2000.0f);
    cam.setViewMatrix(glm::vec3(0.0f, -800.0f, 400.0f), glm::vec3(0, 0, 100), glm::vec3(0, 1, 0));

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        //获取长宽
        glfwGetFramebufferSize(window, &width, &height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 206.0f / 255.0f, 1.0f);

        glm::mat4 modelmtrix =  glm::translate(glm::identity<glm::mat4>(),glm::vec3(0,0,150)) * 
                                glm::rotate(glm::identity<glm::mat4>(), (float)glfwGetTime() * 2.0f,glm::vec3(1,1,1));

        cam.setModelMatrix(modelmtrix);
       
        //设置视口
        glViewport(0, 0, width, height);

        shader.bind(UNIFORM_MVP, cam.getMVP());
        pyramid.render(shader);

        cam.setModelMatrix(glm::translate(glm::identity<glm::mat4>(),glm::vec3(0, 0, 0)));

        shader.bind(UNIFORM_MVP, cam.getMVP());
        plane.render(shader);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    // glfwTerminate();
    return 0;
}