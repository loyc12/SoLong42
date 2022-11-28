/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/11/28 08:34:06 by llord            ###   ########.fr       */
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
	int	flag_r;

	flag_r = 0;
	src_tile = find_tile(d, d->pc);
	d->mv_c++;
	d->m_flag++;
	d->pc = dst_tile->bc;
	if (dst_tile->type == TYPE_FLAG)
	{	
		d->flg_c--;
		flag_r++;
		//printf("    Flag collected! %i flags left\n", d->flg_c);		//REMOVE ME
	}
	if (dst_tile->bc == d->ec && d->flg_c < 1)
		d->md->state = 2;
	src_tile->type = TYPE_EMPTY;
	src_tile->object = NULL;
	dst_tile->type = TYPE_PLAYER;
	if (flag_r)
		load_flag_dist(d);
}

//checks if the player can move in the goal direction, and if so, applies the movement
void	move_player(t_data *d, t_tile *dst_tile)
{
	if (can_move_to(dst_tile, 'P'))
	{
		move_player_to(d, dst_tile);
		load_player_dist(d);
		if (0 < d->nm_n && d->pc != d->ec)
			move_enemies(d);
		printf("Move #%i\n", d->mv_c);
	}
	else if (dst_tile && dst_tile->type == TYPE_ENEMY)
		d->md->state = 3;
	else
		printf("Path blocked!\n");										//REMOVE ME
}
