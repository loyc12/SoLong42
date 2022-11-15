/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/11/15 12:00:00 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	can_move_to(t_tile *tile, char type)
{
	if (tile)
	{
		if (tile->type == TYPE_EMPTY)
			return (1);
		else if (type == 'P')
		{
			if (tile->type == TYPE_FLAG || tile->type == TYPE_END)
				return (1);
		}
		else if (type == 'A')
		{
			if (tile->type == TYPE_PLAYER)
				return (1);
		}
	}
	return (0);
}

//moves the player to a neighboring tile if need be
static void	move_player_to(t_data *d, t_tile *dst_tile)
{
	t_tile *src_tile;
	int	old_n;

	old_n = d->flag_n;
	src_tile = find_tile(d, d->pc);
	d->flag_m++;
	d->flag_r++;
	d->pc = dst_tile->bc;
	if (dst_tile->type == TYPE_FLAG)
	{	
		d->flag_n--;
		//printf("flag collected!\n");													//REMOVE ME
	}
	if (dst_tile->bc == d->ec && d->flag_n < 1)
	{
		d->flag_n--;
		d->md->state = 2;
	}
	src_tile->type = TYPE_EMPTY;
	src_tile->object = NULL;
	dst_tile->type = TYPE_PLAYER;

	//printf("player moved to tile (%i,%i)\n", d->pc->x, d->pc->y);						//REMOVE ME
	
	if (old_n != d->flag_n)
		load_flag_dist(d);
}

//checks if the player can move in the goal direction, and if so, applies the movement
void	move_player(t_data *d, t_tile *src_tile, char goal)
{
	t_tile	*dst_tile;

	dst_tile = NULL;
	if (goal == 'N')
		dst_tile = find_tile(d, src_tile->bc)->north;
	else if (goal == 'E')
		dst_tile = find_tile(d, src_tile->bc)->east;
	else if (goal == 'S')
		dst_tile = find_tile(d, src_tile->bc)->south;
	else if (goal == 'W')
		dst_tile = find_tile(d, src_tile->bc)->west;
	if (can_move_to(dst_tile, 'P'))
	{
		move_player_to(d, dst_tile);
		load_player_dist(d);
		if (0 < d->flag_a && d->pc != d->ec)
			move_enemies(d);
		printf("Move #%i\n", d->flag_m);
	}
	else if (dst_tile && dst_tile->type == TYPE_ENEMY)
		d->md->state = 3;
	else
		printf("Path blocked!\n");											//REMOVE ME
}
