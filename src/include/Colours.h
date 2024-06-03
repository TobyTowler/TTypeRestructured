#ifndef COLOURS_H
#define COLOURS_H

#include <ncurses.h>

namespace NcursesColors {

// GRUVBOX THEME
//  COLOURS
constexpr int BACKGROUND = 0;
constexpr int TITLE = 1;
constexpr int SUB = 2;
constexpr int TEXT = 3;
constexpr int GREEN_TEXT = 4;
constexpr int RED_TEXT = 5;
constexpr int BACKGROUND_CURSOR = 6;
constexpr int SCORE = 7;

// PAIRS
constexpr int TITLEPAIR = 10;
constexpr int SUBPAIR = 11;
constexpr int TEXTPAIR = 12;
constexpr int GREEN_TEXTPAIR = 13;
constexpr int RED_TEXTPAIR = 14;
constexpr int BACKGROUND_CURSORPAIR = 15;
constexpr int SCORE_PAIR = 16;

inline void initCustomColor() {

    // Initialize custom color
    init_color(BACKGROUND, 40 * 1000 / 255, 40 * 1000 / 255, 40 * 1000 / 255);
    init_color(TITLE, 215 * 1000 / 255, 153 * 1000 / 255, 33 * 1000 / 255);
    init_color(SUB, 69 * 1000 / 255, 133 * 1000 / 255, 136 * 1000 / 255);
    init_color(TEXT, 235 * 1000 / 255, 219 * 1000 / 255, 178 * 1000 / 255);
    init_color(GREEN_TEXT, 104 * 1000 / 255, 157 * 1000 / 255, 106 * 1000 / 255);
    init_color(RED_TEXT, 204 * 1000 / 255, 36 * 1000 / 255, 39 * 1000 / 255);
    init_color(BACKGROUND_CURSOR, 178 * 1000 / 255, 98 * 1000 / 255, 134 * 1000 / 255);
    init_color(SCORE, 152 * 1000 / 255, 151 * 1000 / 255, 26 * 1000 / 255);
}

// Initialize color pairs
inline void initColorPairs() {
    init_pair(TITLEPAIR, TITLE,
              BACKGROUND); // Assign the custom color to pair number 1 with a black background
    init_pair(SUBPAIR, SUB, BACKGROUND);
    init_pair(TEXTPAIR, TEXT, BACKGROUND);
    init_pair(GREEN_TEXTPAIR, GREEN_TEXT, BACKGROUND);
    init_pair(RED_TEXTPAIR, RED_TEXT, BACKGROUND);
    init_pair(BACKGROUND_CURSORPAIR, TEXT, BACKGROUND_CURSOR);
    init_pair(SCORE_PAIR, SCORE, BACKGROUND);
}

} // namespace NcursesColors

#endif // !colours
