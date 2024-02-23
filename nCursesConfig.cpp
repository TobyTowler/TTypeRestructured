#include "nCursesConfig.h"
#include <ncurses.h>
#include <iostream>

/*************************************
 * ncurses initialisation
 *************************************/
void nCursesCFG(){
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
//    printw("HELLO");
//    refresh();
}