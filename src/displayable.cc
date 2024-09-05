#include "displayable.hh"
#include <glad/glad.h>
#include <vector>
#include "vertices.hh"

namespace cdxg
{
    Displayable::Displayable(GLenum drawType = GL_DYNAMIC_DRAW){
        meDrawType = drawType;
    }

    void Displayable::setVertices(std::vector<Vertex> vertices)
    {
        mvVertices = vertices;
    }

    void Displayable::setVerticesIndices(std::vector<unsigned int> verticesIndices)
    {
        muivVerticesIndices = verticesIndices;
    }

    void Displayable::refresh(){}

    void Displayable::load()
    {
            glCreateVertexArrays(1, &muiVao);
            glCreateBuffers(1, &muiVbo);
            glCreateBuffers(1, &muiIbo);

            glNamedBufferStorage(muiVbo, sizeof(mvVertices.data())*sizeof(mvVertices[0]), mvVertices.data(), meDrawType);
            glNamedBufferStorage(muiIbo, sizeof(muivVerticesIndices.data())*sizeof(muivVerticesIndices[0]), &muivVerticesIndices[0], meDrawType);

            glVertexArrayVertexBuffer(muiVao, 0, muiVbo, 0, sizeof(mvVertices.data()));
            glVertexArrayElementBuffer(muiVbo, muiIbo);

            initializeVertexAttribArrays<decltype(mvVertices)::value_type>(muiVao);
    }

    void Displayable::unload()
    {
            glDeleteVertexArrays(1, &muiVao);
    }
} // namespace cdxg
