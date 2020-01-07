#include "rt.h"

static	t_point	find_pos(t_data *data, int x, int y)
{
	t_point		ret;

	ret = veccpy(data->obj.camera[0].sc);
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].x, x));
	ret = add_vec(ret, mult_vec2(data->obj.camera[data->obj.index[0]].y, y));
	ret = sub_vec(ret, data->obj.camera[data->obj.index[0]].pos.origin);
	return (ret);
}

static void	rot_cam_input(t_data *data, int key_code)
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

static void	create_light(t_data *data, t_light *new, int x, int y)
{
	new->color = 0xFF00FF;
	new->distance = 5;
	new->intensity = 1;
	new->origin = find_pos(data, x, y);
}


static void	light_cursor(t_data *data)
{
	static char curr = 0;
	if (data->input.button & SDL_BUTTON_LEFT)
	{
		if (curr == 0)
		{
			data->obj.nb_light += 1;
			create_light(data, &data->obj.light[data->obj.nb_light], data->input.x, data->input.y);
			curr = 1;
		}
		else
		{
			data->obj.light[data->obj.nb_light].origin = find_pos(data,data->input.x, data->input.y);
		}
		
	}
	else if (curr == 1)
	{
		data->obj.nb_light -= 1;
		curr = 0;
	}
}

void		move_light(t_data *data)
{
	if (key_old(*data, SDL_SCANCODE_W))
		data->obj.light[data->obj.index[2]].origin.y -= 0.1;
	if (key_old(*data, SDL_SCANCODE_S))
		data->obj.light[data->obj.index[2]].origin.y += 0.1;
	if (key_old(*data, SDL_SCANCODE_A))
		data->obj.light[data->obj.index[2]].origin.x -= 0.1;
	if (key_old(*data, SDL_SCANCODE_D))
		data->obj.light[data->obj.index[2]].origin.x += 0.1;
	if (key_old(*data, SDL_SCANCODE_Q))
		data->obj.light[data->obj.index[2]].origin.z += 0.1;
	if (key_old(*data, SDL_SCANCODE_E))
		data->obj.light[data->obj.index[2]].origin.z -= 0.1;
	printf("light %d\n", data->obj.index[2]);
}

void		move_obj(t_data *data)
{
	if (key_old(*data, SDL_SCANCODE_W))
		((t_base *)(data->obj.item[data->obj.index[1]]))->origin.origin.y -= 0.1;
	if (key_old(*data, SDL_SCANCODE_S))
		((t_base *)(data->obj.item[data->obj.index[1]]))->origin.origin.y += 0.1;
	if (key_old(*data, SDL_SCANCODE_A))
		((t_base *)(data->obj.item[data->obj.index[1]]))->origin.origin.x -= 0.1;
	if (key_old(*data, SDL_SCANCODE_D))
		((t_base *)(data->obj.item[data->obj.index[1]]))->origin.origin.x += 0.1;
	if (key_old(*data, SDL_SCANCODE_Q))
		((t_base *)(data->obj.item[data->obj.index[1]]))->origin.origin.z += 0.1;
	if (key_old(*data, SDL_SCANCODE_E))
		((t_base *)(data->obj.item[data->obj.index[1]]))->origin.origin.z -= 0.1;
	printf("obj %d\n", data->obj.index[1]);
}

