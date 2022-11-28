/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonusers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/11/28 13:33:11 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//moves an enemy to a neighboring tile if need be
void	move_enemy_to(t_data *d, t_tile *dst_tile, int id)
{
	t_tile *src_tile;
	src_tile = find_tile(d, d->enemies[id]);

	if (dst_tile && src_tile)
	{
		d->enemies[id] = dst_tile->bc;
		if (dst_tile->bc == d->pc)
			d->md->state = STATE_DYING;
		src_tile->type = TYPE_EMPTY;
		src_tile->object = NULL;
		dst_tile->type = TYPE_ENEMY;
		//printf("Enemy #%i moved to tile (%i,%i)\n", id, dst_tile->bc->x, dst_tile->bc->y);	//REMOVE ME
	}

}

//makes the enemies move
void	move_enemies(t_data *d)
{
	t_tile	*dst_tile;
	t_tile	*src_tile;
	char	*order;
	int		id;
	int		i;

	id = -1;
	while (++id < d->nm_n)
	{
		src_tile = find_tile(d, d->enemies[id]);
		if (d->md->difficulty <= (rand() % 8))
			move_random(d, src_tile, id);
		else
		{
			i = -1;
			order = random_comb();
			while (++i < 4)
			{
				dst_tile = find_neighbor(src_tile, order[i]);
				if (can_move_to(dst_tile, 'A') && dst_tile->dst_p < src_tile->dst_p)
				{
					move_enemy_to(d, dst_tile, id);
					break ;
				}
			}
			free(order);
		}
	}
}

//makes the player move automatically
void	solve(t_data *d)
{
	t_tile	*dst_tile;
	t_tile	*src_tile;
	char	*order;
	int		i;

	i = -1;
	order = random_comb();
	src_tile = find_tile(d, d->pc);
	while (++i < 4)
	{
		dst_tile = find_neighbor(src_tile, order[i]);
		if (can_move_to(dst_tile, 'P') && dst_tile->dst_f < src_tile->dst_f)
		{
			move_player(d, dst_tile);
			break ;
		}
	}
	free(order);
	if (i == 4 && d->pc != d->ec)
		move_random(d, src_tile, -1);
	usleep(40000);
}
