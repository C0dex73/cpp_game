#include "testGame.hh"
using namespace cdxg;

/**
 * The main function, called when the executable lauches
 */
int main(){
    TestGame game = TestGame(800, 600, "testGame");
    game.Run();
    return 0;
}