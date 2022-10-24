/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiler.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/24 14:22:24 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	connect_tile(t_data *d, t_tile *tile, int i)
{
	t_tile	*north_tile;
	t_tile	*west_tile;

	north_tile = d->tiles[i - d->max_by];
	west_tile = d->tiles[i - 1];
	if (north_tile->type != 0)
	{
		tile->north = north_tile;
		north_tile->south = tile;
	}
	if (west_tile->type != 0)
	{
		tile->west = west_tile;
		west_tile->east = tile;
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
		if (tile->type != 0 && 0 < tile->bc->x && 0 < tile->bc->y)
		connect_tile(d, tile, i);
	}
}