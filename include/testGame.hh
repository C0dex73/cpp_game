#ifndef CDXG_TEST_GAME
#define CDXG_TEST_GAME

#include "gameTemplate.hh"

namespace cdxg {

    class TestGame : public GameTemplate {
        public:
        TestGame(int initialWidth, int initialHeight, std::string initialTitle);
        ~TestGame(){};
        
        void Initialize() override;
        void LoadComponents() override;
        void Update() override;
        void Render() override;
    }; // class TestGame

} // namespace cdxg

#endif