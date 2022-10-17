/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinaters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/17 10:07:11 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	find_wx(t_coords *bc, t_data *d)
{
	int wx;	//window x position
	int	center_offset;
	int	window_offset;

	window_offset = (d->max_wx - d->asset_size) / 2;
	center_offset = d->asset_size * (d->max_bx - d->max_by) / 4;

	wx = ((bc->x - bc->y) * d->asset_size / 2) + window_offset - center_offset;

	return (wx);
}

int	find_wy(t_coords *bc, t_data *d)
{
	int wy;	//window y position
	int	window_offset;
	int	center_offset;

	window_offset = (d->max_wy - d->asset_size) / 2;
	center_offset = d->asset_size * (d->max_bx + d->max_by) / 8;

	wy = ((bc->x + bc->y - (bc->z / 2)) * d->asset_size / 4) + window_offset - center_offset;

	return (wy);
}
