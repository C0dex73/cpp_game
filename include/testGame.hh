#ifndef CDXG_TEST_GAME
#define CDXG_TEST_GAME

#include "gameTemplate.hh"
#include "displayable.hh"
#include <vector>

namespace cdxg {

    class TestGame : public GameTemplate {
        public:
        TestGame(int initialWidth, int initialHeight, std::string initialTitle);
        ~TestGame();
        void Initialize() override;
        void Update() override;
        void Render() override;
        private:
        std::vector<Displayable<VertexRGB>> rectangles;
        int state = -1;
        void addRectangle();
        void processInput();
        std::vector<VertexRGB> vertices;
        std::vector<unsigned int> indices;
        int oldAddButtonState = 0;
        int oldSubButtonState = 0;
        int oldSpaceButtonState = 0;
    }; // class TestGame

} // namespace cdxg

#endif