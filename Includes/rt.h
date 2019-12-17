#ifndef RT_H
# define RT_H

# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "tga_reader.h"
# include "object.h"
# include "subrt.h"

typedef struct	s_flag
{
	int			pixel : 2;
	int			auto : 1;
	int			perspective : 1;
	int			bounce : 1;
}				t_flag;


typedef struct	s_data
{
	t_window	window;
	t_input		input;
	t_object	obj;
	t_tga		*texture;
	t_flag		flag;
	t_vec		ray;
}				t_data;

//				EFFECT
//				EFFECT

//				OBJECT
void			*check_object(t_data *data, t_vec ray, float *dist);
//				OBJECT

//				RAY
int				loop(t_data data);
//				RAY

//				PARSING
int				parsing(t_data *data, int nb, char *arg[]);
//				PARSING

//				INIT
int				initialize(t_data *data);
//				INIT

int				stop_main_execute(char *error, t_win *wn, int error_value);
void			stop_execute(char *error, t_win *wn);
int				main(int argc, char *argv[]);

#endif