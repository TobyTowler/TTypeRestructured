#include "nCursesConfig.h"
#include <ncurses.h>

/*************************************
 * ncurses initialisation
 *************************************/
void nCursesCFG(){
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
}
