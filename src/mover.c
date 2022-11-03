/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/11/03 17:37:10 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//checks if the player can move in the goal direction, and if so, applies the movement
void	move_player(t_data *d, t_tile *tile, char goal)
{
	t_tile	*dst_tile;

	dst_tile = NULL;

	if (goal == 'N')
		dst_tile = find_tile(d->pc, d)->north;
	else if (goal == 'E')
		dst_tile = find_tile(d->pc, d)->east;
	else if (goal == 'S')
		dst_tile = find_tile(d->pc, d)->south;
	else if (goal == 'W')
		dst_tile = find_tile(d->pc, d)->west;
	else
		return ;
	if (dst_tile && (dst_tile->type != TYPE_END || d->flag_n <= 0))
		move_to_tile(d, tile, dst_tile);
	else
		printf("path blocked!\n");											//REMOVE ME
}

void	load_tile_dist(t_data *d)
{
	int	i;

	i = -1;
	while(++i < d->board_s)
	{
		d->tiles[i]->flag_f = d->board_s;
	}
	i = -1;
	if (0 < d->flag_n)
	{
		while(++i < d->board_s)
			if (d->tiles[i]->type == TYPE_FLAG)
				fill_tile_dist(d, d->tiles[i], 0);
	}
	else
		fill_tile_dist(d, find_tile(d->ec, d), 0);
	i = -1;
	while(++i < d->board_s)
	{
		printf("value for (%i, %i) is %i\n", d->tiles[i]->bc->x, d->tiles[i]->bc->y, d->tiles[i]->flag_f);
	}
}