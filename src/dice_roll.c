#include <math.h>
#include <string.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


Texture2D* load_dice_sides(const char* director);
void unload_dice_sides(Texture2D* dices);
void draw_layout(void);


float dice_count = 0;
bool auto_roll = false;
float number_of_rolls = 0;

int main(void)
{
	Image icon = LoadImage("asserts/icon.png");
	Font font = LoadFont("asserts/Lato-Bold.ttf");

	InitWindow(1280, 720, "Distribution Vizualizer");
	Texture2D* dice_sides = load_dice_sides("asserts/Dice Sides");
	
	Vector2 dice_image_position[6] = {{10/0.6, 40}, {100/0.6, 40}, {200/0.6, 40}, {300/0.6, 40}, {400/0.6, 40}, {500/0.6, 40}};

	SetWindowIcon(icon);
	SetTargetFPS(60);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 18);



	while(!WindowShouldClose())
	{
	 	BeginDrawing();
			DrawTextureEx(dice_sides[0], dice_image_position[0],0, 0.6f, WHITE);
			DrawTextureEx(dice_sides[1], dice_image_position[1],0, 0.6f, WHITE);
			DrawTextureEx(dice_sides[2], dice_image_position[2],0, 0.6f, WHITE);
                        DrawTextureEx(dice_sides[3], dice_image_position[3],0, 0.6f, WHITE);
                        DrawTextureEx(dice_sides[4], dice_image_position[4],0, 0.6f, WHITE);
                        DrawTextureEx(dice_sides[5], dice_image_position[5],0, 0.6f, WHITE);
               		draw_layout();

		EndDrawing();

	}
	unload_dice_sides(dice_sides);	
	CloseWindow();
	UnloadImage(icon);
	UnloadFont(font);
	return 0;
}

void draw_layout(void)
{
	ClearBackground((Color){20, 20, 20, 255});
	DrawText("The Statistics of Rolling a Dice", 420, 20, 20, LIGHTGRAY);

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

}

Texture2D* load_dice_sides(const char* dir)
{
	Texture2D* dice = malloc(sizeof(Texture2D)*6);
	if(dice == NULL)
	{
		fprintf(stderr, "Memory Allocation failed");
		exit(EXIT_FAILURE);
	}
	
	if (chdir(dir) != 0) 
	{
        	fprintf(stderr, "Failed to open directory: %s\n", dir);
        	free(dice);
        	exit(EXIT_FAILURE);
	}

	DIR* directory = opendir(".");
	struct dirent* entry;
	struct stat file_stat;
	int i;
	while((entry = readdir(directory)) != NULL)
	{
		if(stat(entry->d_name, &file_stat) == 0 && S_ISREG(file_stat.st_mode))
		{
			i = entry->d_name[0] - '0';
		}
		if (i >= 1 && i <= 6)
		{
			dice[i-1] = LoadTexture(entry->d_name); 
		}
	}

	closedir(directory);
	return dice;

}

void unload_dice_sides(Texture2D* dice)
{
	for(int i = 0; i < 6; ++i) UnloadTexture(dice[i]);
	free(dice);
}
