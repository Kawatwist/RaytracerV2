/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:14:27 by lomasse           #+#    #+#             */
/*   Updated: 2020/08/01 15:19:59 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# define MV 128
# define NS 64
# define KEY_G SDL_SCANCODE_G

typedef enum		e_item
{
	SPHERE = 0,
	PLAN = 1,
	CONE = 2,
	CYLINDER = 3,
	TRIANGLE = 4,
	DISK = 5,
	OBJ = 6,
	NONE,
}					t_item;

typedef struct		s_ipoint
{
	int				x;
	int				y;
	int				z;
}					t_ipoint;

typedef struct		s_point
{
	float			x;
	float			y;
	float			z;
}					t_point;

typedef struct		s_vec
{
	t_point			origin;
	t_point			direction;
}					t_vec;

typedef struct		s_effect
{
	t_point			movement;
	t_point			axe;
	t_point			distance;
	int				color;
	int				id_texture;
	int				id_normal;
	int				id_rotation;
	float			id_refraction;
	char			type;
	Uint8			reflection;
	Uint8			opacity;
	Uint8			transparancy;
	Uint8			refraction;
	Uint8			texture;
	Uint8			normal;
	Uint8			flag;
	Uint16			isub;
	Uint8			sub : 1;
}					t_effect;

typedef struct		s_base
{
	t_vec			origin;
	t_effect		effect;
}					t_base;

typedef struct		s_light
{
	t_point			origin;
	t_point			direction;
	int				color;
	float			distance;
	float			distancesave;
	float			ang;
	float			intensity;
	float			intensitysave;
	float			variance;
	char			type;
}					t_light;

typedef	struct		s_sphere
{
	t_vec			origin;
	t_effect		effect;
	float			rayon;
}					t_sphere;

typedef	struct		s_plan
{
	t_vec			origin;
	t_effect		effect;
}					t_plan;

typedef	struct		s_cone
{
	t_vec			origin;
	t_effect		effect;
	float			ang;
	float			high;
	int				side;
	char			close;
	t_point			dir_close;
}					t_cone;

typedef	struct		s_cylinder
{
	t_vec			origin;
	t_effect		effect;
	float			rayon;
	float			hauteur;
	char			close;
	t_point			dir_close;
	Uint32			mode : 1;
}					t_cylinder;

typedef	struct		s_triangle
{
	t_vec			p1;
	t_effect		effect;
	t_vec			p2;
	t_vec			p3;
}					t_triangle;

typedef	struct		s_disk
{
	t_vec			origin;
	t_effect		effect;
	float			rayon;
}					t_disk;

typedef	struct		s_obj
{
	t_vec			origin;
	t_effect		effect;
	t_vec			destination;
	t_point			low;
	t_point			high;
	t_point			diff;
	float			size;
	Uint8			face;
	Uint8			id_texture[6];
}					t_obj;

typedef struct		s_generate
{
	t_point			origin;
	int				nb;
	float			rayon_i;
	t_sphere		sphere;
	Uint32			axe : 2;
}					t_generate;

#endif
