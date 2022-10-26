/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiler.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/25 11:57:51 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	connect_tile(t_data *d, t_tile *tile, int i)
{
	if (d->tiles[i - d->max_by]->type != 1)
	{
		tile->north = d->tiles[i - d->max_by];
		tile->north->south = tile;
	}
	if (d->tiles[i - 1]->type != 1)
	{
		tile->west = d->tiles[i - 1];
		tile->west->east = tile;
	}
}

void	connect_tiles(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		if (tile->type != 1 && 0 < tile->bc->x && 0 < tile->bc->y)
		connect_tile(d, tile, i);
	}
}