/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:53:45 by fdrudi            #+#    #+#             */
/*   Updated: 2022/03/29 16:08:53 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct	s_paint
{
	FILE	*fp;
	char	**map;
	int		w_x;
	int		w_y;
	char	s[2];
	char	c[2];
	float	c_x;
	float	c_y;
	float	rad;
	char	tmp;
}				t_paint;

void	ft_print(t_paint *p)
{
	int	i;
	int	j;

	i = -1;
	while (++i < p->w_y)
	{
		j = -1;
		while (++j < p->w_x)
			write(1, &p->map[i][j], 1);
		write(1, "\n", 1);
	}
}

void	ft_free(t_paint *p)
{
	int	i;

	i = -1;
	while (++i < p->w_y)
		free(p->map[i]);
	free(p->map);
}

int	ft_read(t_paint *p, int def)
{
	if (def == 1)
	{
		if (fscanf(p->fp, "%d %d %s", &p->w_x, &p->w_y, p->s) < 3 || p->s[1] != '\0')
			return (1);
	}
	else
	{
		if (fscanf(p->fp, "%s %f %f %f %s", p->c, &p->c_x, &p->c_y, &p->rad, p->s) < 5
			|| p->s[1] != '\0' || p->c[1] != '\0')
			return (1);
	}
	fscanf(p->fp, "%c", &p->tmp);
	if (p->tmp != '\n')
		return (1);
	return (0);
}

void	ft_circle(t_paint *p)
{
	int		i;
	int		j;
	int		x;
	int		y;
	float	tmp;

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
					tmp = sqrtf(powf(j - p->rad, 2) + powf(i - p->rad, 2));
					if (tmp <= p->rad)
					{
						if (p->c[0] == 'C')
							p->map[(int) y + i][(int) x + j] = p->s[0];
						else
							if (p->rad - tmp < 1)
								p->map[(int) y + i][(int) x + j] = p->s[0];
					}
				}
			}
		}
	}
}

int	ft_window(t_paint *p)
{
	int	i;

	i = -1;
	p->map = (char **) malloc (sizeof(char *) * p->w_y);
	if (!p->map)
		return (1);
	while (++i < p->w_y)
	{
		p->map[i] = (char *) malloc (sizeof(char) * p->w_x);
		if (!p->map[i])
			return (1);
		memset(p->map[i], p->s[0], p->w_x);
	}
	if (ft_read(p, -1) == 1)
		return (1);
	if (p->c[0] != 'C' && p->c[0] != 'c')
		return (1);
	else
		ft_circle(p);
	return (0);
}

int	main(int argc, char **argv)
{
	t_paint	p;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	p.fp = fopen(argv[1], "r");
	if (!p.fp)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	if (ft_read(&p, 1) == 1)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	if (ft_window(&p) == 1)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	ft_print(&p);
	ft_free(&p);
	return (0);
}
