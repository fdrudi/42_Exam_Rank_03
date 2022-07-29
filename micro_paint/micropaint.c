#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

typedef struct s_sqr
{
	float	y;
	float	x;
	float	w;
	float	h;
	char	c[2];
	char	s[2];
}				t_sqr;

typedef struct s_paint
{
	FILE	*fp;
	char	**map;
	int		h;
	int		w;
	char	c[2];
	char	tmp;
	t_sqr	r;
}				t_paint;

int	ft_error(char *s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
		write(1, &s[i], 1);
	return (1);
}

void	ft_free(t_paint *p)
{
	int	i;

	i = 0;
	while (p->map[i])
	{
		free(p->map[i]);
		i++;
	}
	free(p->map);
}

void	ft_print(t_paint *p)
{
	int	i;
	int	j;

	i = -1;
	while (++i < p->h)
	{
		j = -1;
		while (++j < p->w)
			write(1, &p->map[i][j], 1);
		write (1, "\n", 1);
	}
}

int	ft_read_b(t_paint *p)
{
	if (fscanf(p->fp, "%s", p->r.s) != 1 || p->r.s[0] == '\0')
		return (2);
	if (p->r.s[1] != '\0')
		return (0);
	if (p->r.s[0] != 'r' && p->r.s[0] != 'R')
		return (0);
	if (fscanf(p->fp, "%f %f %f %f %s", &p->r.x, &p->r.y, &p->r.w, &p->r.h, p->r.c) < 5 || p->r.c[1] != '\0')
		return (0);
	if (p->r.w <= 0 || p->h <= 0)
		return (0);
	fscanf(p->fp, "%c", &p->tmp);
	if (p->tmp != '\0' && p->tmp != '\n')
		return (0);
	return (1);
}

int	ft_rect(t_paint *p)
{
	int	i;
	int	j;

	while (p->tmp != '\0')
	{
		i = ft_read_b(p);
		if (i == 2)
			break;
		if (i == 0)
			return (0);
		i = -1;
		while (++i < (int)p->r.h)
		{
			if (i + p->r.y < p->h && i + p->r.y >= 0)
			{
				j = -1;
				while (++j < (int)p->r.w)
				{
					if (j + p->r.x < p->w && j + p->r.x >= 0)
					{
						if (p->r.s[0] == 'R')
							p->map[i + (int)p->r.y][j + (int)p->r.x] = p->r.c[0];
						else if (i == 0 || j == 0 || i == p->r.h - 1 || j == p->r.w - 1)
							p->map[i + (int)p->r.y][j + (int)p->r.x] = p->r.c[0];
					}
				}
			}
		}
	}
	return (1);
}

int	ft_read(t_paint *p)
{
	if (fscanf(p->fp, "%d %d %s", &p->w, &p->h, p->c) < 3 || p->c[1] != '\0')
		return (0);
	if (p->w < 0 || p->w > 300 || p->h < 0 || p->h > 300)
		return (0);
	fscanf(p->fp, "%c", &p->tmp);
	if (p->tmp != '\0' && p->tmp != '\n')
		return (0);
	return (1);
}

int	ft_map(t_paint *p)
{
	int i;

	i = 0;
	p->map = (char **) malloc (sizeof(char *) * (p->h + 1));
	if (!p->map)
		return (0);
	while (i < p->h)
	{
		p->map[i] = (char *) malloc (sizeof(char) * (p->w + 1));
		if (!p->map[i])
			return (0);
		if (memset(p->map[i], p->c[0], p->w) == NULL)
			return (0);
		i++;
	}
	p->map[i] = NULL;
	return (1);
}

int	main(int argc, char *argv[])
{
	t_paint	p;

	if (argc != 2)
		return (ft_error("Error: argument\n"));
	p.fp = fopen(argv[1], "r");
	if (!p.fp)
		return (1);
	if (ft_read(&p) == 0)
		return (ft_error("Error: Operation file corrupted\n"));
	if (ft_map(&p) == 0)
		return (1);
	if (ft_rect(&p) == 0)
		return (ft_error("Error: Operation file corrupted\n"));
	ft_print(&p);
	ft_free(&p);
	fclose(p.fp);
	return (0);
}
