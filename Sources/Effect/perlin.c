#include "rt.h"

/*
**	Wikipedia Version
*/

# define IYMAX 400
# define IXMAX 400

float lerp(float a0, float a1, float w)
{
    return ((1.0 - w) * a0 + w * a1);
}

/*
**	Extern float Gradient Removed
*/

float dotGridGradient(int ix, int iy, float x, float y)
{
	float Gradient[IYMAX][IXMAX][2];
    float dx = x - (float)ix;
    float dy = y - (float)iy;
    return (dx * Gradient[iy][ix][0] + dy * Gradient[iy][ix][1]);
}

float perlin(float x, float y)
{
    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;

    float n0, n1, ix0, ix1, value;

    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = lerp(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = lerp(n0, n1, sx);

    value = lerp(ix0, ix1, sy);
    return value;
}


void		perlin_noise(t_data *data)
{
	for (unsigned int i = 0; i < data->window.x; i++)
		for (unsigned int j =0; j < data->window.y; j++)
			((int *)data->window.pxl)[i + (j * data->window.y)] = ((int)(perlin((float)i, (float)j) * 255) << 24) + ((int)(perlin((float)i, (float)j) * 255) << 16)
			+ ((int)(perlin((float)i, (float)j) * 255) << 8) + ((int)(perlin((float)i, (float)j) * 255));
}


/*
static void	get_random_unit_vector(t_point *p)
{
	p->x = rand();
	p->y = rand();
	p->z = 0;
	*p = normalize(*p);
}

static void	perlin(int *color, float t)
{
	*color = 0xff000000 +
	(((int)(t * 255.0)) << 16) +
	(((int)(t * 255.0)) << 8) +
	(int)(t * 255.0);
}

static void	apply_gradient(t_data *data, t_point* noise_map)
{
	unsigned int i;
	unsigned int j;
	float t[4];
	t_point p;
	i = -1;
	p.z = 0.0;
	i = -1;
	while(++i < data->window.y)
	{
		j = -1;
		while (++j < data->window.x)
		{
			// printf("[%d][%d]\n",i ,j);
			p.x = j % GRADIENT;
			p.y = i % GRADIENT;
			p = normalize(p);

			t[0] = dot_product(noise_map[i * (data->window.x / GRADIENT) + (j / GRADIENT)], p) * (((float)(j % GRADIENT) / GRADIENT));

			p.x = (j + 1) % GRADIENT;
			p.y = i % GRADIENT;
			p = normalize(p);

			t[1] = dot_product(noise_map[i * (data->window.x / GRADIENT) + ((j + 1) / GRADIENT)], p) * (((float)((j + 1) % GRADIENT) / GRADIENT));
			t[2] = (1.0 - ((float)(j % GRADIENT) / GRADIENT)) * t[0] + ((float)(j % GRADIENT) / GRADIENT) * t[1];

			p.x = j % GRADIENT;
			p.y = (i + 1) % GRADIENT;
			p = normalize(p);

			t[0] = dot_product(noise_map[(((i + 1) * data->window.x) / GRADIENT) + (j / GRADIENT)], p) * (((float)(j % GRADIENT) / GRADIENT));

			p.x = (j + 1) % GRADIENT;
			p.y = (i + 1) % GRADIENT;
			p = normalize(p);

			t[1] = dot_product(noise_map[(((i + 1) * data->window.x) / GRADIENT) + ((j + 1)/ GRADIENT)], p) * (((float)((j + 1) % GRADIENT) / GRADIENT));
			t[3] = (1.0 - ((float)(j % GRADIENT) / GRADIENT)) * t[0] + ((float)(j % GRADIENT) / GRADIENT) * t[1];
			t[0] = (1.0 - ((float)(i % GRADIENT) / GRADIENT)) * t[2] + ((float)(i % GRADIENT) / GRADIENT) * t[3];
			perlin(&((int*)(data->window.pxl))[(i * data->window.x) + j], t[0]);
			// printf("%f %f %f\n",t[0], t[2], t[3]);
		}
	}
}

void	perlin_noise(t_data *data)
{
	unsigned int i;
	t_point* noise_map;

	if (!(noise_map = (t_point*)malloc(sizeof(t_point) *
		(((data->window.x / GRADIENT) + 1) * ((data->window.y / GRADIENT) + 1))))) //RELOCATE? CHANGE GradieNT
		exit(0);
	srand(time(NULL));
	i = -1;
	while(++i < (((data->window.x / GRADIENT) + 1) * ((data->window.y / GRADIENT) + 1)))
		get_random_unit_vector(&(noise_map[i]));
	apply_gradient(data, noise_map);
	free(noise_map);
}
*/
