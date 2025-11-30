#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "raylib.h"
#include "simulation.h"


void init_simulation(simulation_state_t* simulator)
{
	simulator->dice_count = 1;
	simulator->total_rolls = 0;
	simulator->max_frequency = 0;
	simulator->is_auto_rolling = false;
	simulator->auto_roll_speed = 1.0;
	memset(simulator->frequency, 0, MAX_SUM*sizeof(int));
}

void reset_simulation(simulation_state_t* simulator)
{
	simulator->total_rolls = 0;
	simulator->max_frequency = 0;
	memset(simulator->frequency, 0, MAX_SUM*sizeof(int));
}

void roll_dice(simulation_state_t* simulator)
{
	int sum = 0;
	for(int i = 0; i < simulator->dice_count; ++i) sum += GetRandomValue(1, 6);

	if(sum < MAX_SUM)
	{
		simulator->frequency[sum]++;
		simulator->total_rolls++;
		if (simulator->frequency[sum] > simulator->max_frequency)
			simulator->max_frequency = simulator->frequency[sum];			
	}
}

double get_probility(int dice_count, int sum)
{
	double mean = 3.5*dice_count;
	double st_deviation = sqrt(dice_count * 35.0/12.0);
	double exponent = -0.5 * pow((sum - mean) / st_deviation, 2.0);
	return (1.0 / (st_deviation * sqrt(2.0 * M_PI))) * exp(exponent);
}
