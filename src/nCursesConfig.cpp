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
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();

    // Get the screen size
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    // Set padding space around the content (2 spaces on each side)
    int pad_top = 2;                         // Padding from the top
    int pad_left = 2;                        // Padding from the left
    int content_height = rows - 2 * pad_top; // Available height for content
    int content_width = cols - 2 * pad_left; // Available width for content

    // Create a window with padding
    WINDOW *win = newwin(content_height, content_width, pad_top, pad_left);

    // Set the border around the window
    box(win, 0, 0);
    NcursesColors::initCustomColor();
    NcursesColors::initColorPairs();
}
