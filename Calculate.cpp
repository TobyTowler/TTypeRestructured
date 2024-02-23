#include "Calculate.h"
#include "TType.h"
#include "ncurses.h"

void calculateScore(TType obj){
    int right = 0;

    for(int i = 0; i<obj.getInput().size(); i++){
        if(obj.getWords().at(i) == obj.getInput().at(i)) {right++;}
    }

    printw("\n\nYour accuracy was %0.f%%", double(right)/double(obj.getWords().size())*100);

    //Calculate WPM
    //chrono::duration<double> wpm = elapsed/ calculateWords(char words[], maxSize);
    printw("\nWell done! \n\n");

    refresh();
}