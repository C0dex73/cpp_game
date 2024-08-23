#include "shader.hh"
#include "strRawShaders.hh"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace cdxg {

    Shader::Shader(RawShaderDuo *pShaders):
    muiShaderProgramId(glCreateProgram())
    {
        mpstrVertexShader = pShaders->VertexShader();
        mpstrFragmentShader = pShaders->FragmentShader();
        ShaderInitializer();
    }

    Shader::Shader(const std::string *pstrVertexShader, const std::string *pstrFragmentShader):
    muiShaderProgramId(glCreateProgram())
    {
        mpstrVertexShader = pstrVertexShader;
        mpstrFragmentShader = pstrFragmentShader;
        ShaderInitializer();
    }

    Shader::~Shader()
    {
        glDeleteProgram(muiShaderProgramId);
    }

    void Shader::ShaderInitializer()
    {
        const char* vertexShader = mpstrVertexShader->c_str();
        unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
        glCompileShader(vertexShaderID);

        const char* fragmentShader = mpstrFragmentShader->c_str();
        unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);
        glCompileShader(fragmentShaderID);
        //TODO : handle shaders conpile error

        // TODO : link shaders to program
    }

} // namespace cdxg