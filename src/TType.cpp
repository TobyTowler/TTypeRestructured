#include "include/TType.h"
#include "chrono"
#include "include/Colours.h"
#include "ncurses.h"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <future>
#include <map>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

// Custom text
using std::chrono::steady_clock;

void TType::setWords(string fileName) {
    this->randomWorded = false;
    if (fileName == "") {
        fileName = "default.txt";
    }
    this->inputFile = "fileName";
    words.clear();
    string str;
    ifstream f;
    f.open("./../text/" + this->inputFile);
    getline(f, str);
    words = str;
}

void TType::clearInput() { input.clear(); }

/*
 * Method for writing to screen
 * checking and colouring characters
 */
void TType::checkChar() {

    int length = 0, height, width;

    getmaxyx(stdscr, height, width);

    clear();

    // blank space
    printw("\n\n");

    // Chars user has written - RED-GREEN/BLACK
    for (int i = 0; i < input.size(); i++) {
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
    this->inputFile = "1000words.txt";
    this->randomWorded = true;
    this->setRandomWords(this->inputFile);
    this->input = {};
    this->ch = '\0';
    this->runTime = 0;
    this->numberOfCorrectWords = 0;
    this->timeTrial = false;
}

void TType::run() {

    bool started = false;
    int length = 0; // holds the line length

    chrono::steady_clock::time_point start;

    for (int i = 0; i < size(words); i++) {
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

void TType::runTimeTrial() {

    bool started = false;
    int length = 0; // holds the line length
    int i = 0;
    runTime = 15;
    chrono::steady_clock::time_point start;

    do {
        if (!started) {
            start = steady_clock::now();
            started = true;
        }
        checkChar();
        ch = getch();
        i++;

        input.push_back(ch);

        if (ch == KEY_BACKSPACE) {
            if (i > 0)
                i -= 2;
            else
                i--;
            input.pop_back();
            input.resize(i + 1);
        }
    } while (std::chrono::steady_clock::now() - start < chrono::seconds(int(runTime)));

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
    if (this->randomWorded) {
        setRandomWords(this->inputFile);
    }
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
    this->randomWorded = true;
    words.clear();
    this->inputFile = fileName;
    // open files
    string str;
    ifstream f;
    f.open("./../text/" + this->inputFile);
    getline(f, str);

    // convert string to array
    vector<string> wordsArray;
    stringstream ss(str);
    string tmp;
    while (std::getline(ss, tmp, ' ')) {
        wordsArray.push_back(tmp);
    }

    // select words
    int wordLimit;

    if (timeTrial) {
        // wordLimit = wordsArray.size();
        wordLimit = 20;
    } else {
        wordLimit = 5;
    }

    srand(time(NULL));
    for (int i = 0; i < wordLimit; i++) {
        int num = rand() % wordsArray.size();
        words.append(wordsArray[num] + " ");
        wordsArray.erase(wordsArray.begin() + num);
    }
    words.erase(words.begin() + words.length() - 1);
}
