#include "rt.h"

void	input_id(t_data *data, void **obj, char ctrl)//possibiliter de reduire avec un tmp les lignes
{
	if (key_check(*data, SDL_SCANCODE_KP_4) && !ctrl && (*(t_base **)obj)->effect.id_texture < data->obj.nb_texture - 1)
		(*(t_base **)obj)->effect.id_texture += 1;
	else if (key_check(*data, SDL_SCANCODE_KP_4) && ctrl && (*(t_base **)obj)->effect.id_texture > 0)
		(*(t_base **)obj)->effect.id_texture -= 1;

	//demander a loic comment proteger id_texture car on a pas de nb_id_texture
	if (key_check(*data, SDL_SCANCODE_KP_5) && !ctrl)
		(*(t_base **)obj)->effect.id_normal += 1;
	else if (key_check(*data, SDL_SCANCODE_KP_5) && ctrl)
		(*(t_base **)obj)->effect.id_normal -= 1;

	if (key_check(*data, SDL_SCANCODE_KP_6) && !ctrl)
		(*(t_base **)obj)->effect.id_rotation += 1;
	else if (key_check(*data, SDL_SCANCODE_KP_6) && ctrl)
		(*(t_base **)obj)->effect.id_rotation -= 1;
}

void	input_descartes_obj(t_data *data, void **obj, char ctrl)//possibiliter de reduire avec un tmp les lignes
{
	if (key_old(*data, SDL_SCANCODE_KP_1) && !ctrl && (*(t_base **)obj)->effect.reflection < 255)
		 (*(t_base **)obj)->effect.reflection += 1;
	else if (key_old(*data, SDL_SCANCODE_KP_1) && ctrl && (*(t_base **)obj)->effect.reflection > 0)
		(*(t_base **)obj)->effect.reflection -= 1;
	if (key_old(*data, SDL_SCANCODE_KP_2) && !ctrl && (*(t_base **)obj)->effect.refraction < 255)
		 (*(t_base **)obj)->effect.refraction += 1;
	else if (key_old(*data, SDL_SCANCODE_KP_2) && ctrl && (*(t_base **)obj)->effect.refraction > 0)
		(*(t_base **)obj)->effect.refraction -= 1;
	if (key_old(*data, SDL_SCANCODE_KP_3) && !ctrl && (*(t_base **)obj)->effect.opacity < 255)
		 (*(t_base **)obj)->effect.opacity += 1;
	else if (key_old(*data, SDL_SCANCODE_KP_3) && ctrl && (*(t_base **)obj)->effect.opacity > 0)
		(*(t_base **)obj)->effect.opacity -= 1;
}

void	input_color_obj(t_data *data, void **obj, char ctrl)//possibiliter de reduire avec un tmp les lignes
{
	if (key_old(*data, SDL_SCANCODE_KP_7) && !ctrl && ((*(t_base **)obj)->effect.color & 0xFF0000) >> 16 < 255)
		((char *)&((*(t_base **)obj)->effect.color))[2] += 1;
    if (key_old(*data, SDL_SCANCODE_KP_7) && ctrl && ((*(t_base **)obj)->effect.color & 0xFF0000) >> 16 > 0)
		((char *)&((*(t_base **)obj)->effect.color))[2] -= 1;
	if (key_old(*data, SDL_SCANCODE_KP_8) && !ctrl && ((*(t_base **)obj)->effect.color & 0xFF00) >> 8 < 255)
		((char *)&((*(t_base **)obj)->effect.color))[1] += 1;
	if (key_old(*data, SDL_SCANCODE_KP_8) && ctrl && ((*(t_base **)obj)->effect.color & 0xFF00) >> 8 > 0)
		((char *)&((*(t_base **)obj)->effect.color))[1] -= 1;
	if (key_old(*data, SDL_SCANCODE_KP_9) && !ctrl && ((*(t_base **)obj)->effect.color & 0xFF) < 255)
		((char *)&((*(t_base **)obj)->effect.color))[0] += 1;
	if (key_old(*data, SDL_SCANCODE_KP_9) && ctrl && ((*(t_base **)obj)->effect.color & 0xFF) > 0)
		((char *)&((*(t_base **)obj)->effect.color))[0] -= 1;
}

void	input_move_obj(t_data *data, void **obj)
{
    if (key_old(*data, SDL_SCANCODE_SPACE))
		(*(t_base **)obj)->origin.origin.y -= 0.1;
	if (key_old(*data, SDL_SCANCODE_LSHIFT))
		(*(t_base **)obj)->origin.origin.y += 0.1;
	if (key_old(*data, SDL_SCANCODE_A))
		(*(t_base **)obj)->origin.origin.x -= 0.1;
	if (key_old(*data, SDL_SCANCODE_D))
		(*(t_base **)obj)->origin.origin.x += 0.1;
	if (key_old(*data, SDL_SCANCODE_W))
		(*(t_base **)obj)->origin.origin.z += 0.1;
	if (key_old(*data, SDL_SCANCODE_S))
		(*(t_base **)obj)->origin.origin.z -= 0.1;
}
