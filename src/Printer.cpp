#include "include/Printer.h"
#include "include/Colours.h"
#include "include/TType.h"
#include "include/fileSelector.h"
#include <ncurses.h>

using namespace std;

bool play;

/*************************************
 * title bar
 *************************************/
void printTitle() {
    attron(COLOR_PAIR(NcursesColors::TITLEPAIR));

    clear();
    printw(""
           "  ______  ______                            \n"
           " /\\__  _\\/\\__  _\\                          \n"
           " \\/_/\\ \\/\\/_/\\ \\/ __  __  _____      __    \n"
           "    \\ \\ \\   \\ \\ \\/\\ \\/\\ \\/\\ '__`\\  /'__`\\  \n"
           "     \\ \\ \\   \\ \\ \\ \\ \\_\\ \\ \\ \\L\\ \\/\\  __/  \n"
           "      \\ \\_\\   \\ \\_\\/`____ \\ \\ ,__/\\ \\____\\ \n"
           "       \\/_/    \\/_/`/___/> \\ \\ \\/  \\/____/ \n"
           "                      /\\___/\\ \\_\\          \n"
           "                      \\/__/  \\/_/          \n\n"
           "              Press To Start\n\n");

    attroff(COLOR_PAIR(NcursesColors::TITLEPAIR));
}

void waitForKeyPress() {
    while (!play) {
        int ch = getch();
        if (ch == 10) {
            play = true;
        }
    }
}

/*************************************
 * Method for setting/resetting game parameters
 * prints menu options
 *************************************/
void printSettings(TType &obj) {

    attron(COLOR_PAIR(NcursesColors::SUBPAIR));
    printw(" 1. Play game \n");
    printw(" 2. Play time trial \n");
    printw(" 3. Change text file \n");
    printw(" 4. Change text to random words from a file\n");
    // printw(" 4. Title screen\n");
    printw(" Press 'CTRL + C' to quit \n");
    refresh();
    attroff(COLOR_PAIR(NcursesColors::SUBPAIR));

    int cha;

    cha = getch();

    if (toupper(cha) == '1') {
        obj.timeTrial = false;
    }

    if (cha == '2') {
        obj.timeTrial = true;
        obj.setRandomWords("1000words.txt");
    }

    // Changing file
    if (toupper(cha) == '3') {
        obj.setWords(fileSelector("./../text/"));
    }

    // Changing file random words
    if (toupper(cha) == '4') {
        obj.setRandomWords(fileSelector("./../text/"));
    }
}
