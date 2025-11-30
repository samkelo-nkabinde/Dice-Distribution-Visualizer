
#define RAYGUI_IMPLEMENTATION
#include "ui.h"

const Color BACKGROUND_COLOUR = {20, 20, 20, 255};
const Color BAR_COLOUR = {70, 130, 180, 255};
const Color HIGHLIGHT_COLOUR = {100, 160, 210, 255};

Rectangle roll_button = {1000, 360, 220, 60};
Rectangle auto_roll_button = {1000, 440, 220, 60};
Rectangle reset_button = {1000, 520, 220, 60};

float dice_count_input = 0;
float auto_roll_speed_input = 0;

void main_layout()
{
	ClearBackground(BACKGROUND_COLOUR);
	DrawText("The Statistics of Rolling a Dice", 420, 20, 20, LIGHTGRAY);

	GuiGroupBox((Rectangle){20, 60, 1240, 180}, "Dice");
	GuiGroupBox((Rectangle){20, 260, 920, 440}, "Distribution");

	GuiGroupBox((Rectangle){960, 260, 300, 440}, "Controls");
	DrawText("Number of Dice:", 1000, 280, 20, LIGHTGRAY);
							
	GuiSlider((Rectangle){ 1000, 320, 220, 20 }, "", NULL, &dice_count_input, 1.0f, 6.0f);
	DrawText(TextFormat("%i", (int)round(dice_count_input)), 1180, 280, 20, LIGHTGRAY);

	DrawText("Auto Roll Speed:", 1000, 640, 20, LIGHTGRAY);
	DrawText(TextFormat("%i", (int)round(auto_roll_speed_input)), 1180, 640, 20, LIGHTGRAY);
	GuiSlider((Rectangle){ 1000, 600, 220, 20 }, "", NULL, &auto_roll_speed_input, 1.0f, 5.0f);


}

bool draw_button(Rectangle rect, const char* text, bool active)
{	bool clicked = false;
	Vector2 mousePoint = GetMousePosition();
	bool isHover = CheckCollisionPointRec(mousePoint, rect);
    
	Color color = active ? SKYBLUE : LIGHTGRAY;
	if (isHover) color = active ? BLUE : GRAY;
	if (active && isHover) color = DARKBLUE;
    
	DrawRectangleRec(rect, color);
	DrawRectangleLinesEx(rect, 2, DARKGRAY);
    
	int textWidth = MeasureText(text, 20);
	DrawText(text, (int)(rect.x + rect.width/2 - textWidth/2), (int)(rect.y + rect.height/2 - 10), 20, active ? WHITE : BLACK);
    
	if (isHover && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
	{
	    clicked = true;
	}
	return clicked;
}
