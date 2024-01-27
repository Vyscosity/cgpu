#pragma once

#include <vector>

#include "../Math/glm.h"

#include "BasicTexture.h"

class TextureAtlas : public BasicTexture
{
public:
    TextureAtlas(const char* textureFileName);

    std::vector<float> getTexture(const glm::vec2& coords);

private:
    int m_imageSize;
    int m_individualTextureSize;
};

