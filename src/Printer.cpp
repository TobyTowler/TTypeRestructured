#include "Printer.h"
#include "Colours.h"
#include "TType.h"
#include <ncurses.h>

using namespace std;

/*************************************
 * title bar
 *************************************/
void printTitle() {
    // taken from https://www.asciiart.eu/text-to-ascii-art

    attron(COLOR_PAIR(NcursesColors::TITLEPAIR));

    printw(" /"
           "====================================================================="
           "====================\\\n"
           " ||  __        __   _                            _____       "
           "___________                   ||\n"
           " ||  \\ \\      / /__| | ___ ___  _ __ ___   ___  |_   _|__   |_   "
           "_|_   _|   _ _ __   ___   ||\n"
           " ||   \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\   | |/ _ \\   "
           " | |   | || | | | '_ \\ / _ \\  ||\n"
           " ||    \\ V  V /  __/ | (_| (_) | | | | | |  __/   | | (_) |   | |   "
           "| || |_| | |_) |  __/  ||\n"
           " ||     \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|   |_|\\___/    "
           "|_|   |_| \\__, | .__/ \\___|  ||\n"
           " ||                                                                  "
           "   |___/|_|           ||\n"
           " \\=================================================================="
           "=======================//\n\n"
           "                                      Press To Start\n");

    refresh();

    int ch = getch();

    clear();
    printw(" /"
           "====================================================================="
           "====================\\\n"
           " ||  __        __   _                            _____       "
           "___________                   ||\n"
           " ||  \\ \\      / /__| | ___ ___  _ __ ___   ___  |_   _|__   |_                      "
           "_|_   _|   _ _ __   ___   ||\n"
           " ||   \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\   | |/ _ \\   "
           " | |   | || | | | '_ \\ / _ \\  ||\n"
           " ||    \\ V  V /  __/ | (_| (_) | | | | | |  __/   | | (_) |   | |   "
           "| || |_| | |_) |  __/  ||\n"
           " ||     \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|   |_|\\___/    "
           "|_|   |_| \\__, | .__/ \\___|  ||\n"
           " ||                                                                   "
           "    "
           "   |___/|_|           ||\n"
           " \\=================================================================="
           "=======================//\n\n");

    refresh();
    attroff(COLOR_PAIR(NcursesColors::TITLEPAIR));
}

/*************************************
 * Method for setting/resetting game parameters
 * prints menu options
 *************************************/
void printSettings(TType &obj) {

    attron(COLOR_PAIR(NcursesColors::SUBPAIR));
    printw(" 1. press 'R' to run test \n");
    printw(" 2. press 'C' to change test text \n");
    printw(" 3. press 'CTRL + C' to quit \n");
    printw(" 4. press 'T' to go to title screen\n");
    refresh();
    attroff(COLOR_PAIR(NcursesColors::SUBPAIR));

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
            string str;
            bool search = false;
            while (!search) {
                clear();
                printw("Enter file name: ");
                printw("%s", str.c_str());
                /* printw("\n\n", str); */
                refresh();
                cha = getch();
                switch (cha) {
                case 10: // enter
                    search = true;
                    break;
                case KEY_BACKSPACE: // backspace
                    if (str.length() > 0)
                        /* str = str.substr(0, str.length() - 1); */
                        str.pop_back();
                    else
                        str = "";
                    break;
                default:
                    str += cha;
                    break;
                }
            }

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
