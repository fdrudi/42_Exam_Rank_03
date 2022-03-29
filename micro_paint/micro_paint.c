/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:25:43 by fdrudi            #+#    #+#             */
/*   Updated: 2022/03/29 14:35:24 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct	s_paint
{
	FILE	*fp;
	int		w_y;
	int		w_x;
	char	c[2];
	char	tmp;
	float	p_x;
	float	p_y;
	float	x;
	float	y;
	char	r[2];
	char	c2[2];
	char	**map;
}				t_paint;

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
		if (fscanf(p->fp, "%d %d %s", &p->w_x, &p->w_y, p->c) < 3 || p->c[1] != '\0')
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
		fscanf(p->fp, "%c", &p->tmp);
		if (p->tmp != '\n')
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
	}
	else
	{
		if (fscanf(p->fp, "%s %f %f %f %f %s", p->r, &p->p_x, &p->p_y, &p->x, &p->y, p->c2) < 6
			|| p->c2[1] != '\0' || p->r[1] != '\0')
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
		fscanf(p->fp, "%c", &p->tmp);
		if (p->tmp != '\n')
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
	}
	return (0);
}

void	ft_print_map(t_paint *p)
{
	int	y;
	int	x;

	y = -1;
	while (++y < p->w_y)
	{
		x = -1;
		while (++x < p->w_x)
			write(1, &p->map[y][x], 1);
		write(1, "\n", 1);
	}
}

void	ft_square(t_paint *p)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= p->y)
	{
		if ((p->p_y + i) < p->w_y && (p->p_y + i) >= 0)
		{
			j = -1;
			while (++j <= p->x)
			{
				if ((p->p_x + j) < p->w_x && (p->p_x + j) >= 0)
				{
					if (p->r[0] == 'R')
						p->map[(int) p->p_y + i][(int) p->p_x + j] = p->c2[0];
					else
						if ((i == 0 || i == p->y) || (j == 0 || j == p->x))
							p->map[(int) p->p_y + i][(int) p->p_x + j] = p->c2[0];
				}
			}
		}
	}
}

int	ft_window(t_paint *p)
{
	int	i;

	i = 0;
	p->map = (char **) malloc (sizeof(char *) * p->w_y);
	if (!p->map)
		return (1);
	while (i < p->w_y)
	{
		p->map[i] = (char *) malloc (sizeof(char) * p->w_x);
		if (!p->map[i])
			return (1);
		memset(p->map[i], p->c[0], p->w_x);
		i++;
	}
	if (ft_read(p, -1) == 1)
		return (1);
	if (p->r[0] != 'R' && p->r[0] != 'r')
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	else
		ft_square(p);
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
	ft_print_map(&p);
	ft_free(&p);
	fclose(p.fp);
	return (0);
}
