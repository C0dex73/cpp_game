#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <stdio.h>
#include "displayable.h"
#include "triangle.h"

cdxg::Triangle::Triangle(glm::vec2 _center, float length, float rotation, lengthType lt)
    : Displayable(verticesConstructor(_center, length, rotation, lt), 3, GL_DYNAMIC_DRAW){
    center = _center;
}

glm::vec2 *cdxg::Triangle::getCenter(){
    return &center;
}

glm::vec2 *cdxg::Triangle::verticesConstructor(glm::vec2 center, float length, float rotation, lengthType lt){
    static glm::vec2 _vertices[3];
    glm::vec2 point = glm::vec2(0.0f, 0.0f);
    if(lt == lengthType::Edge){
        point.y += length / sqrt(1.5f);
    }else if(lt == lengthType::Inner){
        point.y += length;
    }else{
        fprintf(stderr, "No implementation for length type %s in triangle !", lt);
        //TODO :  add a way to exit safely or cancel class creation
    }

    for(unsigned int i = 0; i < 3; i++){
        _vertices[i] = center + glm::rotate(point, glm::radians(i*120.0f));
    }

    return _vertices;
}
