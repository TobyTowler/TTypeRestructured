#include "TType.h"
#include "chrono"
#include "ncurses.h"
#include <chrono>
#include <fstream>
#include <sstream>

// Custom text
void TType::setWords(string fileName) {
  stringstream str;
  std::ifstream inputFile("text/" + fileName);
  str << inputFile.rdbuf();
  inputFile.close();
  words = str.str();
}

string TType::getWords() { return words; }

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

  // Colour pairs definition
  short GREEN = 1, RED = 2, WHITE = 3, MAGENTA = 4;
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_WHITE, COLOR_BLACK);
  init_pair(4, COLOR_WHITE, COLOR_MAGENTA);

  // Chars user has written - RED-GREEN/BLACK
  for (int i = 0; i < input.size(); i++) {
    length++;
    // width-10 is a rough value thast seems to look decent since most words
    // arent over 10 characters long could make it dynamic based on distance to
    // next space in words
    if (length > width - 10 && words.at(i - 1) == ' ') {
      printw("\n");
      length = 0;
    }

    if (words.at(i) == input.at(i)) {
      attron(COLOR_PAIR(GREEN));
      printw("%c", words.at(i));
      attroff(COLOR_PAIR(GREEN));
    } else {
      attron(COLOR_PAIR(RED));
      printw("%c", words.at(i));
      attroff(COLOR_PAIR(RED));
    }
  }

  // Current char - WHITE/MAGENTA
  attron(COLOR_PAIR(MAGENTA));
  printw("%c", words[input.size()]);
  attroff(COLOR_PAIR(MAGENTA));

  // Chars not yet reached - WHITE/BLACK
  for (int o = input.size() + 1; o < words.length(); o++) {
    length++;
    if (length > width - 10 && words.at(o - 1) == ' ') {
      printw("\n");
      length = 0;
    }

    attron(COLOR_PAIR(WHITE));
    printw("%c", words[o]);
    attroff(COLOR_PAIR(WHITE));
  }

  refresh();
}

vector<int> TType::getInput() { return input; }

void TType::addToInput(char c) { input.push_back(c); }

TType::TType() {
  this->setWords("default.txt");
  this->input = {};
  this->ch = '\0';
  this->runTime = 0;
  this->numberOfCorrectWords = 0;
}

int TType::getCh() const { return ch; }

void TType::setCh(int ch) { this->ch = ch; }

void TType::run() {

  int length = 0; // holds the line length

  auto start = std::chrono::steady_clock::now();

  for (int i = 0; i < size(words); i++) {

    checkChar();
    ch = getch();
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

double TType::getRunTime() { return runTime; }

int TType::getNumberOfSpaces() {
  int num = 0;
  for (char c : words) {
    if (c == ' ') {
      num++;
    }
  }
  return num;
}

void TType::setNumberOfCorrectWords(int num) { numberOfCorrectWords = num; }

int TType::getNumberOfCorrectWords() { return numberOfCorrectWords; }

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

  // Colour pairs definition
  short GREEN = 11, RED = 10;
  init_pair(11, COLOR_GREEN, COLOR_BLACK);
  init_pair(10, COLOR_RED, COLOR_BLACK);

  // Chars user has written - RED-GREEN/BLACK
  for (int i = 0; i < input.size(); i++) {
    length++;
    // width-10 is a rough value thast seems to look decent since most words
    // arent over 10 characters long could make it dynamic based on distance to
    // next space in words
    if (length > width - 10 && words.at(i - 1) == ' ') {
      printw("\n");
      length = 0;
    }

    if (words.at(i) == input.at(i)) {
      attron(COLOR_PAIR(GREEN));
      printw("%c", words.at(i));
      attroff(COLOR_PAIR(GREEN));
    } else {
      attron(COLOR_PAIR(RED));
      printw("%c", words.at(i));
      attroff(COLOR_PAIR(RED));
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
  printw("--GAME OVER--\nYou Scored:\n\n");
  printw("  Accuracy: %d%%", getAccuracy());
  printw("        WPM: %d", int((numberOfCorrectWords * 60) / runTime));
  printw("        Raw WPM: %d", int((getNumberOfSpaces() + 1) * 60 / runTime));
  printw("\n\n\n\n");

  refresh();
}
