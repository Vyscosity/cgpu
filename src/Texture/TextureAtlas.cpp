#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const char* textureFileName)
{
    loadFromFile(textureFileName);

    m_imageSize = 256 * 2;
    m_individualTextureSize = 16;
}

std::vector <float> TextureAtlas::getTexture(const glm::vec2& coords)
{
    static const float texturesPerRow = (float) m_imageSize / (float) m_individualTextureSize;
    static const float unitSize = 1.0f / texturesPerRow;
    static const float pixel = 1.0f / (float) m_imageSize;

    static float margin = 0.001f;

    float xMin = ( coords.x * unitSize) + margin * pixel;
    float yMin = ( coords.y * unitSize ) + margin * pixel;

    float xMax = ( xMin + unitSize ) - margin * pixel;
    float yMax = ( yMin + unitSize ) - margin * pixel;

    return
    {
        xMax, yMax,
        xMin, yMax,
        xMin, yMin,
        xMax, yMin
    };
}