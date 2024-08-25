#ifndef CDXG_TEST_GAME
#define CDXG_TEST_GAME

#include "gameTemplate.hh"
#include "shader.hh"

namespace cdxg {

    class TestGame : public GameTemplate {
        public:
        TestGame(int initialWidth, int initialHeight, std::string initialTitle);
        virtual ~TestGame();
        Shader *mpShader;
        void Initialize() override;
        void Update() override;
        void Render() override;
    }; // class TestGame

} // namespace cdxg

#endif