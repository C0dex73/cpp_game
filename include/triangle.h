#ifndef CDXG_TRIANGLE
#define CDXG_TRIANGLE

#include <glm/glm.hpp>
#include "displayable.h"

namespace cdxg {
    class Triangle : public Displayable {
        public:
        enum lengthType { Inner , Edge };
        Triangle(glm::vec2 center, float length, float rotation, lengthType lt);
        private:
        glm::vec2 *verticesConstructor(glm::vec2 center, float length, float rotation, lengthType lt);
    };
}

#endif