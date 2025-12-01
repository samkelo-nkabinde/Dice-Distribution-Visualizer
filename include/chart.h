#ifndef CHART_H
#define CHART_H
#include "raylib.h"
extern int chart_width;
extern int chart_height;

void draw_chart_layout(int chart_x, int chart_y, int axis_max, Font font);
void draw_histogram(int min_sum, int max_sum,  int chat_x, int chart_y, int axis_max, int* frequency);

#endif
