#include "rt.h"
#include "thread.h"

void generate_perlin(t_data *data)
{
	int i;
	int j;
	t_point p;

	i = -1;
	srand(time(NULL));
	while(++i < GRADIENT)
	{
		j = -1;
		while(++j < GRADIENT)
		{
			p.x = rand();
			p.y = rand();
			p.z = 0;
			p = normalize(p);
			data->perlin[i * GRADIENT + j] = p;
		}
	}
}

static float lerp(float a, float b, float w)
{
    return (((1.0 - w)) * a + (w * b));
}

static float dotGradient(t_point perlin[GRADIENT * GRADIENT], t_grad g)
{
    float dx;
    float dy;

    dx = g.x - (float)g.ix;
    dy = g.y - (float)g.iy;
    g.iy = g.iy % GRADIENT;
    g.ix = g.ix % GRADIENT;
    return (dx * perlin[g.iy * GRADIENT + g.ix].x +
            dy * perlin[g.iy * GRADIENT + g.ix].y);
}

static void init_perlin(t_point uv, t_perl *p)
{
    p->x0 = (int)uv.x;
    p->x1 = p->x0 + 1;
    p->y0 = (int)uv.y;
    p->y1 = p->y0 + 1;
    p->sx = uv.x - (float)p->x0;
    p->sy = uv.y - (float)p->y0;
}

static void init_grad(t_point uv, t_perl *p, t_grad *g)
{
    g->ix = p->x0;
    g->iy = p->y0;
    g->x = uv.x;
    g->y = uv.y;
}

float   get_perlin(t_point perlin[GRADIENT * GRADIENT], t_point uv)
{
    t_perl p;
    t_grad g;

    if (uv.x < 0)
        uv.x = -uv.x;
    if (uv.y < 0)
        uv.y = -uv.y;
    init_perlin(uv, &p);
    init_grad(uv, &p, &g);
    p.n0 = dotGradient(perlin, g);
    g.ix = p.x1;
    p.n1 = dotGradient(perlin, g);
    p.ix0 = lerp(p.n0, p.n1, p.sx);
    g.iy = p.y1;
    p.n1 = dotGradient(perlin, g);
    g.ix = p.x0;
    p.n0 = dotGradient(perlin, g);
    p.ix1 = lerp(p.n0, p.n1, p.sx);
    p.value = lerp (p.ix0, p.ix1, p.sy);
    return (p.value);
}