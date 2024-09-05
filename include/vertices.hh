#ifndef CDXG_VERTICES
#define CDXG_VERTICES

#include <type_traits>
#include <stdexcept>

namespace cdxg
{
    struct Vertex {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct VertexRGB : public Vertex {
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
    };
    struct VertexRGBA : public VertexRGB {
        float a = 0.0f;
    };

    template<typename T> void initializeVertexAttribArrays(unsigned int vao){
        throw std::invalid_argument("Tried to enableVertexAttribArray of an unhandled class");
    }

} // namespace cdxg


#endif