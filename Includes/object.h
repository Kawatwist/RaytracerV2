#ifndef OBJECT_H
# define OBJECT_H

# define MV 0b10000000
#define  KEY_O SDL_SCANCODE_O

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
	t_point			movement;// 3 input
	t_point			axe;// 3 input
	int				color;//789
	int				id_texture;//4
	int				id_normal;//5
	int				id_rotation;//6
	char			type;
	unsigned char	reflection;//1
	unsigned char	opacity;//2
	unsigned char	refraction;//3
	unsigned char	texture;//0
	unsigned char	normal;// 1 no num pad
	unsigned char	flag;		// mov + axe // set_bit
}				t_effect;

typedef struct  s_base
{
    t_vec       origin;
    t_effect	effect;
}               t_base;

typedef struct	s_light
{
	t_point		origin;
	int			color;//789
	float		distance;//1
	float		intensity;//2
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