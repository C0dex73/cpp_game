#ifndef CDXG_VERTICES
#define CDXG_VERTICES

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
} // namespace cdxg


#endif