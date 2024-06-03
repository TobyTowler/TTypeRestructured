#include "include/nCursesConfig.h"
#include "include/Colours.h"
#include <ncurses.h>

/*************************************
 * ncurses initialisation
 *************************************/
void nCursesCFG() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
    NcursesColors::initCustomColor();
    NcursesColors::initColorPairs();
}
