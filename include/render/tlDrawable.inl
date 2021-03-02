#include <render/tlDrawable.h>
#include <glad/glad.h>
namespace tl
{
    template <typename Shape>
    Drawable<Shape>::Drawable(float in, const tl::color_t &clr)
    {
        Shape shape(in);
        shape.setglobeColor(clr);

        shape.build(_value.vertices, _value.indices);
    }

    template <typename Shape>
    Drawable<Shape>::Drawable(float width, float height,  const std::shared_ptr<TextureUnit> &unit):_tex(unit)
    {
        Shape shape(width, height);

        shape.build(_value.vertices, _value.indices);
    }

    template <typename Shape>
    Drawable<Shape>::~Drawable()
    {
        if (_value.check(_value.vboIdx))
        {
            glDeleteBuffers(1, &_value.vboIdx);
        }

        if (_value.check(_value.eboIdx))
        {
            glDeleteBuffers(1, &_value.eboIdx);
        }
    }

    //!绑定执行
    template <typename Shape>
    void Drawable<Shape>::active()
    {
        if (!_value.isvalid())
        {//不存在 创建后绑定数据
            glGenBuffers(1, &_value.vboIdx);
            glBindBuffer(GL_ARRAY_BUFFER, _value.vboIdx);
            glBufferData(GL_ARRAY_BUFFER, sizeof(tl::vertex) * _value.vertices.size(), &_value.vertices[0], GL_STATIC_DRAW);

            glGenBuffers(1, &_value.eboIdx);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _value.eboIdx);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint8_t) * _value.indices.size(), &_value.indices[0], GL_STATIC_DRAW);
        }
        else
        {//存在缓存单元 直接绑定
            glBindBuffer(GL_ARRAY_BUFFER, _value.vboIdx);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _value.eboIdx);
        }
    }
    //! 绘制
    template <typename Shape>
    void Drawable<Shape>::render(tl::Shader &shader)
    {
        shader.activate();

        active();
        int offset = 0;
        glEnableVertexAttribArray(shader.vertexLoc());
        glVertexAttribPointer(shader.vertexLoc(), 3, GL_FLOAT, GL_FALSE, sizeof(tl::vertex), reinterpret_cast<void *>(offset));
        offset += sizeof(tl::vertex::pos);

        if(shader.colorLoc() > 0)
        {
            glEnableVertexAttribArray(shader.colorLoc());
            glVertexAttribPointer(shader.colorLoc(), 3, GL_FLOAT, GL_FALSE, sizeof(tl::vertex), reinterpret_cast<void *>(offset));
        }
        offset += sizeof(tl::vertex::clr);

        if(shader.normalLoc() > 0)
        {
            glEnableVertexAttribArray(shader.normalLoc());
            glVertexAttribPointer(shader.normalLoc(), 3, GL_FLOAT, GL_FALSE, sizeof(tl::vertex), reinterpret_cast<void *>(offset));
        }
        offset += sizeof(tl::vertex::nor);

        if(_tex && _tex->isValid() && shader.textureLoc())
        {
            glEnableVertexAttribArray(shader.textureLoc());
            glVertexAttribPointer(shader.textureLoc(), 2, GL_FLOAT, GL_FALSE, sizeof(tl::vertex), reinterpret_cast<void*>(offset));

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _tex->texId);
            shader.bind(UNIFORM_TEXCOORD0, 0);
        }

        if (std::is_same<IdxType, uint8_t>::value) 
        {
            glDrawElements(Shape(0).renderType(), renderSize(), GL_UNSIGNED_BYTE, NULL);
        }
        else if (std::is_same<IdxType, uint16_t>::value)
        {
            glDrawElements(Shape(0).renderType(), renderSize(), GL_UNSIGNED_SHORT, NULL);
        }
        else
        {
            glDrawElements(Shape(0).renderType(), renderSize(), GL_UNSIGNED_INT, NULL);
        }

        glDisableVertexAttribArray(shader.vertexLoc());
        if(shader.colorLoc() > 0)
        {
            glDisableVertexAttribArray(shader.colorLoc());
        }

        if(shader.normalLoc() > 0)
        {
            glDisableVertexAttribArray(shader.normalLoc());
        }

        if(shader.textureLoc() > 0)
        {
            glDisableVertexAttribArray(shader.textureLoc());
        }

    }
} // namespace tl