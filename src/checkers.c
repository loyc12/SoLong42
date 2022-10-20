/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/20 14:57:12 by llord            ###   ########.fr       */
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
