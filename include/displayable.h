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
        protected:
        glm::vec3 *const vertices;
        unsigned int verticesCount;
        public:
        Displayable(glm::vec3 *_vertices, unsigned int _verticesCount);
        friend std::ostream& operator<<(std::ostream& os, cdxg::Displayable const d);
        //void Rotate(float angle);
        void draw();
    };
}

#endif