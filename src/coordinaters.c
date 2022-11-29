/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinaters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/29 16:42:00 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//allocates a new t_coord and copies given coordinates inside it
t_coords	*clone_coords(t_coords c1)
{
	t_coords	*c2;

	c2 = ft_calloc(1, sizeof(t_coords));
	c2->x = c1.x;
	c2->y = c1.y;
	return (c2);
}

//convert a board x coord into a window x coord
static int	find_wx(t_data *d, t_coords *bc)
{
	int	wx;
	int	center_offset;
	int	window_offset;

	window_offset = (d->max_wx - d->asset_s) / 2;
	center_offset = d->asset_s * (d->max_bx - d->max_by) / 4;
	wx = ((bc->x - bc->y) * d->asset_s / 2) + window_offset - center_offset;
	return (wx);
}

//convert a board y coord into a window y coord
static int	find_wy(t_data *d, t_coords *bc)
{
	int	wy;
	int	window_offset;
	int	center_offset;

	window_offset = (d->max_wy - d->asset_s) / 2;
	center_offset = d->asset_s * (d->max_bx + d->max_by) / 8;
	wy = ((bc->x + bc->y) * d->asset_s / 4) + window_offset - center_offset;
	return (wy);
}

//converts board coordinates to window coordinates
t_coords	*bc_to_wc(t_data *d, t_coords *bc)
{
	t_coords	*wc;

	wc = ft_calloc(1, sizeof(t_coords));
	wc->x = find_wx(d, bc);
	wc->y = find_wy(d, bc);
	return (wc);
}
