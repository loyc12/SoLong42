/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/31 15:56:51 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	is_in_board(t_data *d, t_coords *bc)
{
	if (0 <= bc->x && bc->x <= d->max_bx)
		if (0 <= bc->y && bc->y <= d->max_by)
			return (1);
	return (0);
}

int	is_in_window(t_data *d, t_coords *wc)
{
	if (0 <= wc->x && wc->x <= d->max_wx)
		if (0 <= wc->y && wc->y <= d->max_wy)
			return (1);
	return (0);
}

int	is_valid(char *input)
{
	int	flag;
	int	i;

	i = -1;
	flag = 1;
	while (input[++i])
	{
		if (input[i] == 'P')
			flag *= 2;
		if (input[i] == 'E')
			flag *= 3;
	}
	if (flag != 6)
		return (0);
	return (1);
}

int	is_in_range(t_data *d, t_tile *tile)
{
	if (d->pc->x - 1 <= tile->bc->x && 0 < tile->bc->x)
	 	if (d->pc->y - 1 <= tile->bc->y && 0 < tile->bc->y)
			return (1);
	return (0);
}
