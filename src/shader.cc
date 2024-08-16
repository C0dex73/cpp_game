#include "shader.hh"
#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace cdxg {

    Shader::Shader(std::string *vertexShader, std::string *fragmentShader):
    mShaderProgramId(glCreateProgram())
    {
        //TODO : create shaders and link them
    }

    Shader::~Shader()
    {
        glDeleteProgram(mShaderProgramId);
    }

} // namespace cdxg