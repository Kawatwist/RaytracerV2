#include "rt.h"

static int	find_type(char *type)
{
	type = ft_strchr(type, ':');
	if (type != NULL)
	{
		if (*(type + 1) == 's')
			return (SPHERE);
		else if (*(type + 1) == 'p')
			return (PLAN);
		else if (*(type + 1) == 'c')
			return (*(type + 2) == 'o' ? CONE : CYLINDER);
	}
	return (NONE);
}

static int	create_type(t_data *data, int index, int type)
{
	static	size_t	tab[4] = {sizeof(t_sphere)
			, sizeof(t_plan), sizeof(t_cone), sizeof(t_cylinder)};
	void	*item;

	if ((item = malloc(tab[(int)type])) == NULL)
		return (11);
	ft_bzero(&((t_base *)item)->effect, sizeof(t_effect));
	ft_bzero(item, sizeof(item));
	data->obj.item[index] = item;
	((t_base *)data->obj.item[index])->effect.type = type;
	return (0);
}

static t_point	add_rot(t_point mov, char *str)
{
	if (!ft_strncmp("rotatex : ", str, 10))
		mov.x = ft_atof(str + 10);
	else if (!ft_strncmp("rotatey : ", str, 10))
		mov.y = ft_atof(str + 10);
	else if (!ft_strncmp("rotatez : ", str, 10))
		mov.z = ft_atof(str + 10);
	return (mov);
}

static int	fill_effect(t_effect *effect, char *line)
{
	if (!ft_strncmp("\t\t\tmv : ", line, 8))
		effect->flag += (ft_atoi(line + 8) > 0 ? MV : 0);
	else if (!ft_strncmp("\t\t\trefraction : ", line, 16))
		effect->refraction = ft_atoi(line + 16);
	else if (!ft_strncmp("\t\t\topacity : ", line, 13))
		effect->opacity = ft_atoi(line + 13);
	else if (!ft_strncmp("\t\t\treflexion : ", line, 15))
		effect->reflection = ft_atoi(line + 15);
	else if (!ft_strncmp("\t\t\trot", line, 6))
		effect->movement = add_rot(effect->movement, line + 3);
	else if (!ft_strncmp("\t\t\ttexture", line, 10))
		effect->texture = ft_atoi(line + 12);
	else if (!ft_strncmp("\t\t\tid_texture", line, 13))
		effect->id_texture = ft_atoi(line + 15);
	else if (!ft_strncmp("\t\t[effect]", line, 11))
		return (0);
	else
		return (11);
	return (0);
}

int         parsing_obj(t_data *data, char **old, char *type)
{
    static unsigned int  index = 0;
	char		*line;
	char		val;

	line = NULL;
	val = find_type(type);
	if (index >= data->obj.nb_item)
		return (11);
	if (val == NONE || create_type(data, index, val))
		return (11);
	while (get_next_line(data->parse.fd, &line) && !ft_strncmp("\t", line, 1)) // Free Line
	{
		if (!ft_strncmp("\torigin :", line, 8))
			((t_base *)data->obj.item[index])->origin.origin = get_point(line);
		else if (!ft_strncmp("\tdirection :", line, 11))
			((t_base *)data->obj.item[index])->origin.direction = get_point(line);
		else if (!ft_strncmp("\tcolor :", line, 8))
			((t_base *)data->obj.item[index])->effect.color = ((ft_atoi_base(line + 11, 16) & 0xFFFFFF) + (255 << 24));
		else if (!ft_strncmp("\trayon : ", line, 8) && (((t_base *)data->obj.item[index])->effect.type == SPHERE || ((t_base *)data->obj.item[index])->effect.type == CYLINDER))
			((t_sphere *)data->obj.item[index])->rayon = ft_atof(line + 8);
		else if (!ft_strncmp("\tangle : ", line, 8) && (((t_base *)data->obj.item[index])->effect.type == CONE))
			((t_cone *)data->obj.item[index])->ang = ft_atof(line + 8);
		else if (!ft_strncmp("\t\t", line, 2))
		{
			if (fill_effect(&(((t_base *)data->obj.item[index])->effect), line))
				return (11);
		}
		else
			return (11);
	}
	*old = line;
	index++;
    return (0);
}