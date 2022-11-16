/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/11/16 13:28:40 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	move_random(t_data *d, t_tile *src_tile, int id)
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
