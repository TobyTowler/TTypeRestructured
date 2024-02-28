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
};

#endif // TTYPE_H
