#include "rt.h"




void	input_distance_light(t_data *data, void **light, char ctrl)
{
    if (key_old(*data, SDL_SCANCODE_KP_1) && !ctrl)
		(*(t_light **)light)->distance += 0.1;
	else if (key_old(*data, SDL_SCANCODE_KP_1) && ctrl)
		(*(t_light **)light)->distance -= 0.1;
}


void	input_intensity_light(t_data *data, void **light, char ctrl)
{
    if (key_old(*data, SDL_SCANCODE_KP_2) && !ctrl)
		(*(t_light **)light)->intensity += 0.1;
	else if (key_old(*data, SDL_SCANCODE_KP_2) && ctrl)
		(*(t_light **)light)->intensity -= 0.1;
}

















void	input_color_light(t_data *data, void **light, char ctrl)
{
    if (key_old(*data, SDL_SCANCODE_KP_7) && !ctrl && ((*(t_light **)light)->color & 0xFF0000) >> 16 < 255)
		((char *)&((*(t_light **)light)->color))[2] += 1;
	else if (key_old(*data, SDL_SCANCODE_KP_7) && ctrl && ((*(t_light **)light)->color & 0xFF0000) >> 16 > 0)
		((char *)&((*(t_light **)light)->color))[2] -= 1;
	if (key_old(*data, SDL_SCANCODE_KP_8) && !ctrl && ((*(t_light **)light)->color & 0xFF00) >> 8 < 255)
		((char *)&((*(t_light **)light)->color))[1] += 1;
	else if (key_old(*data, SDL_SCANCODE_KP_8) && ctrl && ((*(t_light **)light)->color & 0xFF00) >> 8 > 0)
		((char *)&((*(t_light **)light)->color))[1] -= 1;
	if (key_old(*data, SDL_SCANCODE_KP_9) && !ctrl && ((*(t_light **)light)->color & 0xFF) < 255)
		((char *)&((*(t_light **)light)->color))[0] += 1;
	else if (key_old(*data, SDL_SCANCODE_KP_9) && ctrl && ((*(t_light **)light)->color & 0xFF) > 0)
		((char *)&((*(t_light **)light)->color))[0] -= 1;
}



void	input_move_light(t_data *data, void **light)
{
    if (key_old(*data, SDL_SCANCODE_SPACE))
		(*(t_light **)light)->origin.y -= 0.1;
	if (key_old(*data, SDL_SCANCODE_LSHIFT))
		(*(t_light **)light)->origin.y += 0.1;
	if (key_old(*data, SDL_SCANCODE_A))
		(*(t_light **)light)->origin.x -= 0.1;
	if (key_old(*data, SDL_SCANCODE_D))
		(*(t_light **)light)->origin.x += 0.1;
	if (key_old(*data, SDL_SCANCODE_W))
		(*(t_light **)light)->origin.z += 0.1;
	if (key_old(*data, SDL_SCANCODE_S))
		(*(t_light **)light)->origin.z -= 0.1;
}