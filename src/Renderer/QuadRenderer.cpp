#include "QuadRenderer.h"

#include <iostream>

#include "../Camera.h"
#include "../Math/Matrix.h"


/*
std::vector<Vertex> vertexes;

std::vector<Vertex> vert = {
    {1.0f, 0.0f, 0.0f,   0x7fff, 0x7fff},   //top right
    {0.0f, 0.0f, 0.0f,  0, 0x7fff},        //top left
    {0.0f, 1.0f, 0.0f, 0, 0},             //bottom left
    {1.0f, 1.0f, 0.0f,  0x7fff, 0}         //bottom right
};
*/

std::vector<float> vertices = {
    1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
};

std::vector<float> uv = {
    1, 1,
    0, 1,
    0, 0,
    1, 0,
};

std::vector<uint16_t> indices = {
    0, 1, 2,
    2, 3, 0
};

QuadRenderer::QuadRenderer()
{
    Vertex::init();


    //m_basicTexture = BasicTexture("res/textures/grass.png"); //prob not

    m_basicTexture.loadFromFile("res/textures/grass.png");

    /*m_quadModel.addData(
    {
        -0.5,  0.5, 0,
         0.5,  0.5, 0,
         0.5, -0.5, 0,
        -0.5, -0.5, 0,
    },
    {
        0, 1,
        1, 1,
        1, 0,
        0, 0,
    },
    {
        0, 1, 2,
        2, 3, 0
    });*/
    /*m_quadModel.addData(
        { vertices, uv, indices }
    );*/
}

void QuadRenderer::add(const glm::vec3& position)
{
    m_quads.push_back(position);
}

void QuadRenderer::renderQuads(const Camera& camera)
{

    for (auto& quad : m_quads)
    {
        m_shader.loadModelMatrix(quad);
        m_quadModel.bindVAO();

    }
    m_basicTexture.bindTexture();

    /*bgfx::setState(0
        | BGFX_STATE_WRITE_RGB
        | BGFX_STATE_WRITE_A
        | BGFX_STATE_WRITE_Z
        | BGFX_STATE_DEPTH_TEST_LESS
        | BGFX_STATE_MSAA
    );*/

    m_shader.loadProjViewMatrix(camera.getProjMatrix(), camera.getViewMatrix());
    m_shader.useProgram();

    m_quads.clear();
}

