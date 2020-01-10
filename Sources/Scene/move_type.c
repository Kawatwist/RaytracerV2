#include "rt.h"
//4 function dans le fichier

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
	printf("light %d\n", data->obj.index[2]);
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
	if (key_old(*data, KEY_O) && !ctrl && (*(t_base **)obj)->effect.type == SPHERE && (*(t_base **)obj)->effect.type == CYLINDER)// + autre obj avec rayon
		(*(t_sphere **)obj)->rayon < 100.0 ? (*(t_sphere **)obj)->rayon += 0.1 : 0.0;
	else if (key_old(*data, KEY_O))
		(*(t_sphere **)obj)->rayon > 0.1 ? (*(t_sphere **)obj)->rayon -= 0.1 : 0.0;

	/*reflexion / opaciter / refraction*/
	input_descartes_obj(data, obj, ctrl);

	/*id*/
	input_id(data, obj, ctrl);

	/*texture*///pas test
	if (key_old(*data, SDL_SCANCODE_KP_0) && !ctrl && (*(t_base **)obj)->effect.texture < 255)
		(*(t_base **)obj)->effect.texture += 1;
	else if (key_old(*data, SDL_SCANCODE_KP_0) && ctrl && (*(t_base **)obj)->effect.texture > 0)
		(*(t_base **)obj)->effect.texture -= 1;

	/*normal*///pas test
	if (key_old(*data, SDL_SCANCODE_1) && !ctrl && (*(t_base **)obj)->effect.normal < 255)
		(*(t_base **)obj)->effect.normal += 1;
	else if (key_old(*data, SDL_SCANCODE_1) && ctrl && (*(t_base **)obj)->effect.normal > 0)
		(*(t_base **)obj)->effect.normal -= 1;

	/*mouvement*/
	/*axe*/
	/*flag*/
	
	ctrl = 0;
	printf("\nObject Actuel + Texture : %d\t\t%d\n", data->obj.index[1], (*(t_base **)obj)->effect.id_texture);
	printf("Reflexion || Refraction || Opacity\n[%d]\t[%d]\t[%d]\n", ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.reflection, ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.refraction, ((t_base *)(data->obj.item[data->obj.index[1]]))->effect.opacity);
	printf("Color : [%d]\t[%d]\t[%d]\n", ((*(t_base **)obj)->effect.color & 0xFF0000) >> 16, (((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color & 0xFF00) >> 8, (((t_base *)(data->obj.item[data->obj.index[1]]))->effect.color & 0xFF));
}

void		move_cam(t_data *data, void **cam)
{
	(void)cam;//faire reduire les lignes avec le void **cam
	t_point tmp;

	tmp = veccpy(data->obj.camera[data->obj.index[2]].pos.direction);
	if (key_old(*data, SDL_SCANCODE_W))
	{
		data->obj.camera[data->obj.index[2]].pos.origin = add_vec(data->obj.camera[data->obj.index[2]].pos.origin, mult_vec2(tmp, 0.5));
		data->obj.camera[data->obj.index[2]].sc = add_vec(data->obj.camera[data->obj.index[2]].sc, mult_vec2(tmp, 0.5));
	}
	if (key_old(*data, SDL_SCANCODE_S))
	{
		data->obj.camera[data->obj.index[2]].pos.origin = sub_vec(data->obj.camera[data->obj.index[2]].pos.origin, mult_vec2(tmp, 0.5));
		data->obj.camera[data->obj.index[2]].sc = sub_vec(data->obj.camera[data->obj.index[2]].sc, mult_vec2(tmp, 0.5));
	}
	input_move_cam(data, tmp);
    call_rot_cam(data);
}
