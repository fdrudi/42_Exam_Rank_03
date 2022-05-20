/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:28:04 by fdrudi            #+#    #+#             */
/*   Updated: 2022/05/20 17:46:00 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct s_circle
{
	float	rad;
	float	x;
	float	y;
	char	p[2];
	char	c[2];
}				t_circle;

typedef struct s_paint
{
	FILE		*fp;
	char		**map;
	int			w;
	int			h;
	char		b[2];
	t_circle	c;
	char		tmp;
	int			cntrl;
}				t_paint;

void	ft_free(t_paint *p)
{
	int	i;

	i = -1;
	while (++i < p->h)
		free(p->map[i]);
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
		write(1, "\n", 1);
	}
}

int	ft_read(t_paint *p, int def)
{
	if (def == 1)
	{
		if (fscanf(p->fp, "%d %d %s", &p->w, &p->h, p->b) < 3 || p->b[1] != '\0')
			return (0);
		fscanf(p->fp, "%c", &p->tmp);
		if (p->tmp != '\n')
			return (0);
		p->cntrl = 0;
	}
	else
	{
		if (p->cntrl > 0)
		{
			if (fscanf(p->fp, "%s", p->c.c) != 1 || p->c.c[0] == '\0')
			{
				p->tmp = '\0';
				return (3);
			}
			if (fscanf(p->fp, "%f %f %f %s", &p->c.x, &p->c.y, &p->c.rad, p->c.p) < 4
				|| p->c.c[1] != '\0' || p->c.p[1] != '\0')
				return (0);
		}
		else
		{
			if (fscanf(p->fp, "%s %f %f %f %s", p->c.c, &p->c.x, &p->c.y, &p->c.rad, p->c.p) < 5
				|| p->c.c[1] != '\0' || p->c.p[1] != '\0')
				return (0);
			fscanf(p->fp, "%c", &p->tmp);
			if (p->tmp != '\n' && p->tmp != '\0')
				return (0);
			if (p->c.c[0] != 'C' && p->c.c[0] != 'c')
				return (0);
			p->cntrl += 1;
		}
	}
	return (1);
}

int	ft_circle(t_paint *p)
{
	int		i;
	int		j;
	int		x;
	int		y;
	float	tmp;

	while (p->tmp != '\0')
	{
		i = ft_read(p, -1);
		if (i == 0)
			return (0);
		else if (i == 3)
			return (1);
		i = -1;
		y = p->c.y - p->c.rad;
		x = p->c.x - p->c.rad;
		while (++i <= p->c.rad * 2)
		{
			if ((y + i) < p->h && (y + i) >= 0)
			{
				j = -1;
				while (++j <= p->c.rad * 2)
				{
					if ((x + j) < p->w && (x + j) >= 0)
					{
						tmp = sqrt(powf(i - p->c.rad, 2) + powf(j - p->c.rad, 2));
						if (tmp <= p->c.rad)
						{
							if (p->c.c[0] == 'C')
								p->map[(int) (y + i)][(int) (x + j)] = p->c.p[0];
							else
								if (p->c.rad - tmp < 1)
									p->map[(int) (y + i)][(int) (x + j)] = p->c.p[0];
						}
					}
				}
			}
		}
		// return (1);
	}
	return (1);
}

int	ft_map(t_paint *p)
{
	int	i;

	i = -1;
	p->map = (char **) malloc (sizeof(char *) * p->h + 1);
	if (!p->map)
		return (0);
	while (++i < p->h)
	{
		p->map[i] = (char *) malloc (sizeof(char) * p->w + 1);
		if (!p->map[i])
			return (0);
		memset(p->map[i], p->b[0], p->w);
	}
	p->map[i] = 0;
	return (1);
}


int	main(int argc, char **argv)
{
	t_paint	p;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 17);
		return (1);
	}
	p.fp = fopen(argv[1], "r");
	if (ft_read(&p, 1) == 0)
	{	write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	if (ft_map(&p) == 0)
	{
		write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	if (ft_circle(&p) == 0)
	{
		write(1, "Error: Operation file corrupted\n", 33);
		return (1);
	}
	ft_print(&p);
	ft_free(&p);
	fclose(p.fp);
	return (0);
}
