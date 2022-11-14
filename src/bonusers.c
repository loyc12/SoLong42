/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonusers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/11/14 16:19:08 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//moves an enemy to a neighboring tile if need be
static void	move_enemy_to(t_data *d, t_tile *dst_tile, int id)
{
	t_tile *src_tile;

	src_tile = find_tile(d, d->enemies[id]);
	d->enemies[id] = dst_tile->bc;
	if (dst_tile->bc == d->pc)
		d->md->state = 3;
	src_tile->type = TYPE_EMPTY;
	src_tile->object = NULL;
	dst_tile->type = TYPE_ENEMY;

	//printf("enemy moved to tile (%i,%i)\n", dst_tile->bc->x, dst_tile->bc->y);			//REMOVE ME
}

static void	move_random(t_data *d, t_tile *src_tile, int id)
{
	t_tile	*dst_tile;
	int		i;

	dst_tile = NULL;
	i = rand() % 6;
	if (i == 0)
		dst_tile = find_tile(d, src_tile->bc)->north;
	else if (i == 1)
		dst_tile = find_tile(d, src_tile->bc)->east;
	else if (i == 2)
		dst_tile = find_tile(d, src_tile->bc)->south;
	else if (i == 3)
		dst_tile = find_tile(d, src_tile->bc)->west;
	if (can_move_to(dst_tile, 'A'))
		move_enemy_to(d, dst_tile, id);
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
	while (++i < d->flag_a)
	{
		tile = find_tile(d, d->enemies[i]);
		if (d->md->difficulty <= (rand() % 8))
			move_random(d, tile, i);
		else if (can_move_to(tile->north, 'A') && tile->north->flag_e < tile->flag_e)
			move_enemy(d, tile, 'N', i);
		else if (can_move_to(tile->east, 'A') && tile->east->flag_e < tile->flag_e)
			move_enemy(d, tile, 'E', i);
		else if (can_move_to(tile->south, 'A') && tile->south->flag_e < tile->flag_e)
			move_enemy(d, tile, 'S', i);
		else if (can_move_to(tile->west, 'A') && tile->west->flag_e < tile->flag_e)
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
	if (can_move_to(tile->north, 'P') && tile->north->flag_f < tile->flag_f)
		move_player(d, tile, 'N');
	else if (can_move_to(tile->east, 'P') && tile->east->flag_f < tile->flag_f)
		move_player(d, tile, 'E');
	else if (can_move_to(tile->south, 'P') && tile->south->flag_f < tile->flag_f)
		move_player(d, tile, 'S');
	else if (can_move_to(tile->west, 'P') && tile->west->flag_f < tile->flag_f)
		move_player(d, tile, 'W');
	else if (d->pc != d->ec)
		printf("Player bot is lost bruh...\n");
	usleep(30000);
}