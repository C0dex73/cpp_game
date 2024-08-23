#ifndef CDXG_STR_RAW_SHADERS
#define CDXG_STR_RAW_SHADERS

#include <string>

namespace cdxg {
    class RawShaders {
        public:
        RawShaders() = delete;
        static RawShaderDuo source;
    }; // class RawShaders

    class RawShaderDuo {
        private:
        const std::string msstrVertexShader;
        const std::string msstrFragmentShader;
        public:
        RawShaderDuo(const char const*vertexShader, const char const*fragmentShader);
        const std::string *VertexShader();
        const std::string *FragmentShader();
    }; // class RawShadersDuo
} // namespace cdxg

#endif // CDXG_STR_RAW_SHADERS