#include <iostream>
#include "ncurses.h"
#include "TType.h"
#include "nCursesConfig.h"
#include "Printer.h"
#include "Calculate.h"

int main()
{
    nCursesCFG();

    printTitle();

    TType game;

    while(true){
        game.clearInput();  //reset input for each game

        printSettings(game);

        game.run();

        calculateScore(game);
    }




}
