#ifndef CDXG_TEST_GAME
#define CDXG_TEST_GAME

#include "gameTemplate.hh"
#include "displayable.hh"

namespace cdxg {

    class TestGame : public GameTemplate {
        public:
        TestGame(int initialWidth, int initialHeight, std::string initialTitle);
        ~TestGame();
        void Initialize() override;
        void Update() override;
        void Render() override;
        private:
        Displayable<VertexRGB> rectangle;
    }; // class TestGame

} // namespace cdxg

#endif