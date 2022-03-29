/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <fdrudi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:33:09 by fdrudi            #+#    #+#             */
/*   Updated: 2022/03/29 17:34:53 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_paint
{
	FILE	*fp;
	char	**map;
	int		w_y;
	int		w_x;
	char	c[2];
	float	r_y;
	float	r_x;
	float	y;
	float	x;
	char	r[2];
	char	tmp;
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

void	ft_rectangle(t_paint *p)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= p->r_y)
	{
		if ((p->r_y + i) < p->w_y && (p->r_y + i) >= 0)
		{
			j = -1;
			while (++j <= p->r_x)
			{
				if ((p->r_x + j) < p->w_x && (p->r_x + j) >= 0)
				{
					if (p->r[0] == 'R')
						p->map[(int) p->r_y + i][(int) p->r_x + j] = p->c[0];
					else
						if (i == 0 || i == p->r_y || j == 0 || j == p->r_x)
							p->map[(int) p->r_y + i][(int) p->r_x + j] = p->c[0];
				}
			}
		}
	}
}

int	ft_read(t_paint *p, int def)
{
	if (def == 1)
	{
		if (fscanf(p->fp, "%d %d %s", &p->w_x, &p->w_y, p->c) < 3 || p->c[1] != '\0')
			return (1);
	}
	else
	{
		if (fscanf(p->fp, "%s %f %f %f %f %s", p->r, &p->r_x, &p->r_y, &p->x, &p->y, p->c) < 6
			|| p->c[1] != '\0' || p->r[1] != '\0')
			return (1);
	}
	fscanf(p->fp, "%c", &p->tmp);
	if (p->tmp != '\n')
		return (1);
	return (0);
}

int	ft_window(t_paint *p)
{
	int	i;

	i = -1;
	p->map = (char **) malloc (sizeof(char *) * p->w_y);
	while (++i < p->w_y)
	{
		p->map[i] = (char *) malloc (sizeof(char) * p->w_x);
		memset(p->map[i], p->c[0], p->w_x);
	}
	if (ft_read(p, -1) == 1)
		return (1);
	if (p->r[0] != 'R' && p->r[0] != 'r')
		return (1);
	else
		ft_rectangle(p);
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
