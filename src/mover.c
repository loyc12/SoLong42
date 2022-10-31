/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/10/31 13:46:38 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void empty_tile(t_data *d, t_tile *tile)
{
	tile->type = 0;
	tile->object = NULL;
	d->updated += 1;
}

void move_player(t_data *d, t_tile *tile, char goal)
{
	if (goal == 'N' && find_tile(d->pc, d)->north)
	{
		empty_tile(d, tile);
		tile->north->type = 4;
		d->pc = tile->north->bc;
	}
	else if (goal == 'E' && find_tile(d->pc, d)->east)
	{
		empty_tile(d, tile);
		tile->east->type = 4;
		d->pc = tile->east->bc;
	}
	else if (goal == 'S' && find_tile(d->pc, d)->south)
	{
		empty_tile(d, tile);
		tile->south->type = 4;
		d->pc = tile->south->bc;
	}
	else if (goal == 'W' && find_tile(d->pc, d)->west)
	{
		empty_tile(d, tile);
		tile->west->type = 4;
		d->pc = tile->west->bc;
	}
	printf("\nplayer coords: %i,%i\n", d->pc->x, d->pc->y);	//REMOVE ME
}