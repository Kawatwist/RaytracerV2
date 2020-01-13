#include "rt.h"

void		move_light(t_data *data, void **light)
{
	static char ctrl = 0;

	if (key_old(*data, SDL_SCANCODE_LCTRL))
		ctrl = 1;
	/*moves*/
	input_move_light(data, light);

	/*distance*/
	input_distance_light(data, light, ctrl);
	
	/*color*/
	input_color_light(data, light, ctrl);
	
	/*intensity*/
	input_intensity_light(data, light, ctrl);
	
	ctrl = 0;	
	printf("light %d\n", data->obj.index[2]);//debug
	printf("Color : [%d]\t[%d]\t[%d]\n", ((*(t_light **)light)->color & 0xFF0000) >> 16, ((*(t_light **)light)->color & 0xFF00) >> 8, ((*(t_light **)light)->color & 0xFF));
}

void		move_obj(t_data *data, void **obj)
{
	static char ctrl = 0;

	if (key_old(*data, SDL_SCANCODE_LCTRL))
		ctrl = 1;
	/*moves*/
	input_move_obj(data, obj);

	/*color*/
	input_color_obj(data, obj, ctrl);
	
	/*rayon*/
	if (key_old(*data, KEY_O) && !ctrl)// + autre obj avec rayon
		(*(t_sphere **)obj)->rayon < 100.0
		? (*(t_sphere **)obj)->rayon += 0.1 : 0.0;
	else if (key_old(*data, KEY_O) && ctrl)
		(*(t_sphere **)obj)->rayon > 0.1
		? (*(t_sphere **)obj)->rayon -= 0.1 : 0.0;

	/*reflexion / opaciter / refraction*/
	input_descartes_obj(data, obj, ctrl);

	/*id*/
	input_id(data, obj, ctrl);

	/*texture*///pas test
	if (key_old(*data, SDL_SCANCODE_KP_0) && !ctrl &&
	(*(t_base **)obj)->effect.texture < 255)
		(*(t_base **)obj)->effect.texture += 1;
	else if (key_old(*data, SDL_SCANCODE_KP_0) && ctrl &&
	(*(t_base **)obj)->effect.texture > 0)
		(*(t_base **)obj)->effect.texture -= 1;

	/*normal*///pas test
	if (key_old(*data, SDL_SCANCODE_1) && !ctrl &&
	(*(t_base **)obj)->effect.normal < 255)
		(*(t_base **)obj)->effect.normal += 1;
	else if (key_old(*data, SDL_SCANCODE_1) && ctrl &&
	(*(t_base **)obj)->effect.normal > 0)
		(*(t_base **)obj)->effect.normal -= 1;

	/*mouvement*/
	/*axe*/
	/*flag*/
	
	ctrl = 0;
	printf("\nObject Actuel + Texture : %d\t\t%d\n", data->obj.index[1], (*(t_base **)obj)->effect.id_texture);
	printf("Reflexion => [%d] || Refraction => [%d] || Opacity => [%d] \n", ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.reflection, ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.refraction, ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.opacity);
	printf("Color : [%d]\t[%d]\t[%d]\n", ((*(t_base **)obj)->effect.color & 0xFF0000) >> 16, (((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color & 0xFF00) >> 8, (((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color & 0xFF));
}

void		move_cam(t_data *data, void **cam)
{
	t_point tmp;

	tmp = veccpy(data->obj.camera[data->obj.index[0]].pos.direction);
	if (key_old(*data, SDL_SCANCODE_W))
	{
		(*(t_camera **)cam)->pos.origin =
		add_vec((*(t_camera **)cam)->pos.origin, mult_vec2(tmp, 0.5));
		(*(t_camera **)cam)->sc =
		add_vec((*(t_camera **)cam)->sc, mult_vec2(tmp, 0.5));
	}
	if (key_old(*data, SDL_SCANCODE_S))
	{
		(*(t_camera **)cam)->pos.origin =
		sub_vec((*(t_camera **)cam)->pos.origin, mult_vec2(tmp, 0.5));
		(*(t_camera **)cam)->sc =
		sub_vec((*(t_camera **)cam)->sc, mult_vec2(tmp, 0.5));
	}
    if (key_old(*data, SDL_SCANCODE_A))
	{
		tmp = roty(tmp, 90);
		(*(t_camera **)cam)->pos.origin =
		add_vec((*(t_camera **)cam)->pos.origin, mult_vec2(tmp, 0.5));
		(*(t_camera **)cam)->sc =
		add_vec((*(t_camera **)cam)->sc, mult_vec2(tmp, 0.5));
		tmp = veccpy(data->obj.camera[data->obj.index[2]].pos.direction);
	}
	input_move_cam(data, tmp, cam);
    call_rot_cam(data);
}
