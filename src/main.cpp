#include "include/Printer.h"
#include "include/TType.h"
#include "include/nCursesConfig.h"

int main() {
    nCursesCFG();

    printTitle();

    TType game;

    while (true) {
        game.resetGame();

        printSettings(game);

        if (game.timeTrial) {
            game.runTimeTrial();
        } else {
            game.run();
        }
    }
}
