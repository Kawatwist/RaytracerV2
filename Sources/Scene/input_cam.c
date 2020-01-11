#include "rt.h"

static void	rot_cam_input(t_data *data, int key_code)//possibilite de mettre un tmp
{
	if (key_code == SDL_SCANCODE_UP)
	{
		(data->obj.camera[data->obj.index[0]]).sc = add_vec(rotx(sub_vec((data->obj.camera[data->obj.index[0]]).sc, (data->obj.camera[data->obj.index[0]]).pos.origin), 5.0), (data->obj.camera[data->obj.index[0]]).pos.origin);
		(data->obj.camera[data->obj.index[0]]).x = rotx((data->obj.camera[data->obj.index[0]]).x, 5.0);
		(data->obj.camera[data->obj.index[0]]).y = rotx((data->obj.camera[data->obj.index[0]]).y, 5.0);
	}
	if (key_code == SDL_SCANCODE_DOWN)
	{
		(data->obj.camera[data->obj.index[0]]).sc = add_vec(rotx(sub_vec((data->obj.camera[data->obj.index[0]]).sc, (data->obj.camera[data->obj.index[0]]).pos.origin), -5.0), (data->obj.camera[data->obj.index[0]]).pos.origin);
		(data->obj.camera[data->obj.index[0]]).x = rotx((data->obj.camera[data->obj.index[0]]).x, -5.0);
		(data->obj.camera[data->obj.index[0]]).y = rotx((data->obj.camera[data->obj.index[0]]).y, -5.0);
	}
	if (key_code == SDL_SCANCODE_LEFT)
	{
		(data->obj.camera[data->obj.index[0]]).sc = add_vec(roty(sub_vec((data->obj.camera[data->obj.index[0]]).sc, (data->obj.camera[data->obj.index[0]]).pos.origin), 5.0), (data->obj.camera[data->obj.index[0]]).pos.origin);
		(data->obj.camera[data->obj.index[0]]).x = roty((data->obj.camera[data->obj.index[0]]).x, 5.0);
		(data->obj.camera[data->obj.index[0]]).y = roty((data->obj.camera[data->obj.index[0]]).y, 5.0);
	}
	if (key_code == SDL_SCANCODE_RIGHT)
	{
		(data->obj.camera[data->obj.index[0]]).sc = add_vec(roty(sub_vec((data->obj.camera[data->obj.index[0]]).sc, (data->obj.camera[data->obj.index[0]]).pos.origin), -5.0), (data->obj.camera[data->obj.index[0]]).pos.origin);
		(data->obj.camera[data->obj.index[0]]).x = roty((data->obj.camera[data->obj.index[0]]).x, -5.0);
		(data->obj.camera[data->obj.index[0]]).y = roty((data->obj.camera[data->obj.index[0]]).y, -5.0);
	}
}

void    call_rot_cam(t_data *data)
{
    if (key_old(*data, SDL_SCANCODE_UP))
		rot_cam_input(data, SDL_SCANCODE_UP);
	if (key_old(*data, SDL_SCANCODE_DOWN))
		rot_cam_input(data, SDL_SCANCODE_DOWN);
	if (key_old(*data, SDL_SCANCODE_LEFT))
		rot_cam_input(data, SDL_SCANCODE_LEFT);
	if (key_old(*data, SDL_SCANCODE_RIGHT))
		rot_cam_input(data, SDL_SCANCODE_RIGHT);
	printf("cam %d\n", data->obj.index[0]);//debug
}


void	input_move_cam(t_data *data, t_point tmp)
{
    if (key_old(*data, SDL_SCANCODE_A))
	{
		tmp = roty(tmp, 90);
		data->obj.camera[data->obj.index[2]].pos.origin = add_vec(data->obj.camera[data->obj.index[2]].pos.origin, mult_vec2(tmp, 0.5));
		data->obj.camera[data->obj.index[2]].sc = add_vec(data->obj.camera[data->obj.index[2]].sc, mult_vec2(tmp, 0.5));
		tmp = veccpy(data->obj.camera[data->obj.index[2]].pos.direction);
	}
	if (key_old(*data, SDL_SCANCODE_D))
	{
		tmp = roty(tmp, 90);
		data->obj.camera[data->obj.index[2]].pos.origin = sub_vec(data->obj.camera[data->obj.index[2]].pos.origin, mult_vec2(tmp, 0.5));
		data->obj.camera[data->obj.index[2]].sc = sub_vec(data->obj.camera[data->obj.index[2]].sc, mult_vec2(tmp, 0.5));
		tmp = veccpy(data->obj.camera[data->obj.index[2]].pos.direction);
	}
	if (key_old(*data, SDL_SCANCODE_LSHIFT))
	{
		data->obj.camera[data->obj.index[2]].pos.origin = add_vec(data->obj.camera[data->obj.index[2]].pos.origin, mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
		data->obj.camera[data->obj.index[2]].sc = add_vec(data->obj.camera[data->obj.index[2]].sc, mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
	}
	if (key_old(*data, SDL_SCANCODE_SPACE))
	{
		data->obj.camera[data->obj.index[2]].pos.origin = sub_vec(data->obj.camera[data->obj.index[2]].pos.origin, mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
		data->obj.camera[data->obj.index[2]].sc = sub_vec(data->obj.camera[data->obj.index[2]].sc, mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
	}
}