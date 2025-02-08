#include "include/Printer.h"
#include "include/Colours.h"
#include "include/TType.h"
#include "include/fileSelector.h"
#include <chrono>
#include <ncurses.h>
#include <thread>

using namespace std;

bool play;

/*************************************
 * title bar
 *************************************/
void printTitle() {
    // taken from https://www.asciiart.eu/text-to-ascii-art

    while (!play) {

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

        refresh();

        this_thread::sleep_for(std::chrono::milliseconds(600));

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
               "                      \\/__/  \\/_/          \n\n\n");

        refresh();
        this_thread::sleep_for(std::chrono::milliseconds(400));
        attroff(COLOR_PAIR(NcursesColors::TITLEPAIR));
    }
}

void waitForKeyPress() {
    while (!play) {
        int ch = getch();
        if (ch == 10) {
            play = true;
        }
    }
}

void callTitle() {
    play = false;
    while (!play) {
        thread printer(printTitle);
        thread presser(waitForKeyPress);
        printer.join();
        presser.join();
    }
}

/*************************************
 * Method for setting/resetting game parameters
 * prints menu options
 *************************************/
void printSettings(TType &obj) {

    attron(COLOR_PAIR(NcursesColors::SUBPAIR));
    printw(" 1. press 'R' to run test \n");
    printw(" 2. press 'C' to change test text to read from a file\n");
    printw(" 3. press 'V' to change test text to random words from a file\n");
    printw(" 4. press 'CTRL + C' to quit \n");
    printw(" 5. press 'T' to go to title screen\n");
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
            obj.setWords(fileSelector("./../text/"));
            // string str;
            // bool search = false;
            // while (!search) {
            //     clear();
            //     printw("Enter file name: ");
            //     printw("%s", str.c_str());
            //     /* printw("\n\n", str); */
            //     refresh();
            //     cha = getch();
            //     switch (cha) {
            //     case 10: // enter
            //         search = true;
            //         break;
            //     case KEY_BACKSPACE: // backspace
            //         if (str.length() > 0)
            //             /* str = str.substr(0, str.length() - 1); */
            //             str.pop_back();
            //         else
            //             str = "";
            //         break;
            //     default:
            //         str += cha;
            //         break;
            //     }
            // }
            //
            // obj.setWords(str);
            // getch();
        }

        // Changing file random words
        if (toupper(cha) == 'V') {
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

            obj.setRandomWords(str);
        }

        // Title screen
        else if (toupper(cha) == 'T') {
            clear();
            callTitle();
            printSettings(obj);
            obj.clearInput();
            obj.clearWords();
        }
    }
}
