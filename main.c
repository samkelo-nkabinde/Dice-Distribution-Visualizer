#include <stdio.h>
#include <stdbool.h>

#include "raylib.h"
#include "assets.h"
#include "ui.h"
#include "simulation.h"
#include "chart.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FRAME_RATE 30
chart_width = SCREEN_WIDTH - 500;
chart_height = SCREEN_HEIGHT - 380;
x_start_pos = 100;
y_start_pos = 300;


void control_dice_count(simulation_state_t* sim);
void control_roll_speed(simulation_state_t* sim);
void draw_dice(Vector2* position, Texture2D* images, simulation_state_t* sim);

int main()
{
	Image icon = LoadImage("assets/icon.png");
	Font main_font = LoadFont("assets/Lato-Bold.ttf");

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dice Distribution Vizualizer");
	SetWindowIcon(icon);
	SetTargetFPS(FRAME_RATE);

	GuiSetStyle(DEFAULT, TEXT_SIZE, 18);

	Texture2D* dice_sides = load_dice_sides("assets/Dice Sides");
	Vector2 image_position[MAX_DICE] = {0};
	for(int i = 0; i < MAX_DICE; ++i) image_position[i].y = 90;

	simulation_state_t sim;
	init_simulation(&sim);
	
	while(!WindowShouldClose())
	{
	
		if(sim.is_auto_rolling) control_roll_speed(&sim);
	
		BeginDrawing();
			main_layout();
			draw_dice(image_position, dice_sides, &sim);
			control_dice_count(&sim);	

			if(draw_button(roll_button, "ROLL" , false)) roll_dice(&sim);
			
			if(draw_button(reset_button, "RESET", false)) reset_simulation(&sim);

			if(draw_button(auto_roll_button, sim.is_auto_rolling ? "STOP ROLL": "AUTO ROLL", sim.is_auto_rolling))
			{
				sim.is_auto_rolling = !sim.is_auto_rolling;
			}

			int axis_max =(sim.max_frequency > 0) ? sim.max_frequency : 10;
			draw_chart_layout(axis_max, main_font);
			DrawText(TextFormat("Total of rolls: %d", sim.total_rolls), 700, 280, 20, LIGHTGRAY); 
			draw_histogram(sim.dice_count, sim.dice_count*MAX_DICE, axis_max, sim.frequency);			

		EndDrawing();
	}
	UnloadImage(icon);
	UnloadFont(main_font);
	unload_dice_sides(dice_sides);
}

void control_dice_count(simulation_state_t* sim)
{
	int dice_count = (int)round(dice_count_input);
	if(dice_count > sim->dice_count && sim->dice_count < MAX_DICE)
	{
		sim->dice_count ++; 				
		reset_simulation(sim);
	}

	if(dice_count < sim->dice_count && sim->dice_count > 1)
	{
		sim->dice_count --; 
		reset_simulation(sim);
	}
}

void control_roll_speed(simulation_state_t* sim)
{
	sim->rolls_per_frame = auto_roll_speed_input*0.1;
	sim->rolls_pass += sim->rolls_per_frame;
	while(sim->rolls_pass >= 1.0)
	{
		roll_dice(sim);
		sim->rolls_pass -= 1.0;
	}
}

void draw_dice(Vector2* position, Texture2D* images, simulation_state_t* sim)
{
	switch((int)round(dice_count_input))
	{
		case 1:
		{
			position[0].x = 580;
			DrawTextureEx(images[sim->rolls[0] - 1], 
					position[0], 
					0.0, 0.6, 
					WHITE);
			break;
		}
		case 2:
		{
			position[0].x = 480;
			position[1].x = 640;
			for(int i = 0; i < 2; ++i)
			{
				DrawTextureEx(images[sim->rolls[i] - 1], 
						position[i],
						0.0, 0.6, 
						WHITE);
			}
			break;
		}
		case 3:
		{
			position[0].x = 580;
			position[1].x = 420;
			position[2].x = 740;
			for(int i = 0; i < 3; ++i)
			{
				DrawTextureEx(images[sim->rolls[i] - 1], 
						position[i],
						0.0, 0.6, 
						WHITE);
			}

			break;
		}
		case 4:
		{
			break;
		}
		case 5:
		{
			break;
		}
		case 6:
		{
			break;
		}
		default:
			return;
	}
}
