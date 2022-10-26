/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/10/25 12:16:40 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void move_player(t_data *d, t_tile *tile, char goal)
{
	if (goal == 'N' && find_tile(d->pc, d)->north)
	{
		tile->type = 0;
		tile->north->type = 4;
		d->pc = tile->north->bc;
	}
	else if (goal == 'E' && find_tile(d->pc, d)->east)
	{
		tile->type = 0;
		tile->east->type = 4;
		d->pc = tile->east->bc;
	}
	else if (goal == 'S' && find_tile(d->pc, d)->south)
	{
		tile->type = 0;
		tile->south->type = 4;
		d->pc = tile->south->bc;
	}
	else if (goal == 'W' && find_tile(d->pc, d)->west)
	{
		tile->type = 0;
		tile->west->type = 4;
		d->pc = tile->west->bc;
	}
	printf("\nplayer coords: %i,%i\n", d->pc->x, d->pc->y);	//REMOVE ME
	d->updated += 1;
}