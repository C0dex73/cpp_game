#ifndef CDXG_TRIANGLE
#define CDXG_TRIANGLE

#include <glm/glm.hpp>
#include "displayable.h"

namespace cdxg {
    class Triangle : public Displayable {
        public:
        enum lengthType { Inner , Edge };
        Triangle(glm::vec3 center, float length, float rotation, lengthType lt);
        private:
        glm::vec3 *verticesConstructor(glm::vec3 center, float length, float rotation, lengthType lt);
    };
}

#endif