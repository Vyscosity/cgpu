#pragma once

#include <vector>
#include "Shader.h"

class BasicShader : public Shader
{
    public:
        BasicShader(const char* vertexFile   = "vs_cubes",
                    const char* fragmentFile = "fs_cubes");

        void loadProjViewMatrix   (const glm::mat4& pMatrix, const glm::mat4& vMatrix);
        void loadModelMatrix(glm::vec3 quad);

    private:
        virtual void getUniforms() override;

        //GLuint m_locationProjectionViewMatrix;
        //GLuint m_locationModelMatrix;
};

