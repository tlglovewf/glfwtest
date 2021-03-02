#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_
#include <geometry/basegeom.h>
#include <render/tlShader.h>
#include <render/tlTexture.h>
#include <memory>
namespace tl
{
    template <typename Shape>
    class Drawable
    {
    public:
        using IdxType = typename Shape::Type; 
        struct Buffer
        {
            
            GLuint vboIdx = ErrorValue;
            GLuint eboIdx = ErrorValue;
            GLuint dwType = GL_TRIANGLES;
            VertexVector vertices;
            std::vector<IdxType> indices;

            static constexpr GLuint ErrorValue = -1;
            inline bool check(GLuint v) { return (v != ErrorValue); }
        };
        
    public:
        Drawable(float in, const color_t &clr);
        Drawable(float width, float height, const std::shared_ptr<TextureUnit> &unit );
        ~Drawable();

        //! 获取gpu渲染对象
        const Buffer &get() const
        {
            return _value;
        }
        //! 获取渲染点数量
        inline size_t renderSize() const
        {
            return _value.indices.size();
        }

        //!绑定执行
        void active();
        //! 绘制
        void render(Shader &shader);

    protected:
        Buffer                       _value;
        std::shared_ptr<TextureUnit> _tex;
    };

} // namespace tl
#include "tlDrawable.inl"
#endif