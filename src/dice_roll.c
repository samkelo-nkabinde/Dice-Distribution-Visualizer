#include <math.h>
#include <string.h> 
#include <stdbool.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(void)
{
	Image icon = LoadImage("asserts/icon.png");
	Font font = LoadFont("asserts/Lato-Bold");
	InitWindow(1280, 720, "Distribution Vizualizer");

	SetWindowIcon(icon);
	SetTargetFPS(60);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 18);


	float dice_count = 0;
	bool auto_roll = false;

	while(!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground((Color){20, 20, 20, 255});
			DrawText("The Statistics of Rolling a Dice", 420, 20, 20, LIGHTGRAY);
			//DrawRectangleLines(20, 50, 1240, 200, DARKGRAY);

			GuiGroupBox((Rectangle){20, 60, 1240, 180}, "Dice");
			GuiGroupBox((Rectangle){20, 260, 920, 440}, "Distribution");

			GuiGroupBox((Rectangle){960, 260, 300, 440}, "Controls");
			DrawText("Number of Dice", 1000, 280, 20, LIGHTGRAY);
							
			GuiSlider((Rectangle){ 1000, 360, 220, 20 }, "", NULL, &dice_count, 1.0f, 6.0f);
			DrawText(TextFormat("%i", (int)round(dice_count)), 1000, 320, 20, LIGHTGRAY);

			GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
			GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(LIGHTGRAY));
			GuiButton((Rectangle){ 1000, 400, 220, 60 }, "ROLL");

			DrawText("Roll automatically",1000, 480, 18, LIGHTGRAY);
			GuiCheckBox((Rectangle){ 1000, 520, 20, 20 }, "", &auto_roll);

            		//GuiSlider((Rectangle){ 150, 610, 200, 20 }, "High Freq", NULL, &frequency2, 10.0f, 100.0f);
            
            		//GuiSlider((Rectangle){ 600, 580, 200, 20 }, "Amplitude", NULL, &amplitude1, 0.1f, 2.0f);
            	//	GuiSlider((Rectangle){ 600, 610, 200, 20 }, "Noise Level", NULL, &noiseLevel, 0.0f, 2.0f);

		EndDrawing();

	}
	CloseWindow();
	UnloadImage(icon);
	UnloadFont(font);
	return 0;
}