void		move_cam(t_data *data)
{
	t_point tmp;

	tmp = veccpy(data->obj.camera[data->obj.index[2]].pos.direction);
	if (key_old(*data, SDL_SCANCODE_W))//up
	{
		data->obj.camera[data->obj.index[2]].pos.origin = add_vec(data->obj.camera[data->obj.index[2]].pos.origin, mult_vec2(tmp, 0.5));
		data->obj.camera[data->obj.index[2]].sc = add_vec(data->obj.camera[data->obj.index[2]].sc, mult_vec2(tmp, 0.5));
	}
	if (key_old(*data, SDL_SCANCODE_S))
	{
		data->obj.camera[data->obj.index[2]].pos.origin = sub_vec(data->obj.camera[data->obj.index[2]].pos.origin, mult_vec2(tmp, 0.5));
		data->obj.camera[data->obj.index[2]].sc = sub_vec(data->obj.camera[data->obj.index[2]].sc, mult_vec2(tmp, 0.5));
	}
	if (key_old(*data, SDL_SCANCODE_A))//left
	{
		tmp = roty(tmp, 90);
		data->obj.camera[data->obj.index[2]].pos.origin = add_vec(data->obj.camera[data->obj.index[2]].pos.origin, mult_vec2(tmp, 0.5));
		data->obj.camera[data->obj.index[2]].sc = add_vec(data->obj.camera[data->obj.index[2]].sc, mult_vec2(tmp, 0.5));
		tmp = veccpy(data->obj.camera[data->obj.index[2]].pos.direction);
	}
	if (key_old(*data, SDL_SCANCODE_D))
	{
		tmp = roty(tmp, -90);
		data->obj.camera[data->obj.index[2]].pos.origin = add_vec(data->obj.camera[data->obj.index[2]].pos.origin, mult_vec2(tmp, 0.5));
		data->obj.camera[data->obj.index[2]].sc = add_vec(data->obj.camera[data->obj.index[2]].sc, mult_vec2(tmp, 0.5));
		tmp = veccpy(data->obj.camera[data->obj.index[2]].pos.direction);
	}
	if (key_old(*data, SDL_SCANCODE_LSHIFT))
	{
		// tmp = rotx(tmp, 90);
		data->obj.camera[data->obj.index[2]].pos.origin = add_vec(data->obj.camera[data->obj.index[2]].pos.origin, mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
		data->obj.camera[data->obj.index[2]].sc = add_vec(data->obj.camera[data->obj.index[2]].sc, mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
		// tmp = veccpy(data->obj.camera[data->obj.index[2]].pos.direction);
	}
	if (key_old(*data, SDL_SCANCODE_SPACE))
	{
		// tmp = rotx(tmp, -90);
		data->obj.camera[data->obj.index[2]].pos.origin = sub_vec(data->obj.camera[data->obj.index[2]].pos.origin, mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
		data->obj.camera[data->obj.index[2]].sc = sub_vec(data->obj.camera[data->obj.index[2]].sc, mult_vec2(normalize(fill_vec(0, 1, 0)), 0.5));
		// tmp = veccpy(data->obj.camera[data->obj.index[2]].pos.direction);
	}

/*============================================================================*/
	if (key_old(*data, SDL_SCANCODE_UP))
		rot_cam_input(data, SDL_SCANCODE_UP);
	if (key_old(*data, SDL_SCANCODE_DOWN))
		rot_cam_input(data, SDL_SCANCODE_DOWN);
	if (key_old(*data, SDL_SCANCODE_LEFT))
		rot_cam_input(data, SDL_SCANCODE_LEFT);
	if (key_old(*data, SDL_SCANCODE_RIGHT))
		rot_cam_input(data, SDL_SCANCODE_RIGHT);
	printf("cam %d\n", data->obj.index[0]);
}

static void	stay_in_case(t_data *data)
{
	data->obj.index[0] > data->obj.nb_camera ? data->obj.index[0] = 0 : 0;
	data->obj.index[0] < 0 ? data->obj.index[0] = data->obj.nb_camera : 0;
	data->obj.index[1] > data->obj.nb_item ? data->obj.index[1] = 0 : 0;
	data->obj.index[1] < 0 ? data->obj.index[1] = data->obj.nb_item - 1 : 0;
	data->obj.index[2] > data->obj.nb_light ? data->obj.index[2] = 0 : 0;
	data->obj.index[2] < 0 ? data->obj.index[2] = data->obj.nb_light : 0;

	data->obj.type_index > 2 ? data->obj.type_index = 0 : 0;
	data->obj.type_index < 0 ? data->obj.type_index = 2 : 0;
}

static void	input_obj(t_data *data)
{
	//Modif Index
	if (key_check(*data, SDL_SCANCODE_KP_PLUS))
		data->obj.index[data->obj.type_index] += 1;
	if (key_check(*data, SDL_SCANCODE_KP_MINUS))
		data->obj.index[data->obj.type_index] -= 1;
	if (key_check(*data, SDL_SCANCODE_6))
		data->obj.type_index += 1;
	if (key_check(*data, SDL_SCANCODE_5))
		data->obj.type_index -= 1;
	// Check > Nb_type
	stay_in_case(data);
	//Modif Obj
	
	//	data->obj.type_index ==> ptr sur function
	data->move[data->obj.type_index] (data);
}

void        input(t_data *data)
{
	if (data->input.key == NULL)
		data->input.key = (unsigned char *)SDL_GetKeyboardState(NULL);
	data->input.button = (int)SDL_GetMouseState(&data->input.x, &data->input.y);
	ft_memcpy(data->input.oldkey, data->input.key, 282);
	SDL_PollEvent(&data->input.ev);
    if (key_check(*data, SDL_SCANCODE_V))
		data->flag.pixel = (data->flag.pixel < 0b11 ? data->flag.pixel + 1 : 0);
	input_obj(data);
	light_cursor(data);
}