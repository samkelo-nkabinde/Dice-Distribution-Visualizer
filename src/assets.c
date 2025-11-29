#include "assets.h"

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
	int i = -1;
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
