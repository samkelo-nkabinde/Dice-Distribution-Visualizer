#include <stdio.h>
#include "raylib.h"
#include "assets.h"
#include "ui.h"
#include "simulation.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FRAME_RATE 30


int main()
{
	Image icon = LoadImage("assets/icon.png");
	Font main_font = LoadFont("assets/Lato-Bold.ttf");

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dice Distribution Vizualizer");
	SetWindowIcon(icon);
	SetTargetFPS(FRAME_RATE);

	GuiSetStyle(DEFAULT, TEXT_SIZE, 18);

	Texture2D* dice_sides = load_dice_sides("assets/Dice Sides");

	simulation_state_t sim;
	init_simulation(&sim);
	
	int current_dice_count = 0;
	int prev_dice_count = 0;


	while(!WindowShouldClose())
	{

		BeginDrawing();
			main_layout();
			current_dice_count = (int)round(dice_count_input);

			if(sim.is_auto_rolling)
			{
				for(int i = 0; i < sim.auto_roll_speed; ++i) roll_dice(&sim);
			}
	
			if(current_dice_count > prev_dice_count && current_dice_count < 6)
			{
				current_dice_count = (int)round(dice_count_input);
				prev_dice_count = current_dice_count;
				sim.dice_count++;	
				reset_simulation(&sim);
			}

			if(prev_dice_count < current_dice_count && prev_dice_count < 6)
			{
				current_dice_count = (int)round(dice_count_input);
				prev_dice_count = current_dice_count;
				sim.dice_count--;
				reset_simulation(&sim);
			}
			printf("%d\n", sim.dice_count);

			if(draw_button(roll_button, "ROLL" , false)) roll_dice(&sim);
			
			if(draw_button(reset_button, "RESET", false)) reset_simulation(&sim);

			if(draw_button(auto_roll_button, sim.is_auto_rolling ? "STOP ROLL": "AUTO ROLL", sim.is_auto_rolling))
			{
				sim.is_auto_rolling = !sim.is_auto_rolling;
			}

			int chart_x = 80;
			int chart_y = 320;
			int chart_width =  SCREEN_WIDTH - 500;
			int chart_height = SCREEN_HEIGHT - 380;
			DrawLine(chart_x, chart_y, chart_x, chart_y + chart_height, LIGHTGRAY);
			DrawLine(chart_x, chart_y + chart_height, chart_x + chart_width, chart_y + chart_height, LIGHTGRAY);
			int axis_max = (sim.max_frequency > 0) ? sim.max_frequency: 10;

			int ticks_count  = 5;

			for(int i = 0; i <= ticks_count; ++i)
			{
				float normalize = (float)i / ticks_count;
				int normalized_value = (int)(normalize*axis_max);
				float y_pos = (chart_y + chart_height) - (normalize * (chart_height - 10));
				DrawLine(chart_x - 5, (int)y_pos, chart_x, (int)y_pos, LIGHTGRAY);
				const char* label = TextFormat("%d", normalized_value);
				int text_width = MeasureText(label, 10);
				DrawText(label, chart_x - 10 - text_width, (int)y_pos - 5, 10, LIGHTGRAY);
			}
			int min_sum = sim.dice_count;
			int max_sum = sim.dice_count*6;
			int bar_count = max_sum - min_sum + 1;
			if(bar_count > 0)
			{
				float bar_width = (float)chart_width / bar_count;
				for(int i = 0; i <= max_sum; ++i)
				{
					int count = sim.frequency[i];
					float bar_height = ((float)count / axis_max )*(chart_height - 20);
					float x_pos = chart_x + (i - min_sum)*bar_width;
					float y_pos = (chart_y + chart_height) - bar_height;
					DrawRectangleRec((Rectangle){x_pos + 1, y_pos, bar_width - 2, bar_height}, SKYBLUE);
					
					const char* label = TextFormat("%d", i);
					int label_width = MeasureText(label, 10);
					DrawText(label, (int)x_pos + bar_width/2 - label_width/2, chart_y + chart_height + 5, 10, LIGHTGRAY);
				}
			}
			

		EndDrawing();
	}
	UnloadImage(icon);
	UnloadFont(main_font);
	unload_dice_sides(dice_sides);
}
