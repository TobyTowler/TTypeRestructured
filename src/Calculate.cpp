#include "Calculate.h"
#include "TType.h"
#include "ncurses.h"

void calculateScore(TType obj){
    int right = 0;

    for(int i = 0; i<obj.getInput().size(); i++){
        if(obj.getWords().at(i) == obj.getInput().at(i)) {right++;}
    }

    printw("\n\n--GAME OVER-- \nYou scored;\n");
    printw("  Accuracy: %0.f%%        ", double(right)/double(obj.getWords().size())*100);

    //Calculate WPM
    int WPM;
    printw("WPM: %d\n\n", WPM);

    refresh();
}