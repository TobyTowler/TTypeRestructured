#include "include/TType.h"
#include "chrono"
#include "include/Colours.h"
#include "ncurses.h"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Custom text
void TType::setWords(string fileName) {
    words.clear();
    string str;
    ifstream f;
    f.open("text/" + fileName);
    getline(f, str);
    words = str;
}

void TType::clearWords() { setWords("default.txt"); }

void TType::clearInput() { input.clear(); }

/*************************************
 * Method for writing to screen
 * checking and colouring characters
 *************************************/
void TType::checkChar() {

    int length = 0, height, width;

    getmaxyx(stdscr, height, width);

    clear();

    // blank space
    printw("\n\n     ");

    // Chars user has written - RED-GREEN/BLACK
    for (int i = 0; i < input.size(); i++) {
        length++; // width-10 is a rough value thast seems to look decent since most words arent
                  // over 10 characters long could make it dynamic based on distance
        // to next space in words
        if (length > width - 15 && words.at(i - 1) == ' ') {

            printw("          ");
            length = 0;
        }

        if (words.at(i) == input.at(i)) {
            attron(COLOR_PAIR(NcursesColors::GREEN_TEXTPAIR));
            printw("%c", words.at(i));
            attroff(COLOR_PAIR(NcursesColors::GREEN_TEXTPAIR));
        } else {
            attron(COLOR_PAIR(NcursesColors::RED_TEXTPAIR));
            printw("%c", words.at(i));
            attroff(COLOR_PAIR(NcursesColors::RED_TEXTPAIR));
        }
    }

    // Current char - WHITE/MAGENTA
    attron(COLOR_PAIR(NcursesColors::BACKGROUND_CURSORPAIR));
    printw("%c", words[input.size()]);
    attroff(COLOR_PAIR(NcursesColors::BACKGROUND_CURSORPAIR));

    // Chars not yet reached - WHITE/BLACK
    for (int o = input.size() + 1; o < words.length(); o++) {
        length++;
        if (length > width - 15 && words.at(o - 1) == ' ') {
            printw("          ");
            length = 0;
        }
        attron(COLOR_PAIR(NcursesColors::TEXTPAIR));
        printw("%c", words[o]);
        attroff(COLOR_PAIR(NcursesColors::TEXTPAIR));
    }

    refresh();
}

void TType::setLines() {
    map<int, string> lines;
    int lineSize = 50, counter = 0;
    for (int i = 0; i < words.length(); i++) {
        counter++;
    }
}

TType::TType() {
    // this->setWords("longtext.txt");
    this->setRandomWords("1000words.txt");
    this->input = {};
    this->ch = '\0';
    this->runTime = 0;
    this->numberOfCorrectWords = 0;
}

void TType::run() {

    bool started = false;
    int length = 0; // holds the line length

    chrono::steady_clock::time_point start;

    for (int i = 0; i < size(words); i++) {
        /* if (words[i] == '\n') { */
        /*     break; */ /* } */
        checkChar();
        ch = getch();

        if (!started) {
            start = std::chrono::steady_clock::now();
            started = true;
        }

        input.push_back(ch);
        // addToInput(ch);

        if (ch == KEY_BACKSPACE) {
            if (i > 0)
                i -= 2;
            else
                i--;
            input.pop_back();
            input.resize(i + 1);
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = (end - start);
    runTime = time.count();

    checkCharAndRealWPM();
    printScore();
}

int TType::getNumberOfSpaces() {
    int num = 0;
    for (char c : words) {
        if (c == ' ') {
            num++;
        }
    }
    return num;
}

int TType::getRawWPM() { return int((getNumberOfSpaces() + 1) * 60 / runTime); }

int TType::getAccuracy() {
    int right = 0;

    for (int i = 0; i < input.size(); i++) {
        if (words.at(i) == input.at(i)) {
            right++;
        }
    }

    return (double(right) / double(words.size()) * 100);
}

void TType::checkCharAndRealWPM() {

    int length = 0, height, width;

    getmaxyx(stdscr, height, width);

    clear();

    // Chars user has written - RED-GREEN/BLACK
    for (int i = 0; i < input.size(); i++) {
        length++;
        // width-10 is a rough value thast seems to look decent since most words
        // arent over 10 characters long could make it dynamic based on distance
        // to next space in words
        if (length > width - 10 && words.at(i - 1) == ' ') {
            printw("\n");
            length = 0;
        }

        if (words.at(i) == input.at(i)) {
            attron(COLOR_PAIR(NcursesColors::GREEN_TEXTPAIR));
            printw("%c", words.at(i));
            attroff(COLOR_PAIR(NcursesColors::GREEN_TEXTPAIR));
        } else {
            attron(COLOR_PAIR(NcursesColors::RED_TEXTPAIR));
            printw("%c", words.at(i));
            attroff(COLOR_PAIR(NcursesColors::RED_TEXTPAIR));
        }
    }

    bool CORRECT = true;
    for (int i = 0; i < input.size(); i++) {
        if (words.at(i) != input.at(i)) {
            CORRECT = false;
        }
        if (words.at(i) == ' ' || i == words.length() - 1) {
            if (CORRECT) {
                numberOfCorrectWords++;
            }
            CORRECT = true;
        }
    }
    refresh();
}

void TType::resetGame() {
    input.clear();
    numberOfCorrectWords = 0;
}

void TType::printScore() {
    printw("\n\n");
    attron(COLOR_PAIR(NcursesColors::SCORE_PAIR));
    printw("--GAME OVER--\nYou Scored:\n\n");
    printw("  Accuracy: %d%%", getAccuracy());
    printw("        WPM: %d", int((numberOfCorrectWords * 60) / runTime));
    printw("        Raw WPM: %d", int((getNumberOfSpaces() + 1) * 60 / runTime));
    attroff(COLOR_PAIR(NcursesColors::SCORE_PAIR));
    printw("\n\n\n\n");

    refresh();
}

void TType::setRandomWords(string fileName) {
    words.clear();
    // open files
    string str;
    ifstream f;
    f.open("text/" + fileName);
    getline(f, str);

    // convert string to array
    vector<string> wordsArray;
    stringstream ss(str);
    string tmp;
    while (std::getline(ss, tmp, ' ')) {
        wordsArray.push_back(tmp);
    }
    // printw("%zu", wordsArray.size());
    // getch();

    // select words
    srand(time(NULL));
    for (int i = 0; i < 5; i++) {
        int num = rand() % wordsArray.size();
        words.append(wordsArray[num] + " ");
        wordsArray.erase(wordsArray.begin() + num);
    }
    words.erase(words.begin() + words.length() - 1);
}
