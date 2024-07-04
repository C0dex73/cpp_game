#ifndef CDXG_DISPLAYABLE
#define CDXG_DISPLAYABLE

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

namespace cdxg {
    class Displayable {
        private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int VshaderID;
        unsigned int FshaderID;
        const unsigned int shaderProgramID;
        unsigned int type;
        inline void refreshVertices();
        protected:
        glm::vec2 *const vertices;
        unsigned int verticesCount;
        public:
        Displayable(glm::vec2 *_vertices, unsigned int _verticesCount, unsigned int _type);
        friend std::ostream& operator<<(std::ostream& os, cdxg::Displayable const d);
        void rotate(float angle, glm::vec2 *center = new glm::vec2(0.0f, 0.0f));
        void draw();
        glm::vec2 *getVertex(unsigned int n);
    };
}

#endif