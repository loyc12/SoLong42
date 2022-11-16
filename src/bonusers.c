/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/11/16 13:05:27 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//moves an enemy to a neighboring tile if need be
void	move_enemy_to(t_data *d, t_tile *dst_tile, int id)
{
	t_tile *src_tile;

	src_tile = find_tile(d, d->enemies[id]);
	d->enemies[id] = dst_tile->bc;
	if (dst_tile->bc == d->pc)
		d->md->state = 3;
	src_tile->type = TYPE_EMPTY;
	src_tile->object = NULL;
	dst_tile->type = TYPE_ENEMY;

	//printf("Enemy #%i moved to tile (%i,%i)\n", id, dst_tile->bc->x, dst_tile->bc->y);	//REMOVE ME
}

//checks if the enemy can move in the goal direction, and if so, applies the movement
static void	move_enemy(t_data *d, t_tile *src_tile, char goal, int id)
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
	move_enemy_to(d, dst_tile, id);
}

void	move_enemies(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	while (++i < d->nm_n)
	{
		tile = find_tile(d, d->enemies[i]);
		if (d->md->difficulty <= (rand() % 8))
			move_random(d, tile, i);
		else if (can_move_to(tile->north, 'A') && tile->north->dst_p < tile->dst_p)
			move_enemy(d, tile, 'N', i);
		else if (can_move_to(tile->east, 'A') && tile->east->dst_p < tile->dst_p)
			move_enemy(d, tile, 'E', i);
		else if (can_move_to(tile->south, 'A') && tile->south->dst_p < tile->dst_p)
			move_enemy(d, tile, 'S', i);
		else if (can_move_to(tile->west, 'A') && tile->west->dst_p < tile->dst_p)
			move_enemy(d, tile, 'W', i);
		else
			move_random(d, tile, i);
	}
}

//makes the player move automatically
void	solve(t_data *d)
{
	t_tile	*tile;

	tile = find_tile(d, d->pc);
	if (can_move_to(tile->north, 'P') && tile->north->dst_f < tile->dst_f)
		move_player(d, tile, 'N');
	else if (can_move_to(tile->east, 'P') && tile->east->dst_f < tile->dst_f)
		move_player(d, tile, 'E');
	else if (can_move_to(tile->south, 'P') && tile->south->dst_f < tile->dst_f)
		move_player(d, tile, 'S');
	else if (can_move_to(tile->west, 'P') && tile->west->dst_f < tile->dst_f)
		move_player(d, tile, 'W');
	else if (d->pc != d->ec)
		printf("Player bot is lost bruh...\n");												//REMOVE ME
	usleep(40000);
}