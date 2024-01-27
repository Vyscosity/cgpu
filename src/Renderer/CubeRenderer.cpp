#include "CubeRenderer.h"

#include <iostream>

#include "../Camera.h"
#include "../Math/Matrix.h"

CubeRenderer::CubeRenderer()
    : m_atlasTest("res/textures/Texture_Atlas.png")
{
    Vertex::init();

    //m_basicTexture.loadFromFile("test");

    std::vector<float> vertices = {
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    auto top = m_atlasTest.getTexture({ 0, 0 });
    auto side = m_atlasTest.getTexture({ 1, 0 });
    auto bottom = m_atlasTest.getTexture({ 2, 0 });

    std::vector<float> texCoords;
    texCoords.insert(texCoords.end(), side.begin(), side.end());
    texCoords.insert(texCoords.end(), side.begin(), side.end());
    texCoords.insert(texCoords.end(), side.begin(), side.end());
    texCoords.insert(texCoords.end(), side.begin(), side.end());
    texCoords.insert(texCoords.end(), top.begin(), top.end());
    texCoords.insert(texCoords.end(), bottom.begin(), bottom.end());

    std::vector<uint16_t> indices = {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        8, 9, 10,
        10, 11, 8,
        12, 13, 14,
        14, 15, 12,
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20,
    };

    m_cubeModel.addData({ vertices, texCoords, indices });
}

void CubeRenderer::add(const glm::vec3& position)
{
    m_quads.push_back(position);
}

void CubeRenderer::render(const Camera& camera)
{
    //    glEnable(GL_CULL_FACE);
    for (auto& quad : m_quads)
    {
        m_shader.loadModelMatrix(quad);
        m_cubeModel.bindVAO();
        //m_shader.loadModelMatrix(makeModelMatrix({ quad, {0, 0, 0} }));

        //glDrawElements(GL_TRIANGLES, m_cubeModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
    m_atlasTest.bindTexture();

    m_shader.loadProjViewMatrix(camera.getProjMatrix(), camera.getViewMatrix());
    m_shader.useProgram();

    m_quads.clear();
}

