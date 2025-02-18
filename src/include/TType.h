#ifndef TTYPE_H
#define TTYPE_H
#include <string>
#include <vector>

using namespace std;

class TType {
  private:
    string words;
    vector<int> input;
    int ch;
    double runTime;
    int numberOfCorrectWords;
    bool randomWorded;

  public:
    enum CurrentScreen { TITLE, SCORE };

    string inputFile;
    bool timeTrial;
    CurrentScreen currentScreen;

    TType();

    void setWords(string fileName); // Custom text

    void clearInput();

    void checkChar();

    void run();

    void runTimeTrial();

    int getNumberOfSpaces();

    int getRawWPM();

    void checkCharAndRealWPM();

    int getAccuracy();

    void printScore();

    void resetGame();

    void setLines();

    void setRandomWords(string fileName);
};

#endif // TTYPE_H
