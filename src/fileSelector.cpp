#include "include/fileSelector.h"
#include "include/Colours.h"
#include <filesystem>
#include <ncurses.h>
#include <vector>

/*
 * fileSelector
 * keyboard up and down selector
 * search fuzzy find
 *
 *
 */

string fileSelector(string path) {
    vector<string> files;
    for (const auto &entry : filesystem::directory_iterator(path)) {
        files.push_back(entry.path().filename().string());
    }
    string chosen = files[0];

    bool play = true;
    int selected = 0;
    while (play) {
        clear();
        printw("Available Files: ");
        for (int i = 0; i < files.size(); i++) {
            if (i == selected) {
                attron(COLOR_PAIR(NcursesColors::BACKGROUND_CURSORPAIR));
                printw("\n  %s", files[i].c_str());
                attroff(COLOR_PAIR(NcursesColors::BACKGROUND_CURSORPAIR));
            } else {
                printw("\n  %s", files[i].c_str());
            }
        }
        int ch = getch();
        switch (ch) {
        case 'j':
            selected++;
            break;
        case 'k':
            selected--;
            break;
        case 'q':
            return "";
            break;
        case 10:
            chosen = selected;
            play = false;
            break;
        }
        if (selected > files.size() - 1) {
            selected = 0;
        } else if (selected < 0) {
            selected = files.size() - 1;
        }
    }

    return files[selected];
}
