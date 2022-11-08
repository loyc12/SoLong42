/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/08 13:17:16 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//finds a tile in d->tiles from its board coordinates
t_tile	*find_tile(t_data *d, t_coords *bc)
{
	int	index;

	index = (bc->y * (d->max_bx + 1)) + bc->x;
	return (d->tiles[index]);
}

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

	i = -1;
	printf("board size is %i\n", d->board_s);								//REMOVE ME
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		if (tile->type != TYPE_WALL)
			connect_tile(d, tile, i);
	}
	if (is_map_valid(d))
		printf("map has been validated!\n");								//REMOVE ME
	load_flag_dist(d);
	load_player_dist(d);
}

//moves the player to a neighboring tile if need be
void	move_to_tile(t_data *d, t_tile *src_tile, t_tile *dst_tile)
{
	int	flag;

	flag = 0;
	d->flag_m++;
	d->flag_r++;
	d->pc = dst_tile->bc;
	if (dst_tile->type == TYPE_FLAG)
	{	
		d->flag_n--;
		printf("\nflag collected!\n");										//REMOVE ME
		flag = 1;
	}
	if (dst_tile->bc == d->ec && d->flag_n < 1)
	{
		printf("\ngame completed in %i moves!!!\n\n", d->flag_m);			//REMOVE ME
		d->flag_n--;
	}
	src_tile->type = TYPE_EMPTY;
	src_tile->object = NULL;
	dst_tile->type = TYPE_PLAYER;
	printf("successfully moved to tile (%i,%i)\n", d->pc->x, d->pc->y);		//REMOVE ME
	if (flag)
		load_flag_dist(d);
}
