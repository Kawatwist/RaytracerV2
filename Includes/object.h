/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <lomasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:14:27 by lomasse           #+#    #+#             */
/*   Updated: 2020/03/08 06:12:26 by lomasse          ###   ########.fr       */
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
	NONE,
}					t_item;

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
	int				color;
	int				id_texture;
	int				id_normal;
	int				id_rotation;
	float			id_refraction;
	char			type;
	unsigned char	reflection;
	unsigned char	opacity;
	unsigned char	transparancy;
	unsigned char	refraction;
	unsigned char	texture;
	unsigned char	normal;
	unsigned char	flag;
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
	float			ang;
	float			intensity;
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
	char			side;
}					t_cone;

typedef	struct		s_cylinder
{
	t_vec			origin;
	t_effect		effect;
	float			rayon;
	float			hauteur;
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

#endif
