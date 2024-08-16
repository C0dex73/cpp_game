#ifndef CDXG_SHADER_CLASS
#define CDXG_SHADER_CLASS

#include <string>

namespace cdxg {
    class Shader {
        public:
        GLuint mShaderProgramId;
        Shader(std::string *vertexShader, std::string *fragmentShader);
        ~Shader();

    }; // class Shader
} // namespace cdxg

#endif // CDXG_SHADER_CLASS