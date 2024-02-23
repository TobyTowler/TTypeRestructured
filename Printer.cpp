#include "Printer.h"
#include "TType.h"
#include <ncurses.h>
#include <iostream>

using namespace std;

/*************************************
 * title bar
 *************************************/
void printTitle(){
    //taken from https://www.asciiart.eu/text-to-ascii-art
    printw("   /=========================================================================================\\\n"
           "   ||  __        __   _                            _____       _____ _____                   ||\n"
           "   ||  \\ \\      / /__| | ___ ___  _ __ ___   ___  |_   _|__   |_   _|_   _|   _ _ __   ___   ||\n"
           "   ||   \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\   | |/ _ \\    | |   | || | | | '_ \\ / _ \\  ||\n"
           "   ||    \\ V  V /  __/ | (_| (_) | | | | | |  __/   | | (_) |   | |   | || |_| | |_) |  __/  ||\n"
           "   ||     \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|   |_|\\___/    |_|   |_| \\__, | .__/ \\___|  ||\n"
           "   ||                                                                     |___/|_|           ||\n"
           "   \\=========================================================================================//\n");

    refresh();
}


/*************************************
 * Method for setting/resetting game parameters
 * prints menu options
 *************************************/
void printSettings(TType &obj){

    printw("1. press 'Any key' to run test \n");
    printw("2. press 'C' to change test text \n");
    printw("3. press 'CTRL + C' to quit \n");
    printw("4. press 'T' to go to title screen\n");
    refresh();

    int cha = getch();

    if(toupper(cha) == 'C'){
        printw("Enter file name: ");
        echo();
        string str;
        while (true){
            cha = getch();
            if(cha == 10) break; //10 = enter key
            else {
                str += cha;
                refresh();
            }
        }
        noecho();
        obj.setWords(str);
    }
    else if(toupper(cha) == 'T'){
        clear();
        printTitle();
        printSettings(obj);
        obj.clearInput();
        obj.clearWords();
    }
}