#ifndef CHART_H
#define CHART_H
#include "raylib.h"

extern int chart_width;
extern int chart_height;

extern int x_start_pos;
extern int y_start_pos;

void draw_chart_layout(int axis_max, Font font);
void draw_histogram(int min_sum, int max_sum, int axis_max, int* frequency);

#endif
