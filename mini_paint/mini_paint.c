/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:43:15 by fdrudi            #+#    #+#             */
/*   Updated: 2022/05/20 16:08:55 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_free(t_paint *p)
{
	int	i;

	i = -1;
	while (++i < p->w_y)
		free(p->map[i]);
	free(p->map);
}

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

int	ft_read(t_paint *p, int def)
{
	if (def == 1)
	{
		if (fscanf(p->fp, "%d %d %s", &p->w_x, &p->w_y, p->c) < 3 || p->c[1] != '\0')
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
	}
	else
	{
		if (fscanf(p->fp, "%s %f %f %f %s", p->c2, &p->c_x, &p->c_y, &p->rad, p->c3) < 5
			|| p->c2[1] != '\0' || p->c3[1] != '\0')
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
	}
	fscanf(p->fp, "%c", &p->tmp);
	if (p->tmp != '\n')
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	return (0);
}

void	ft_circle(t_paint *p)
{
	int		i;
	int		j;
	int		x;
	int		y;
	float	tmp;

	i = -1;
	y = p->c_y - p->rad;
	x = p->c_x - p->rad;
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
							p->map[(int) (y + i)][(int) (x + j)] = p->c3[0];
						else
							if (p->rad - tmp < 1)
								p->map[(int) (y + i)][(int) (x + j)] = p->c3[0];
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
		memset(p->map[i], p->c[0], p->w_x);
	}
	if (ft_read(p, -1) == 1)
		return (1);
	if (p->c2[0] != 'c' && p->c2[0] != 'C')
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
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
	if (ft_read(&p, 1) == 1)
		return (1);
	if (ft_window(&p) == 1)
		return (1);
	ft_print(&p);
	ft_free(&p);
	fclose(p.fp);
	return (0);
}
