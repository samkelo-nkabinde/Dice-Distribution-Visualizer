#include <stdio.h>
#include "raylib.h"
#include "assets.h"
#include "ui.h"
#include "simulation.h"
#include "chart.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FRAME_RATE 30

void control_dice_count(simulation_state_t* sim);
void control_roll_speed(simulation_state_t* sim);

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
	
	while(!WindowShouldClose())
	{
	
		if(sim.is_auto_rolling) control_roll_speed(&sim);
	
		BeginDrawing();
			main_layout();
			control_dice_count(&sim);	

			if(draw_button(roll_button, "ROLL" , false)) roll_dice(&sim);
			
			if(draw_button(reset_button, "RESET", false)) reset_simulation(&sim);

			if(draw_button(auto_roll_button, sim.is_auto_rolling ? "STOP ROLL": "AUTO ROLL", sim.is_auto_rolling))
			{
				sim.is_auto_rolling = !sim.is_auto_rolling;
			}

			chart_width = SCREEN_WIDTH - 500;
			chart_height = SCREEN_HEIGHT - 380;
			x_start_pos = 100;
			y_start_pos = 300;
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
