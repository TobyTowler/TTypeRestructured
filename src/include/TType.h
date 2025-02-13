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
    string inputFile;
    bool randomWorded;

  public:
    TType();

    void setWords(string fileName); // Custom text

    void clearInput();

    void checkChar();

    void run();

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
