#include "rt.h"

static void	*create_sphere()
{
	t_sphere *s;

	s = malloc(sizeof(t_sphere));
	ft_bzero(s, sizeof(t_sphere));
	s->origin.origin = fill_vec(0, 0, 3);
	s->rayon = 0.5;
	s->effect.color = 0xFF00FF;
	s->effect.type = SPHERE;
	s->effect.reflection = 0;
	return (s);
}

int		parsing(t_data *data, int nb, char *arg[])
{
	(void)data;
	(void)nb;
	(void)arg;
	data->obj.item = malloc(sizeof(void *) * 2);
	data->obj.item[1] = NULL;
	data->obj.item[0] = create_sphere();
	return (0);
}