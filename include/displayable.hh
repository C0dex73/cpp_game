#ifndef CDXG_DISPLAYABLE
#define CDXG_DISPLAYABLE

#include <vector>
#include "vertices.hh"
#include <glad/glad.h>

namespace cdxg
{
    class Displayable {
        protected:
        Displayable(GLenum drawType);
        void setVertices(std::vector<Vertex> vertices);
        void setVerticesIndices(std::vector<unsigned int> verticesIndices);
        std::vector<Vertex> mvVertices = {Vertex()};
        std::vector<unsigned int> muivVerticesIndices = {0, 0, 0};
        unsigned int muiVao;
        unsigned int muiVbo;
        unsigned int muiIbo;
        GLenum meDrawType;
        void refresh();
        void load();
        void unload();
    }; // class Displayable    
} // namespace cdxg

#endif // CDXG_DISPLAYABLE