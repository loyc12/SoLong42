/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/29 12:35:35 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//connects a tile to its north and west neighbor if need be
static void	connect_tile(t_data *d, t_tile *tile, int i)
{
	if (d->tiles[i - (d->max_bx + 1)]->type != TYPE_WALL)
	{
		tile->north = d->tiles[i - (d->max_bx + 1)];
		tile->north->south = tile;
	}
	if (d->tiles[i - 1]->type != TYPE_WALL)
	{
		tile->west = d->tiles[i - 1];
		tile->west->east = tile;
	}
}

//connects ALL valid tiles together (aka links their "direction pointers")
void	connect_grid(t_data *d)
{
	t_tile	*tile;
	int		i;

	//printf("  Board size is %i (%ix%i)\n", d->board_s, d->max_bx + 1, d->max_by + 1);	//REMOVE ME
	i = -1;
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		if (tile->type != TYPE_WALL && 0 < tile->bc->x && 0 < tile->bc->y)
			connect_tile(d, tile, i);
	}
	if (is_map_valid(d))
	{
		//printf("Map has been validated!\n");											//REMOVE ME

		load_flag_dist(d);
		load_player_dist(d);
	}
	else
		d->md->state = STATE_ERR_MAP;
}
