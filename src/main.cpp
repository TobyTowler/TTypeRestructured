#include "include/Printer.h"
#include "include/TType.h"
#include "include/nCursesConfig.h"

int main() {
    nCursesCFG();

    // callTitle();
    printTitle();

    TType game;

    while (true) {
        game.resetGame();

        printSettings(game);

        game.run();
    }
}
