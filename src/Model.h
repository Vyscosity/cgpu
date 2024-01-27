#pragma once

//#include <GL/glew.h>
#include <vector>

//#include <bgfx/bgfx.h>

#include "Mesh.h"

#include "Util/NonCopyable.h"



//#include "Vertex.h"

class Model : public NonCopyable
{
    public:
        Model() = default;
        /*
        Model(const std::vector<GLfloat>& vertexPositions,
              const std::vector<GLfloat>& textureCoords,
              const std::vector<GLuint>&  indices);
        */
        
        Model(const Mesh& mesh);//const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices);

        ~Model();

        /*void addData(const std::vector<GLfloat>& vertexPositions,
                     const std::vector<GLfloat>& textureCoords,
                     const std::vector<GLuint>&  indices);*/
        void addData(const Mesh& mesh);//const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices);

        void deleteData();

        //void addVBO(int dimensions, const std::vector<GLfloat>& data);
        void addVBO(const std::vector<Vertex>& data);
        void bindVAO() const;

        //int getIndicesCount() const;

    private:
        //void addEBO(const std::vector<GLuint>& indices);
        void addEBO(const std::vector<uint16_t>& indices);

        bgfx::ProgramHandle m_Program;
        bgfx::VertexBufferHandle mVbh;
        bgfx::IndexBufferHandle mIbh;
        /*GLuint m_vao = 0;
        int m_vboCount = 0;
        int m_indicesCount = 0;
        std::vector<GLuint> m_buffers;*/
};

