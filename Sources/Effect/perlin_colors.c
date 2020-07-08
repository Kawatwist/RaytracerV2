#include "rt.h"
#include "thread.h"

int perlin_color_cloud(float val)
{
	int color;

	color = 0xFF000080;
	val = (int)val - val;
	if(val < 0)
		val = -val;
	if (val > 1)
		val = 1;
	color = color + ((int)(val * 255) << 16) + ((int)(val * 255) << 8) + (int)(val * 127);
	return (color);
}

int perlin_color_marble(float val)
{
	int color;

	color = 0xFF000000;
	val = (int)val - val;
	if(val < 0)
		val = -val;
	if (val > 1)
		val = 1;
	color = color + ((int)(val * 255) << 16) + ((int)(val * 255) << 8) + (int)(val * 255);
	return (color);
}

int perlin_color_wood(float val)
{
	int color;

	color = 0xFF502020;
	val = (int)val - val;
	if(val < 0)
		val = -val;
	if (val > 1)
		val = 1;
	color = color + ((int)(val * 128) << 16) + ((int)(val * 128) << 8);
	return (color);
}