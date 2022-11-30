/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/11/30 14:23:59 by llord            ###   ########.fr       */
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
			if (tile->type == TYPE_FLAG || \
				tile->type == TYPE_END || \
				tile->type == TYPE_ENEMY)
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
	t_tile	*src_tile;
	int		flag_r;

	flag_r = 0;
	src_tile = find_tile(d, d->pc);
	d->mv_c++;
	d->m_flag++;
	d->pc = dst_tile->bc;
	if (dst_tile->type == TYPE_FLAG)
	{	
		d->flg_c--;
		flag_r++;
	}
	if (dst_tile->bc == d->ec && d->flg_c < 1)
		d->md->state = STATE_SUCCEEDING;
	src_tile->type = TYPE_EMPTY;
	src_tile->object = NULL;
	dst_tile->type = TYPE_PLAYER;
	if (flag_r)
		load_flag_dist(d);
}

//checks if the player can move, and if so moves them
void	move_player(t_data *d, t_tile *dst_tile)
{
	if (can_move_to(dst_tile, 'P'))
	{
		move_player_to(d, dst_tile);
		load_player_dist(d);
		if (0 < d->nm_n)
			move_enemies(d);
		printf(" - Move #%i\n", d->mv_c);
	}
	else
		printf(" - Path blocked!\n");
}
