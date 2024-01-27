#pragma once

#include "Math/Matrix.h"

struct Entity
{
    glm::vec3 position;
    glm::vec3 rotation;

    Entity() : position(glm::vec3(0.0f, 0.0f, 0.0f)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)) {}

};

