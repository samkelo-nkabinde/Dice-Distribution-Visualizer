#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdlib.h>
#include <stdbool.h>
#include "raymath.h"
#define MAX_DICE 6
#define MAX_SUM (MAX_DICE * 6 + 1) // +1 for zero index

typedef struct {

    int dice_count;                
    size_t total_rolls;          
    int frequency[MAX_SUM]; 
    int max_frequency;               
    bool is_auto_rolling;             
    int auto_roll_speed;

} simulation_state_t;

void init_simulation(simulation_state_t* simulator);
void reset_simulation(simulation_state_t* simulator);
void roll_dice(simulation_state_t* simulator);
double get_probility(int dice_count, int sum);

#endif
