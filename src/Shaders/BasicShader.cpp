#include "BasicShader.h"

BasicShader::BasicShader(const char* vertexFile, const char* fragmentFile)
:   Shader(vertexFile, fragmentFile)
{
    getUniforms();
}

void BasicShader::loadProjViewMatrix(const glm::mat4& pMatrix, const glm::mat4& vMatrix)
{
    bgfx::setViewTransform(0, &vMatrix[0][0], &pMatrix[0][0]);
    /*loadMatrix4(m_locationProjectionViewMatrix,
                pvMatrix);*/
}

void BasicShader::loadModelMatrix(glm::vec3 quad)
{
    glm::mat4 mtx = glm::identity<glm::mat4>();

    mtx = glm::translate(mtx, quad);

    bgfx::setTransform(&mtx[0][0]);
    //loadMatrix4(m_locationModelMatrix, matrix);
}

void BasicShader::getUniforms()
{
    //useProgram();
    //m_locationProjectionViewMatrix = glGetUniformLocation(m_id, "projViewMatrix");
    //m_locationModelMatrix          = glGetUniformLocation(m_id, "modelMatrix");
}
