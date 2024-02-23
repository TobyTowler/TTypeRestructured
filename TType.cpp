#include <sstream>
#include <fstream>
#include "iostream"
#include <cstring>
#include "TType.h"
#include "ncurses.h"

//Custom text
void TType::setWords(string fileName){
    stringstream str;
    ifstream file;
    file.open(fileName);
    str << file.rdbuf();
    words = str.str();
}

string TType::getWords(){
    return words;
}

void TType::clearWords() {
    setWords("default.txt");
}

void TType::clearInput() {
    input.clear();
}

/*************************************
 * Method for checking and colouring characters
 *************************************/
void TType::checkChar(){
    string str =  words;
    char wordsChar[str.length()-1];
    strcpy(wordsChar, str.c_str());

    clear();

    //Colour pairs definition
    short GREEN = 1, RED = 2, WHITE = 3, MAGENTA = 4;
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);

    //Chars user has written - RED-GREEN/BLACK
    for(int i = 0; i< input.size(); i++) {
        if (words.at(i) == input.at(i)) {
            attron(COLOR_PAIR(GREEN));
            printw("%c", words.at(i));
            attroff(COLOR_PAIR(GREEN));
        }
        else{
            attron(COLOR_PAIR(RED));
            printw("%c", words.at(i));
            attroff(COLOR_PAIR(RED));
        }
    }

    //Current char - WHITE/MAGENTA
    attron(COLOR_PAIR(MAGENTA));
    printw("%c", words[input.size()]);
    attroff(COLOR_PAIR(MAGENTA));

    //Chars not yet reached - WHITE/BLACK
    for(int o = this->getInput().size()+1; o<str.length(); o++) {
        attron(COLOR_PAIR(WHITE));
        printw("%c", words[o]);
        attroff(COLOR_PAIR(WHITE));
    }


    refresh();
}

const vector<int> &TType::getInput() const {
    return input;
}

void TType::addToInput(char c) {
    input.push_back(c);
}

TType::TType() {
    this->setWords("default.txt");
    this->input = {};
    this->ch = '\0';
}

int TType::getCh() const {
    return ch;
}

void TType::setCh(int ch) {
    this->ch = ch;
}

void TType::run() {
    for (int i = 0; i < size(words) ; i++) {
        checkChar();
        ch = getch();
        addToInput(ch);


        if (ch == KEY_BACKSPACE) {
            if (i > 0) i -= 2;
            else i--;
            input.pop_back();
            input.resize(i + 1);
        }
    }

    checkChar();
}

