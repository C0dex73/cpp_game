#ifndef CDXG_DISPLAYABLE
#define CDXG_DISPLAYABLE

//#warning displayable called

#include <vector>
#include "vertices.hh"
#include "shader.hh"
#include <glad/glad.h>
#include <stdexcept>
#include <iostream>

namespace cdxg
{
    class TestGame;
    template<class Vtype>
    inline void testVertexType() {if(!std::is_base_of<Vertex, Vtype>().value) { throw std::invalid_argument("Tried to initialize cdxg::Displayable<Vtype> class\nwith Vtype not a vertex or vertex derived Class.\n"); }}
    
    template<class Vtype = Vertex>
    class Displayable {
        public:
        enum mGlDrawTypeIndices {
            //IBO drawType is dynamic VBO drawType is dynamic
            DYNAMIC = 0,
            //IBO drawType is dynamic VBO drawType is dynamic
            DYNAMIC_DYNAMIC = 0,
            //IBO drawType is static VBO drawType is static
            STATIC = 1,
            //IBO drawType is static VBO drawType is static
            STATIC_STATIC = 1,
            //IBO drawType is static VBO drawType is dynamic
            DYNAMIC_STATIC = 2,
            //IBO drawType is dynamic VBO drawType is static
            STATIC_DYNAMIC = 3,
            //IBO drawType is stream VBO drawType is stream
            STREAM = 4
        };
        Displayable()
        {
            testVertexType<Vtype>();
            meDrawTypeIndex = Displayable<Vtype>::DYNAMIC;
            mppShader = Shader::defaultShader();
        };
        Displayable(Displayable<Vtype>::mGlDrawTypeIndices drawTypeIndex)
        {
            testVertexType<Vtype>();
            drawTypeIndex = meDrawTypeIndex;
            mppShader = Shader::defaultShader();
        };
        void draw()
        {
            (*mppShader)->Use();

            glBindVertexArray(muiVao);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glBindVertexArray(0);
        };

        void move(float x, float y){
            for(int i = 0; i < mvVertices.size(); ++i){
                mvVertices[i].move(x, y);
            }
            mbVerticesModified = true;
            refreshVram();
        }
        
        protected:
        friend class TestGame;

        void load()
        {
            glGenVertexArrays(1, &muiVao);
            glBindVertexArray(muiVao);
            glGenBuffers(1, &muiVbo);
            glBindBuffer(GL_ARRAY_BUFFER, muiVbo);
            glGenBuffers(1, &muiIbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, muiIbo);

            refreshVram(true, false, -1);

            initializeVertexAttribArrays<Vtype>();

            glBindVertexArray(0);
        };
        void setVertices(std::vector<Vtype> vertices, bool bRefreshVram = true)
        {
            if(mvVertices == vertices) { return; }
            mvVertices = vertices;
            mbVerticesModified = true;
            if(bRefreshVram) { refreshVram(); }
        };
        void setVerticesIndices(std::vector<unsigned int> verticesIndices, bool bRefreshVram = true)
        {
            if(muivVerticesIndices == verticesIndices) { return; }
            muivVerticesIndices = verticesIndices;
            mbVerticesIndicesModified = true;
            if(bRefreshVram) { refreshVram(); }
        };
        void setShader(Shader **shader)
        {
            mppShader = shader;
            (*mppShader)->Load();
        };
        void setShader(Shader *shader)
        {
            mpShader = shader;
            setShader(&mpShader);
        };
        void unload()
        {
            glDeleteVertexArrays(1, &muiVao);
        };
        void refreshVram(bool forceRefresh = false, bool bindBuffers = true, int vertexArrayObjectCallbackID = 0)
        {
            if(!forceRefresh && !mbVerticesIndicesModified && !mbVerticesModified) { return; }
            if(bindBuffers) { glBindVertexArray(muiVao); }
            if(forceRefresh || mbVerticesModified) {
                if(bindBuffers) { glBindBuffer(GL_ARRAY_BUFFER, muiVbo); }
                glBufferData(GL_ARRAY_BUFFER, mvVertices.size()*sizeof(mvVertices[0]), &mvVertices[0], std::get<0>(matGlDrawType[meDrawTypeIndex]));
            }
            if(forceRefresh || mbVerticesIndicesModified){
                if(bindBuffers) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, muiIbo); }
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, muivVerticesIndices.size()*sizeof(muivVerticesIndices[0]), &muivVerticesIndices[0], std::get<1>(matGlDrawType[meDrawTypeIndex]));
            }
            if(vertexArrayObjectCallbackID >= 0 && bindBuffers){
                glBindVertexArray(vertexArrayObjectCallbackID);
            }
        };
        private:
        std::vector<unsigned int> muivVerticesIndices = {0, 0, 0};
        mGlDrawTypeIndices meDrawTypeIndex;
        std::vector<Vtype> mvVertices = {Vtype()};
        static const std::tuple<GLenum, GLenum> matGlDrawType[];
        Shader **mppShader;
        Shader *mpShader;
        unsigned int muiVao;
        unsigned int muiVbo;
        unsigned int muiIbo;
        bool mbVerticesModified = false;
        bool mbVerticesIndicesModified = false;
    }; // class Displayable
    template<class Vtype>
    const std::tuple<GLenum, GLenum> Displayable<Vtype>::matGlDrawType[] = {
        std::tuple<GLenum, GLenum>(GL_DYNAMIC_DRAW, GL_DYNAMIC_DRAW), //DYNAMIC (DYNAMIC_DYNAMIC)
        std::tuple<GLenum, GLenum>(GL_STATIC_DRAW, GL_STATIC_DRAW), //STATIC (STATIC_STATIC)
        std::tuple<GLenum, GLenum>(GL_DYNAMIC_DRAW, GL_STATIC_DRAW), //DYNAMIC_STATIC
        std::tuple<GLenum, GLenum>(GL_STATIC_DRAW, GL_DYNAMIC_DRAW), //STATIC_DYNAMIC
        std::tuple<GLenum, GLenum>(GL_STREAM_DRAW, GL_STREAM_DRAW), //STREAM
    };
} // namespace cdxg

#endif // CDXG_DISPLAYABLE