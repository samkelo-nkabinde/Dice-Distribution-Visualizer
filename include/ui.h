#ifndef UI_H 
#define UI_H

#include <stdbool.h>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

extern const Color BACKGROUND_COLOUR;
extern const Color BAR_COLOUR;
extern const Color HIGHLIGHT_COLOUR;

void main_layout();
bool DrawButton(Rectangle rect, const char* text, bool active);

#endif
