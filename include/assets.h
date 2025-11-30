#ifndef ASSETS_H
#define ASSETS_H

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

Texture2D* load_dice_sides(const char* director);
void unload_dice_sides(Texture2D* dices);

#endif
