/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/11/01 11:02:48 by llord            ###   ########.fr       */
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
	t_tile	*new_tile;

	usleep(100000);											//REMOVE ME (forbidden?)

	if (goal == 'N')
		new_tile = find_tile(d->pc, d)->north;
	else if (goal == 'E')
		new_tile = find_tile(d->pc, d)->east;
	else if (goal == 'S')
		new_tile = find_tile(d->pc, d)->south;
	else if (goal == 'W')
		new_tile = find_tile(d->pc, d)->west;
	else
		return ;

	if (new_tile && (new_tile->type != 3 || d->flag_n <= 0))
	{
		if (new_tile->type == 2)
			d->flag_n -= 1;
		empty_tile(d, tile);
		new_tile->type = 4;
		d->pc = new_tile->bc;
		printf("\nsuccessfully moved to : %i,%i\n", d->pc->x, d->pc->y);	//REMOVE ME
	}
	else
		printf("\ncouldn't move to : %i,%i\n", d->pc->x, d->pc->y);			//REMOVE ME
}