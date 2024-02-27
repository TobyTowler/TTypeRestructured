#include "Calculate.h"
#include "Printer.h"
#include "TType.h"
#include "nCursesConfig.h"

int main() {
  nCursesCFG();

  printTitle();

  TType game;

  while (true) {
    game.clearInput(); // reset input for each game

    printSettings(game);

    game.run();

    calculateScore(game);
  }
}
