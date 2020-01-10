#ifndef RT_H
# define RT_H

# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "tga_reader.h"
# include "object.h"
# include "subrt.h"

# define TRUE 1

typedef struct	s_data t_data;

typedef struct		s_flag
{
	unsigned int	pixel : 2;
	unsigned int	perspective : 1;
	unsigned int	bounce : 1;
}					t_flag;


struct	s_data
{
	t_window	window;
	t_input		input;
	t_object	obj;
	t_scene		parse;
	t_flag		flag;
	t_vec		ray;
	t_tga		**texture;
	float		(*dist[4]) (void *obj, t_vec ray);
	t_point		(*txt[4]) (t_data *data, void *obj, t_vec ray);
	void		(*move[3]) (t_data *data, void **obj);
	int			percent;
};

//				EFFECT
t_point			find_refraction(void *obj, t_vec ray);
t_point			find_reflexion(void *obj, t_vec ray, t_data data);
t_point			find_normal(void *object, t_vec collide);
//				EFFECT

//				LIGHT
unsigned int	ray_to_light(t_data *data, t_vec ray, int base);
int				parsing_light(t_data *data, char **old, char *line);
void        	setup_light(t_data *data);
//				LIGHT

//				OBJECT
int				find_size(t_data data, void *obj);
t_point			find_normal_texture(t_data data, void *obj, t_vec collide, t_point normal);

t_point			texture_plan(t_data *data, void *obj, t_vec ray);
t_point			texture_sphere(t_data *data, void *obj, t_vec ray);
t_point			texture_cylinder(t_data *data, void *obj, t_vec ray);

float			cone(void *coo, t_vec ray);
float			cylinder(void *cylinder, t_vec ray);
float			plane(void *plane, t_vec ray);
float			sphere(void *sphere, t_vec ray);

void			*check_object(t_data *data, t_vec ray, float *dist);
//				OBJECT

//				RAY
int				start_ray(t_data *data);
unsigned int	send_ray(t_data *data, t_vec ray, int bounce);
unsigned int	find_color(t_data *data, void *obj, t_vec ray);
unsigned int	set_color(unsigned int base, unsigned int new, float percent);
char			key_old(t_data data, int mask);
char			key_check(t_data data, int mask);
void			input(t_data *data);
int				loop(t_data data);
//				RAY

//				PARSING
t_point			get_point(char *str);
int				parsing_files(t_data *data, char *line);
int         	parsing_obj(t_data *data, char **line, char *type);
int				parsing_camera(t_data *data, char **line);
int				parsing_head(t_data *data, char **line);
int				parsing(t_data *data, int nb, char *arg[]);
//				PARSING

//				INIT
int         	initialize_cam(t_data *data);
int				initialize_sdl(t_data *data);
int				initialize(t_data *data);
//				INIT

//				TOOL

t_point			rotx(t_point origin, float ang);
t_point			roty(t_point origin, float ang);
t_point			rotz(t_point origin, float ang);

float			square(float f);
float			ang(float value);
float			rad(float value);

t_point			set_neworigin_neg(t_vec ray, float distance);
t_point			set_neworigin_op(t_vec ray, float distance);
t_point			set_neworigin(t_vec ray, float distance);

t_point			veccpy(t_point pnt);
t_vec			create_vec(t_point origin, t_point direction);
t_point			fill_vec(float x, float y, float z);
t_point			add_vec(t_point v1, t_point v2);
t_point			sub_vec2(t_point v1, float sub);
t_point			sub_vec(t_point v1, t_point v2);
t_point			mult_vec2(t_point v1, float mult);
t_point			normalize(t_point v1);

Uint32			set_bit(Uint32 var, Uint32 mask);
float			get_dot_abs(t_point v1, t_point v2);
float			get_angle_vec(t_point v1, t_point v2);
float			square(float f);
t_point			neg_norm(t_point v1);
t_point			sqrt_vec(t_point v1);
t_point			mult_vec(t_point v1, t_point v2);
t_point			div_vec(t_point v1, t_point v2);
t_point			div_vec2(t_point v1, float div);

t_point			cross_vec(t_point v1, t_point v2);
float			cross_product(double **mat, t_point v1, int row);
float			dot_product(t_point v1, t_point v2);
float			length(t_point v1);
//				TOOL

void			move_cam(t_data *data, void **obj);
void			input_move_cam(t_data *data, t_point tmp);
void		    call_rot_cam(t_data *data);


void			move_obj(t_data *data, void **obj);
void			input_move_obj(t_data *data, void **obj);
void			input_color_obj(t_data *data, void **obj, char ctrl);
void			input_descartes_obj(t_data *data, void **obj, char ctrl);
void			input_id(t_data *data, void **obj, char ctrl);


void			move_light(t_data *data, void **obj);
void			input_move_light(t_data *data, void **light);
void			input_color_light(t_data *data, void **light, char ctrl);
void			input_distance_light(t_data *data, void **light, char ctrl);
void			input_intensity_light(t_data *data, void **light, char ctrl);




void			light_cursor(t_data *data);

/*input_obj*/


int				stop_main_execute(char *error, t_data *data, int error_value);
void			stop_execute(char *error, t_data *data);
int				main(int argc, char *argv[]);

#endif