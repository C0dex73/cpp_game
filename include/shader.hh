#ifndef CDXG_SHADER_CLASS
#define CDXG_SHADER_CLASS

#include <string>
#include "strRawShaders.hh"

namespace cdxg {
    class Shader {
        public:
        Shader(RawShaderDuo *pShaders);
        Shader(const char *const pstrVertexShader, const char *const pstrFragmentShader);
        ~Shader();
        void Use();
        void Load();
        private:
        const unsigned int muiShaderProgramId;
        const char *const mpcpVertexShader;
        const char *const mpcpFragmentShader;
    }; // class Shader
} // namespace cdxg

#endif // CDXG_SHADER_CLASS