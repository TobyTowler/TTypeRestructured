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

  public:
    int getCh() const;

    void setCh(int ch);

    TType();

    void setWords(string fileName); // Custom text

    string getWords(); // get string words

    void clearWords();

    void clearInput();

    void checkChar();

    vector<int> getInput();

    void setInput(const vector<int> &input);

    void addToInput(char c);

    void run();

    double getRunTime();

    int getNumberOfSpaces();

    int getNumberOfWords();

    void setNumberOfCorrectWords(int num);

    int getNumberOfCorrectWords();

    int getRawWPM();

    void checkCharAndRealWPM();

    int getAccuracy();

    void printScore();

    void resetGame();
};

#endif // TTYPE_H
