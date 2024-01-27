#pragma once

#include <bgfx/bgfx.h>
//#include <GL/glew.h>
#include <string>

#include "../Util/NonCopyable.h"

class BasicTexture
{
    public:
        BasicTexture() = default;
        BasicTexture(const char* file);

        ~BasicTexture();

        void loadFromFile (const char* file);

        void bindTexture();

        bgfx::TextureHandle getHandle() { return m_color; }

    private:
        //GLuint m_id;

        bgfx::TextureHandle m_color;
        bgfx::UniformHandle s_texColor;
};

