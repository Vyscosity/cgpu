#pragma once

#include "QuadRenderer.h"
#include "CubeRenderer.h"

#include "BasicWindow.h"

class Camera;

//class Window;

class RenderMaster
{
    public:
        void drawQuad(const glm::vec3& pos);
        void drawCube(const glm::vec3& pos);

        void finishRender(BasicWindow& basicWindow, const Camera& camera);

    private:
        QuadRenderer m_quadRenderer;
        CubeRenderer m_cubeRenderer;

};



