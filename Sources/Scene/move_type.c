#include "rt.h"
//4 function dans le fichier

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

void		move_light(t_data *data)
{
	if (key_old(*data, SDL_SCANCODE_SPACE))
		data->obj.light[data->obj.index[2]].origin.y -= 0.1;
	if (key_old(*data, SDL_SCANCODE_LSHIFT))
		data->obj.light[data->obj.index[2]].origin.y += 0.1;
	if (key_old(*data, SDL_SCANCODE_A))
		data->obj.light[data->obj.index[2]].origin.x -= 0.1;
	if (key_old(*data, SDL_SCANCODE_D))
		data->obj.light[data->obj.index[2]].origin.x += 0.1;
	if (key_old(*data, SDL_SCANCODE_W))
		data->obj.light[data->obj.index[2]].origin.z += 0.1;
	if (key_old(*data, SDL_SCANCODE_S))
		data->obj.light[data->obj.index[2]].origin.z -= 0.1;
	if (key_old(*data, SDL_SCANCODE_2))
		data->obj.light[data->obj.index[2]].distance += 0.1;
	if (key_old(*data, SDL_SCANCODE_1))
		data->obj.light[data->obj.index[2]].distance -= 0.1;
/*a voir plus tard avec Loic*/
	if (key_old(*data, SDL_SCANCODE_KP_7))
		data->obj.light[data->obj.index[2]].color += (0xFF & 2);
	if (key_old(*data, SDL_SCANCODE_KP_4))
		data->obj.light[data->obj.index[2]].color -= (0xFF & 2);
	// if (key_old(*data, SDL_SCANCODE_O))//pas utilise encore
	// 	data->obj.light[data->obj.index[2]].intensity -= 0.1;
	
	printf("light %d\n", data->obj.index[2]);
}

void		move_obj(t_data *data)
{
	static char ctrl = 0;
    t_point     tmp;

	if (key_old(*data, SDL_SCANCODE_LCTRL))
		ctrl = 1;
	/*moves*/
    tmp = veccpy(((t_base *)(data->obj.item[data->obj.index[1]]))->origin.origin);
	if (key_old(*data, SDL_SCANCODE_SPACE))
		tmp.y -= 0.1;
	if (key_old(*data, SDL_SCANCODE_LSHIFT))
		tmp.y += 0.1;
	if (key_old(*data, SDL_SCANCODE_A))
		tmp.x -= 0.1;
	if (key_old(*data, SDL_SCANCODE_D))
		tmp.x += 0.1;
	if (key_old(*data, SDL_SCANCODE_W))
		tmp.z += 0.1;
	if (key_old(*data, SDL_SCANCODE_S))
		tmp.z -= 0.1;
    ((t_base *)(data->obj.item[data->obj.index[1]]))->origin.origin = veccpy(tmp);
	/*color*/
	/*input use : 7,8,9 du num pad*/
	if (key_old(*data, SDL_SCANCODE_KP_7) && ctrl == 0)
		((char *)&((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color)[2] += 1;
	if (key_old(*data, SDL_SCANCODE_KP_8) && ctrl == 0)
		((char *)&((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color)[1] += 1;
	if (key_old(*data, SDL_SCANCODE_KP_9) && ctrl == 0)
		((char *)&((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color)[0] += 1;
    if (key_old(*data, SDL_SCANCODE_KP_7) && ctrl == 1 && (((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color & 0xFF0000) >> 16 > 0)
		((char *)&((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color)[2] -= 1;
	if (key_old(*data, SDL_SCANCODE_KP_8) && ctrl == 1)
		((char *)&((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color)[1] -= 1;
	if (key_old(*data, SDL_SCANCODE_KP_9) && ctrl == 1)
		((char *)&((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color)[0] -= 1;
	/*rayon sphere*/
	if (key_old(*data, SDL_SCANCODE_O) && ctrl == 0)
		((t_sphere *)(data->obj.item[data->obj.index[1]]))->rayon < 100.0 ? ((t_sphere *)(data->obj.item[data->obj.index[1]]))->rayon += 0.1 : 0.0;
	else if (key_old(*data, SDL_SCANCODE_O))
		((t_sphere *)(data->obj.item[data->obj.index[1]]))->rayon > 0.1 ? ((t_sphere *)(data->obj.item[data->obj.index[1]]))->rayon -= 0.1 : 0.0;
	/*reflexion / opaciter / reraction*/
	if (key_old(*data, SDL_SCANCODE_KP_1) && ctrl == 0)
		((t_base *)(data->obj.item[data->obj.index[1]]))->effect.reflection < 255 ? ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.reflection += 1 : 0;
	else if (key_old(*data, SDL_SCANCODE_KP_1))
		((t_base *)(data->obj.item[data->obj.index[1]]))->effect.reflection > 0 ? ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.reflection -= 1 : 0;
	if (key_old(*data, SDL_SCANCODE_KP_2) && ctrl == 0)
		((t_base *)(data->obj.item[data->obj.index[1]]))->effect.refraction < 255 ? ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.refraction += 1 : 0;
	else if (key_old(*data, SDL_SCANCODE_KP_2))
		((t_base *)(data->obj.item[data->obj.index[1]]))->effect.refraction > 0 ? ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.refraction -= 1 : 0;
	if (key_old(*data, SDL_SCANCODE_KP_3) && ctrl == 0)
		((t_base *)(data->obj.item[data->obj.index[1]]))->effect.opacity < 255 ? ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.opacity += 1 : 0;
	else if (key_old(*data, SDL_SCANCODE_KP_3))
		((t_base *)(data->obj.item[data->obj.index[1]]))->effect.opacity > 0 ? ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.opacity -= 1 : 0;
	/*other*/
	if (key_old(*data, SDL_SCANCODE_KP_7))
		((t_base *)(data->obj.item[data->obj.index[1]]))->effect.id_texture < 255 ? ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.id_texture += 1 : 0;
	ctrl = 0;
	printf("\nObject Actuel : %d\n", data->obj.index[1]);
	printf("Reflexion || Refraction || Opacity\n[%d]\t[%d]\t[%d]\n", ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.reflection, ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.refraction, ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.opacity);
	printf("Color : [%d]\t[%d]\t[%d]\n", (((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color & 0xFF0000) >> 16, (((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color & 0xFF00) >> 8, (((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color & 0xFF));
}

static void    call_rot_cam(t_data *data)
{
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

/*============================================================================*/
    call_rot_cam(data);
}
