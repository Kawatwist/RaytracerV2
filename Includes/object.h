#ifndef OBJECT_H
# define OBJECT_H

# define MV 0b10000000

typedef enum	e_item
{
	SPHERE = 0,
	PLAN = 1,
	CONE = 2,
	CYLINDER = 3,
	NONE,
}				t_item;

typedef struct	s_point
{
	float		x;
	float		y;
	float		z;
}				t_point;

typedef struct	s_vec
{
	t_point		origin;
	t_point		direction;
}				t_vec;

typedef struct	s_effect
{
	t_point			movement;
	t_point			axe;
	int				color;//3 input
	int				id_texture;
	int				id_normal;
	int				id_rotation;
	char			type;
	unsigned char	reflection;//1 input
	unsigned char	opacity;//1 input
	unsigned char	refraction;//1 input
	unsigned char	texture;
	unsigned char	normal;
	unsigned char	flag;		// mov + axe
}				t_effect;

typedef struct  s_base
{
    t_vec       origin;
    t_effect	effect;
}               t_base;

typedef struct	s_light
{
	t_point		origin;
	int			color;
	float		distance;
	float		intensity;
}				t_light;

typedef	struct	s_sphere
{
	t_vec		origin;
	t_effect	effect;
	float		rayon;
}				t_sphere;

typedef	struct	s_plan
{
	t_vec		origin;
	t_effect	effect;
}				t_plan;

typedef	struct	s_cone
{
	t_vec		origin;
	t_effect	effect;
	float		ang;
}				t_cone;

typedef	struct	s_cylinder
{
	t_vec		origin;
	t_effect	effect;
	float		rayon;
}				t_cylinder;

#endif