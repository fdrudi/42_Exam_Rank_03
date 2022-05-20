#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct s_paint
{
	FILE	*fp;
	char	**map;
	int		w_x;
	int		w_y;
	char	c[2];
	char	tmp;
	float	c_x;
	float	c_y;
	float	rad;
	char	c2[2];
	char	c3[2];
}				t_paint;

void	ft_circle(t_paint *p)
{
	int	x;
	int	y;
	int	i;
	int	j;
	float tmp;

	x = p->c_x - p->rad;
	y = p->c_y - p->rad;
	i = -1;
	while (++i <= p->rad * 2)
	{
		if ((y + i) < p->w_y && (y + i) >= 0)
		{
			j = -1;
			while (++j <= p->rad * 2)
			{
				if ((x + j) < p->w_x && (x + j) >= 0)
				{
					tmp = sqrt(powf(i - p->rad, 2) + powf(j - p->rad, 2));
					if (tmp <= p->rad)
					{
						if (p->c2[0] == 'C')
							p->map[(int) y + i][(int) x + j] = p->c3[0];
						else
							if (p->rad - tmp < 1)
								p->map[(int) y + i][(int) x + j] = p->c3[0];
					}
				}
			}
		}
	}
}

typedef struct s_print
{
	float	w;
	float	h;
	float	x;
	float	y;
	char	p[2];
	char	r[2];
}				t_print;

typedef struct s_paint2
{
	FILE	*fp;
	char	**map;
	int		w;
	int		h;
	char	b[2];
	t_print	p;
}				t_paint2;

void	ft_rectangle(t_paint2 *p)
{
	int	y;
	int	x;

	y = -1;
	while(++y <= p->p.h)
	{
		if (p->p.y + y < p->h && p->p.y + y >= 0)
		{
			x = -1;
			while (++x <= p->p.w)
			{
				if (p->p.x + x < p->w && p->p.x + x >= 0)
				{
					if (p->p.r[0] == 'R')
						p->map[(int) p->p.y + y][(int) p->p.x + x] = p->p.p[0];
					else
						if (y == 0 || y == p->p.y || x == 0 || x == p->p.x)
							p->map[(int) p->p.y + y][(int) p->p.x + x] = p->p.p[0];
				}
			}
		}
	}
}
