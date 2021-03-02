#include "render/tlTexture.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"
namespace tl
{

#define CHECK_PATH(P) P.empty()

    Image::~Image()
    {
        if(mData)
        {
            stbi_image_free(mData);
            mData = nullptr;
        }
        
    }
    //! 保存图片
    void Image::save(const std::string &path)
    {
        if(!path.empty())
        {
            stbi_write_png(path.c_str(),mWidth,mHeight,mFormat, mData, mFormat * mWidth);
        }
    }

    //! 加载图片
    bool Image::load(const std::string &path)
    {
        if(CHECK_PATH(path))
        {
            return false;
        }
        else
        {   
            stbi_uc *uc = stbi_load(path.c_str(), &mWidth, &mHeight, &mFormat, 0);
            if(NULL != uc)
            {
                mData =  uc;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    TextureUnit::~TextureUnit()
    {
        if(texId > -1)
        {
            GLuint id = (GLuint)texId;
            glDeleteTextures(1, &id);
        }
    }
    //!生成纹理单元
    bool TextureUnit::generate(const std::string &path)
    {
        if(image.load(path))
        {
            GLuint id;
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            texId = id;

            GLuint pictype = 0;
            
            switch(image.format())
            {
                case 1:
                    pictype = GL_RED;
                    break;
                case 3:
                    pictype = GL_RGB;
                    break;
                case 4:
                    pictype = GL_RGBA; 
                    break;
                default:
                    break;
            }

            glTexImage2D(GL_TEXTURE_2D, 0, pictype, image.width(), image.height(), 0, pictype, GL_UNSIGNED_BYTE, image.pointer() );
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, pictype == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);  
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, pictype == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0); 
        }
        else
        {
            return false;
        }
        return true;
    }
}