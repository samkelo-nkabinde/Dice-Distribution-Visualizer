#include "chart.h"

int chart_width;
int chart_height;

void draw_chart_layout(int chart_x, int chart_y, int axis_max, Font font)
{
	DrawLine(chart_x, chart_y, chart_x, chart_y + chart_height, LIGHTGRAY);
	DrawLine(chart_x, chart_y + chart_height, chart_x + chart_width, chart_y + chart_height, LIGHTGRAY);
	DrawText("Dice Roll Outcome",chart_width/2, chart_y + chart_height + 30, 20, LIGHTGRAY);
	DrawTextPro(font, "Frequency", (Vector2){chart_x - 60, 1.5*chart_height},(Vector2){0, 0}, -90.0, 20, 2.0, LIGHTGRAY);
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
}

void draw_histogram(int min_sum, int max_sum, int chart_x, int axis_max, int chart_y, int* frequency)
{
	int bar_count = max_sum - min_sum + 1;
	if(bar_count > 0)
	{
		float bar_width = (float)chart_width / bar_count;
		for(int i = 0; i <= max_sum; ++i)
		{
			float bar_height = ((float)frequency[i] / axis_max )*(chart_height - 20);
			float x_pos = chart_x + (i - min_sum)*bar_width;
			float y_pos = (chart_y + chart_height) - bar_height;
			DrawRectangleRec((Rectangle){x_pos + 1, y_pos, bar_width - 4, bar_height}, SKYBLUE);
					
				
			const char* label = TextFormat("%d", i);
			int label_width = MeasureText(label, 10);
			if(((int)x_pos + bar_width/2 - label_width/2) > 80)
				DrawText(label, (int)x_pos + bar_width/2 - label_width/2, chart_y + chart_height + 5, 10, LIGHTGRAY);
		}
	}
}
