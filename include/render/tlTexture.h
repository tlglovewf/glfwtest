#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "disablecopyable.h"
#include <string>
namespace tl
{
    //图片接口
    class Image : public disablecopyable
    {
    public:
        Image() = default;
        ~Image();
        //! 加载图片
        bool load(const std::string &path);

        //! 设置数据
        void setData(uint8_t *data, int width, int height, int format)
        {
            mData   = data;
            mWidth  = width;
            mHeight = height;
            mFormat = format;
        }
        //! 保存图片 默认png
        void save(const std::string &path);

        //! 获取指针
        const uint8_t *pointer()const
        {
            return mData;
        }
        //! 获取宽度
        int width()const
        {
            return mWidth;
        }
        //! 获取长度
        int height()const
        {
            return mHeight;
        }
        //! 获取图片类型
        int format()const
        {
            return mFormat;
        }
    protected:
        uint8_t *mData = nullptr;
        int mWidth     = 0;
        int mHeight    = 0;
        int mFormat    = 0;
    };

    //! 纹理单元
    struct TextureUnit
    {
        uint8_t texId = -1;
        Image   image;
        inline bool isValid()const
        {
            return texId >= 0;
        }
        //!生成纹理单元
        bool generate(const std::string &path);
        TextureUnit() = default;
        ~TextureUnit();
    };
    
} // namespace tl



#endif