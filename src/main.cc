#include "testGame.hh"
using namespace cdxg;

// TODO : replace fprinf to MSGBOX as there is no console for this application

/**
 * The main function, called when the executable lauches
 */
int main(){
    TestGame game = TestGame(800, 600, "testGame");
    game.Run();
    return 0;
}