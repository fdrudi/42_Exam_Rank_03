/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipaint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdrudi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:26:05 by fdrudi            #+#    #+#             */
/*   Updated: 2022/07/28 17:59:46 by fdrudi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct	s_cir
{
	float	rad;
	float	x;
	float	y;
	char	c[2];
	char	s[2];
}				t_cir;

typedef struct s_paint
{
	FILE	*fp;
	char	**map;
	int		w;
	int		h;
	char	c[2];
	char	tmp;
	t_cir	circl;
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

int	ft_error(char *s)
{
	int i;

	i = -1;
	while (s[++i] != '\0')
		write(1, &s[i], 1);
	return (1);
}

int	ft_read_circle(t_paint *p)
{
	if (fscanf(p->fp, "%s", p->circl.s) != 1 || p->circl.s[0] == '\0')
		return (2);
	if ((p->circl.s[0] != 'C' && p->circl.s[0] != 'c') || p->circl.s[1] != '\0')
		return (0);
	if (fscanf(p->fp, "%f %f %f %s", &p->circl.x, &p->circl.y, &p->circl.rad, p->circl.c) < 4
				|| p->circl.c[1] != '\0')
	fscanf(p->fp, "%c", &p->tmp);
	if (p->tmp != '\n' && p->tmp != '\0')
		return (0);
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
		i = ft_read_circle(p);
		if (i == 0)
			return (ft_error("Error: Operation file corrupted\n"));
		if (i == 2)
			break;
		i = -1;
		y = p->circl.y - p->circl.rad;
		x = p->circl.x - p->circl.rad;
		while (++i <= p->circl.rad * 2)
		{
			if ((y + i) < p->h && (y + i) >= 0)
			{
				j = -1;
				while (++j <= p->circl.rad * 2)
				{
					if ((x + j) < p->w && (x + j) >= 0)
					{
						tmp = sqrt(powf(i - p->circl.rad, 2) + powf(j - p->circl.rad, 2));
						if (tmp <= p->circl.rad)
						{
							if (p->circl.s[0] == 'C')
								p->map[(int) (y + i)][(int) (x + j)] = p->circl.c[0];
							else
								if (p->circl.rad - tmp < 1)
									p->map[(int) (y + i)][(int) (x + j)] = p->circl.c[0];
						}
					}
				}
			}
		}
	}
	return (0);
}

int	ft_map(t_paint *p)
{
	int	i;

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

int	ft_read(t_paint *p)
{
	if (fscanf(p->fp, "%d %d %s", &p->w, &p->h, p->c) < 3 || p->c[1] != '\0')
		return (0);
	fscanf(p->fp, "%c", &p->tmp);
	if (p->tmp != '\n' && p->tmp != '\0')
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_paint	p;

	if (argc != 2)
		return (ft_error("Error: argument\n"));
	p.fp = fopen(argv[1], "r");
	if (!p.fp)
		return (ft_error("Error: Operation file corrupted\n"));
	if (ft_read(&p) == 0)
		return (ft_error("Error: Operation file corrupted\n"));
	if (ft_map(&p) == 0)
		return (1);
	if (ft_circle(&p) == 1)
		return (1);
	ft_print(&p);
	ft_free(&p);
	fclose(p.fp);
	return (0);
}
