#include "Model.h"
#include <iostream>

bgfx::VertexLayout Vertex::ms_layout;

Model::Model(const Mesh& mesh)//const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
{
    addData(mesh);// vertices, indices);
}

Model::~Model()
{
    //deleteData();
}

void Model::bindVAO() const
{
    bgfx::setVertexBuffer(0, mVbh);
    bgfx::setIndexBuffer(mIbh);
//    glBindVertexArray(m_vao);
}

std::vector<Vertex> verts;
std::vector<uint16_t> ind;
void Model::addData(const Mesh& mesh)//const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
{
    const int numVertices = mesh.vertices.size() / 3;

    for (int i = 0; i < numVertices; ++i)
    {
        Vertex vertex;
        vertex.x = mesh.vertices[i * 3];
        vertex.y = mesh.vertices[i * 3 + 1];
        vertex.z = mesh.vertices[i * 3 + 2];
        vertex.u = mesh.uv[i * 2] * 0x7fff;
        vertex.v = mesh.uv[i * 2 + 1] * 0x7fff;
        verts.push_back(vertex);
    }

    for (const auto& vertex : verts)
    {
        std::cout << vertex.x << " " << vertex.y << " " << vertex.z << " " << vertex.u << " " << vertex.v << " \n";
    }

    ind = mesh.indices;

    addVBO(verts);
    addEBO(ind);
}

void Model::addVBO(const std::vector<Vertex>& vertices) {
    mVbh = bgfx::createVertexBuffer(bgfx::makeRef(vertices.data(),
        vertices.size() * sizeof(Vertex)),
        Vertex::ms_layout);
}
void Model::addEBO(const std::vector<uint16_t>& indices)
{
    mIbh = bgfx::createIndexBuffer(bgfx::makeRef(indices.data(), indices.size() * sizeof(uint16_t)));
}
/*
void Model::addVBO(int dimensions, const std::vector<GLfloat>& data)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 data.size() * sizeof(GLfloat),
                 data.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(m_vboCount,
                          dimensions,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          (GLvoid*) 0);

    glEnableVertexAttribArray(m_vboCount++);

    m_buffers.push_back(vbo);
}

void Model::addEBO(const std::vector<GLuint>& indices)
{
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(GLuint),
                 indices.data(),
                 GL_STATIC_DRAW);
}
*/

void Model::deleteData()
{
    /*
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(m_buffers.size(),
                    m_buffers.data());

    m_buffers.clear();

    m_vboCount      = 0;
    m_vao           = 0;
    m_indicesCount  = 0;
    */
    //bgfx::destroy(mVbh);
    //bgfx::destroy(mIbh);

}

//int Model::getIndicesCount() const
//{
//    return m_indicesCount;
//}

