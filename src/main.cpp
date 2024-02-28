#include "Printer.h"
#include "TType.h"
#include "nCursesConfig.h"

int main() {
    nCursesCFG();

    printTitle();

    TType game;

    while (true) {
        game.resetGame();

        printSettings(game);

        game.run();

    }
}
