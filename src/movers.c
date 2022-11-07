/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/11/07 16:30:16 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
		move_to_tile(d, tile, dst_tile);
	else
		printf("path blocked!\n");											//REMOVE ME
}
