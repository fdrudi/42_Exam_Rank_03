/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:03:49 by exam              #+#    #+#             */
/*   Updated: 2022/07/29 12:39:51 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICRO_PAINT_H
#define MICRO_PAINT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

typedef struct s_rect
{
	float	x;
	float	y;
	float	w;
	float	h;
	char	s[2];
	char	c[2];
}				t_rect;

typedef struct s_paint
{
	FILE	*fp;
	char	**map;
	int		w;
	int		h;
	char	c[2];
	char	tmp;
	t_rect	r;
}				t_paint;

#endif
