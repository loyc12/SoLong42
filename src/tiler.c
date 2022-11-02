/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiler.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/02 14:07:15 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//finds a tile in d->tiles from its board coordinates
t_tile	*find_tile(t_coords *bc, t_data *d)
{
	int	index;

	index = (bc->y * d->max_by) + bc->x;
	return (d->tiles[index]);
}

//connects a tile to its north and west neighbor if need be
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

//connects ALL valid tiles together (aka links their "direction pointers")
void	connect_grid(t_data *d)
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

//moves the player to a neighboring tile if need be
void	move_to_tile(t_data *d, t_tile *src_tile, t_tile *dst_tile)
{
	d->flag_m++;
	d->flag_r++;;
	d->pc = dst_tile->bc;
	if (dst_tile->type == 2)
	{	
		d->flag_n--;
		printf("flag collected!\n");										//REMOVE ME
	}
	if (dst_tile->type == 3)
	{
		printf("game completed in %i moves!\n", d->flag_m);					//REMOVE ME
		d->flag_n--;
	}
	src_tile->type = 0;
	src_tile->object = NULL;
	dst_tile->type = 4;
	printf("successfully moved to tile (%i,%i)\n\n", d->pc->x, d->pc->y);	//REMOVE ME
}
