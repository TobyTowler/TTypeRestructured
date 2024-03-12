#include "Printer.h"
#include "TType.h"
#include <ncurses.h>

using namespace std;

/*************************************
 * title bar
 *************************************/
void printTitle() {
    // taken from https://www.asciiart.eu/text-to-ascii-art
    // short COLOR = 255;
    // init_pair(255, 226, COLOR_BLACK);
    // attron(COLOR_PAIR(255));

    printw(" /"
           "=========================================================================================\\\n"
           " ||  __        __   _                            _____       ___________                   ||\n"
           " ||  \\ \\      / /__| | ___ ___  _ __ ___   ___  |_   _|__   |_   _|_   _|   _ _ __   ___   ||\n"
           " ||   \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\   | |/ _ \\    | |   | || | | | '_ \\ / _ \\  ||\n"
           " ||    \\ V  V /  __/ | (_| (_) | | | | | |  __/   | | (_) |   | |   | || |_| | |_) |  __/  ||\n"
           " ||     \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|   |_|\\___/    |_|   |_| \\__, | .__/ \\___|  ||\n"
           " ||                                                                     |___/|_|           ||\n"
           " \\=========================================================================================//\n\n"
           "                                      Press To Start\n");

    refresh();

    int ch = getch();

    clear();
    printw(" /"
           "=========================================================================================\\\n"
           " ||  __        __   _                            _____       ___________                   ||\n"
           " ||  \\ \\      / /__| | ___ ___  _ __ ___   ___  |_   _|__   |_   _|_   _|   _ _ __   ___   ||\n"
           " ||   \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\   | |/ _ \\    | |   | || | | | '_ \\ / _ \\  ||\n"
           " ||    \\ V  V /  __/ | (_| (_) | | | | | |  __/   | | (_) |   | |   | || |_| | |_) |  __/  ||\n"
           " ||     \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|   |_|\\___/    |_|   |_| \\__, | .__/ \\___|  ||\n"
           " ||                                                                     |___/|_|           ||\n"
           " \\=========================================================================================//\n\n");

    refresh();
}

/*************************************
 * Method for setting/resetting game parameters
 * prints menu options
 *************************************/
void printSettings(TType &obj) {

    // short ONE = 254, TWO = 253, THREE = 252, FOUR = 251;
    // init_pair(254, 226, COLOR_BLACK);
    // init_pair(253, 227, COLOR_BLACK);
    // init_pair(252, 228, COLOR_BLACK);
    // init_pair(251, 254, COLOR_BLACK);

    // attron(COLOR_PAIR(251));
    printw(" 1. press 'R' to run test \n");
    // attroff(COLOR_PAIR(254));
    // attron(COLOR_PAIR(253));
    printw(" 2. press 'C' to change test text \n");
    // attroff(COLOR_PAIR(253));
    // attron(COLOR_PAIR(252));
    printw(" 3. press 'CTRL + C' to quit \n");
    // attroff(COLOR_PAIR(252));
    // attron(COLOR_PAIR(251));
    printw(" 4. press 'T' to go to title screen\n");
    // attroff(COLOR_PAIR(251));
    refresh();

    int cha;
    bool play = false;

    while (!play) {

        cha = getch();

        if (toupper(cha) == 'R') {
            play = true;
        }

        // Changing file
        if (toupper(cha) == 'C') {
            play = true;
            printw("Enter file name: ");
            echo(); // to see what user is typing turned off again further down
            string str;
            while (true) {
                cha = getch();
                if (cha == 10)
                    break; // 10 = enter key
                else {
                    str += cha;
                    refresh();
                }
            }

            noecho();
            obj.setWords(str);
        }

        // Title screen
        else if (toupper(cha) == 'T') {
            clear();
            printTitle();
            printSettings(obj);
            obj.clearInput();
            obj.clearWords();
        }
    }
}
