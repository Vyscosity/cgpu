#include "BasicTexture.h"

#include <bgfx/bgfx.h>

#include <bx/commandline.h>
#include <bx/endian.h>
#include <bx/math.h>
#include <bx/readerwriter.h>
#include <bx/string.h>

#include <fstream>

#include <bimg/decode.h>
#include <iostream>
#include <stb/stb_image.h>

//#include <SFML/Graphics.hpp>

BasicTexture::BasicTexture(const char* file)
{
    loadFromFile(file);
}

void BasicTexture::loadFromFile(const char* file)
{
    bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

    {
        std::cout << "Loading texture: " << file << "\n";
        int width, height;
        stbi_uc* data = stbi_load(file, &width, &height, 0, 4);
        const bgfx::Memory* mem = bgfx::copy(data, width * height * 4);
        if (nullptr != mem)
        {
            handle = bgfx::createTexture2D((uint16_t)width, (uint16_t)height, false, 1, bgfx::TextureFormat::RGBA8, BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT, mem);
        }
        else
        {
            std::cerr << "Could not load texture: " << file << "\n";
        }
        stbi_image_free(data);

    }
    m_color = handle;
    //return handle;
    //return handle;
}

BasicTexture::~BasicTexture()
{
    //glDeleteTextures(1, &m_id);
    //bgfx::destroy(m_color);
    //bgfx::destroy(s_texColor);
}

void BasicTexture::bindTexture()
{
    s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
    bgfx::setTexture(0, s_texColor, m_color);
    //glBindTexture(GL_TEXTURE_2D, m_id);
}
