#include "Camera.h"

#include "Math/Matrix.h"

Camera::Camera()
{
    m_projectionMatrix = makeProjectionMatrix(90.0f);

    position = glm::vec3(0.0f, 0.0f, -3.5f);
}

void Camera::update()
{
    position = m_pEntity->position;
    rotation = m_pEntity->rotation;

    m_viewMatrix = makeViewMatrix(*this);
    m_projViewMatrx = m_projectionMatrix * m_viewMatrix;
}

void Camera::hookEntity(const Entity& entity)
{
    m_pEntity = &entity;
}

const glm::mat4& Camera::getViewMatrix() const noexcept
{
    return m_viewMatrix;
}

const glm::mat4& Camera::getProjMatrix() const noexcept
{
    return m_projectionMatrix;
}

const glm::mat4& Camera::getProjectionViewMatrix() const noexcept
{
    return m_projViewMatrx;
}

