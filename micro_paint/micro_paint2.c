#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_print
{
	float	w;
	float	h;
	float	x;
	float	y;
	char	p[2];
	char	r[2];
}				t_print;

typedef struct s_paint
{
	FILE	*fp;
	char	**map;
	int		w;
	int		h;
	char	b[2];
	t_print	p;
}				t_paint;

void ft_rectangle(t_paint *p)
{
	int	x;
	int	y;

	y = -1;
	while (++y <= p->p.h)
	{
		if ((p->p.y + y < p->h) && (p->p.y + y > 0))
		{
			x = -1;
			while (++x <= p->p.w)
			{
				if ((p->p.x + x < p->w && (p->p.x + x > 0))
				{
					if (p->p.r[0] == 'R')
						p->map[(int)p->p.y + y][(int)p->p.x + x] = p->p.p[0];
					else
						if (y == 0 || y == p->p.h || x == 0 || x == p->p.w)
							p->map[(int)p->p.y + y][(int)p->p.x + x] = p->p.p[0];
				}
			}
		}
	}
}

int	ft_check(t_paint *p)
{
	if (p->p.w <= 0 || p->p.h <= 0)
		return (0);
	if (p->w <= 0 || p->w > 300 || p->h <= 0 || p->h > 300)
		return (0);
	if (p->b[0] < 32 || p->b[0] > 126)
		return (0);
	if (p->p.p[0] < 32 || p->p.p[0] > 126)
		return (0);
	return (1);
}

int	ft_read(t_paint *p)
{
	char	tmp;

	if (fscanf(p->fp, "%d %d %s", &p->w, &p->h, p->b) != 3 || p->b[1] != '\0')
		return (0);
	fscanf(p->fp, "%c", &tmp);
	if (tmp != '\n')
		return (0);
	if (fscanf(p->fp, "%s %f %f %f %f %s", p->p.r, &p->p.x, &p->p.y, &p->p.w, &p->p.h, p->p.p) != 6 || p->p.r[1] != '\0' || p->p.p[1] != '\0')
		return (0);
	fscanf(p->fp, "%c", &tmp);
	if (tmp != '\n' && tmp != '\0')
		return (0);
	if (p->p.r[0] != 'R' && p->p.r[0] != 'r')
		return (0);
	if (ft_check(p) == 0)
		return (0);
	return (1);
}

int	ft_map(t_paint *p)
{
	int	i;

	i = -1;
	p->map = (char **) malloc (sizeof(char *) * p->h);
	if (!p->map)
		return (0);
	while (++i < p->h)
	{
		p->map[i] = (char *) malloc (sizeof(char) * p->w);
		if (!p->map[i])
			return(0);
		memset(p->map[i], p->b[0], p->w);
	}
	return (1);
}

void	ft_print(t_paint *p)
{
	int	y;
	int	x;

	y = -1;
	while (++y < p->h)
	{
		x = -1;
		while (++x < p->w)
			write(1, &p->map[y][x], 1);
		write(1, "\n", 1);
	}
}

void	ft_free(t_paint *p)
{
	int	i;

	i = -1;
	while (++i < p->h)
		free(p->map[i]);
	free(p->map);
}

int	main(int argc, char *argv[])
{
	t_paint	p;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 17);
		return (1);
	}
	p.fp = fopen(argv[1], "r");
	if (!p.fp)
	{
		write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	if (ft_read(&p) == 0)
	{
		write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	if (ft_map(&p) == 0)
	{
		write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	ft_rectangle(&p);
	ft_print(&p);
	ft_free(&p);
	return (0);
}
