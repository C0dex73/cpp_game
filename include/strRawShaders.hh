#ifndef CDXG_STR_RAW_SHADERS
#define CDXG_STR_RAW_SHADERS

#include <string>

#pragma region SHADER_POINTERS
// Get shaders from linked and compiled .glsl files
// To get all the symbols names,
// run make bin/rawShaders.o then run objdump -x bin/rawShaders.o
#pragma region SOURCE
extern char _binary___assets_source_vs_glsl_start[];
extern char _binary___assets_source_vs_glsl_end[];

extern char _binary___assets_source_fs_glsl_start[];
extern char _binary___assets_source_fs_glsl_end[];
#pragma endregion
#pragma region RGB
extern char _binary___assets_rgb_vs_glsl_start[];
extern char _binary___assets_rgb_vs_glsl_end[];

extern char _binary___assets_rgb_fs_glsl_start[];
extern char _binary___assets_rgb_fs_glsl_end[];
#pragma endregion
#pragma region RGBA
extern char _binary___assets_rgba_vs_glsl_start[];
extern char _binary___assets_rgba_vs_glsl_end[];

extern char _binary___assets_rgba_fs_glsl_start[];
extern char _binary___assets_rgba_fs_glsl_end[];
#pragma endregion
#pragma endregion

namespace cdxg {
    class RawShaderDuo {
        private:
        char *const mpcVertexShader;
        char *const mpcFragmentShader;
        public:
        RawShaderDuo(char *pcVs[2], char *pcFs[2]);
        char *pVertexShader();
        char *pFragmentShader();
    }; // class RawShadersDuo
    
    class RawShaders {
        public:
        RawShaders() = delete;
        static RawShaderDuo source;
        static RawShaderDuo rgb;
        static RawShaderDuo rgba;
    }; // class RawShaders
} // namespace cdxg

#endif // CDXG_STR_RAW_SHADERS