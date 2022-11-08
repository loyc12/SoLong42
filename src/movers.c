/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/11/08 13:37:39 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
/*
static void	move_enemies(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	while (d->enemies[++i])
	{
		tile = find_tile(d, d->enemies[i]);
		if (tile->north && tile->north->flag_e < tile->flag_e)
			move_enemy(d, tile, 'N');
		else if (tile->east && tile->east->flag_e < tile->flag_e)
			move_enemy(d, tile, 'E');
		else if (tile->south && tile->south->flag_e < tile->flag_e)
			move_enemy(d, tile, 'S');
		else if (tile->west && tile->west->flag_e < tile->flag_e)
			move_enemy(d, tile, 'W');
		else
			printf("enemy at (%i,%i)cannot move...\n", tile->bc->x, tile->bc->y);
	}
}
*/

//checks if the player can move in the goal direction, and if so, applies the movement
void	move_player(t_data *d, t_tile *tile, char goal)
{
	t_tile	*dst_tile;

	dst_tile = NULL;
	if (goal == 'N')
		dst_tile = find_tile(d, d->pc)->north;
	else if (goal == 'E')
		dst_tile = find_tile(d, d->pc)->east;
	else if (goal == 'S')
		dst_tile = find_tile(d, d->pc)->south;
	else if (goal == 'W')
		dst_tile = find_tile(d, d->pc)->west;
	else
		return ;
	if (dst_tile)
	{
		move_to_tile(d, tile, dst_tile);
		load_player_dist(d);
	}
	else
		printf("path blocked!\n");											//REMOVE ME
}
