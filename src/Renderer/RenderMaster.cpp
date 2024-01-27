#include "RenderMaster.h"

//#include <SFML/Graphics.hpp>

#include <iostream>

void RenderMaster::drawQuad(const glm::vec3& pos)
{
    m_quadRenderer.add(pos);
}

void RenderMaster::drawCube(const glm::vec3& pos)
{
    m_cubeRenderer.add(pos);
}

void RenderMaster::finishRender(BasicWindow& basicWindow, const Camera& camera)
{
    //glClearColor(0.1, 0.5, 1.0, 1.0);
    //glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    bgfx::setState(0
        | BGFX_STATE_WRITE_RGB
        | BGFX_STATE_WRITE_A
        | BGFX_STATE_WRITE_Z
        | BGFX_STATE_DEPTH_TEST_LESS
        | BGFX_STATE_MSAA
    );

    m_quadRenderer.renderQuads(camera);
    m_cubeRenderer.render(camera);

    basicWindow.display();
}