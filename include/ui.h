#ifndef UI_H 
#define UI_H

#include <stdbool.h>
#include "raylib.h"
#include "raygui.h"

extern const Color BACKGROUND_COLOUR;
extern const Color BAR_COLOUR;
extern const Color HIGHLIGHT_COLOUR;

extern Rectangle roll_button;
extern Rectangle auto_roll_button;
extern Rectangle reset_button;

extern float dice_count_input;
extern float auto_roll_speed_input;


void main_layout();
bool draw_button(Rectangle rect, const char* text, bool active);

#endif
