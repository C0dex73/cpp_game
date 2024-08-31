#ifndef CDXG_DISPLAYABLE
#define CDXG_DISPLAYABLE

#include <vector>
#include "vertices.hh"
#include <glad/glad.h>
#include <stdio.h>
using namespace std;

namespace cdxg
{
    template <class T>
    class Displayable {
        public:
        static_assert(
            std::is_base_of<Vertex, T>::value,
            "Displayable must use a descendant of cdxg::Vertex as vertex type !"
        );
        Displayable(){
            printf("e");
        };
        protected:
        
        void setVertices(vector<T> vertices)
        {
        mvVertices = vertices;
        };
        void setVerticesIndices(vector<unsigned int> verticesIndices)
        {
        muivVerticesIndices = verticesIndices;
        }
        vector<T> mvVertices = {T()};
        vector<unsigned int> muivVerticesIndices = {0, 0, 0};
        unsigned int muiVao;
        unsigned int muiVbo;
        unsigned int muiIbo;
        void refresh()
        {

        };
        void load()
        {
            glCreateVertexArrays(1, &muiVao);
            glCreateBuffers(1, &muiVbo);
            glCreateBuffers(1, &muiIbo);

            glVertexArrayVertexBuffer(muiVao, 0, muiVbo, 0, sizeof(mvVertices.data()));
            glVertexArrayElementBuffer(muiVbo, muiIbo);

            glNamedBufferStorage(muiVbo, sizeof(mvVertices.data())*sizeof(mvVertices[0]), )
        };
        void unload()
        {
            glDeleteVertexArrays(1, &muiVao);
        };
    }; // class Displayable    
} // namespace cdxg

#endif // CDXG_DISPLAYABLE