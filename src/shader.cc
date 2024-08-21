#include "shader.hh"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace cdxg {

    Shader::Shader(std::string *pstrVertexShader, std::string *pstrFragmentShader):
    mShaderProgramId(glCreateProgram())
    {
        // TODO : separate that into specific shader classes and precompiled into files
        const char* vertexShader = pstrVertexShader->c_str();
        unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
        glCompileShader(vertexShaderID);

        const char* fragmentShader = pstrFragmentShader->c_str();
        unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);
        glCompileShader(fragmentShaderID);
        //TODO : handle shaders conpile error

        // TODO : link shaders to program
    }

    Shader::~Shader()
    {
        glDeleteProgram(mShaderProgramId);
    }

} // namespace cdxg