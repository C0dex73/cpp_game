#include "vertices.hh"
#include <type_traits>
#include <glad/glad.h>

namespace cdxg
{
    template<> void initializeVertexAttribArrays<Vertex>(unsigned int vao){
        glEnableVertexArrayAttrib(vao, 0);
        glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, Vertex::x));
        glVertexArrayAttribBinding(vao, 0, 0);
    }

    template<> void initializeVertexAttribArrays<VertexRGB>(unsigned int vao){
        initializeVertexAttribArrays<Vertex>(vao);
        glEnableVertexArrayAttrib(vao, 1);
        glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(VertexRGB, r));
        glVertexArrayAttribBinding(vao, 1, 0);
    }

    template<> void initializeVertexAttribArrays<VertexRGBA>(unsigned int vao){
        initializeVertexAttribArrays<Vertex>(vao);
        glEnableVertexArrayAttrib(vao, 1);
        glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, offsetof(VertexRGBA, r));
        glVertexArrayAttribBinding(vao, 1, 0);
    }
} // namespace cdxg
