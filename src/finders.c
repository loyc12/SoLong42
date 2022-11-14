/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/14 16:15:05 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//finds a tile in d->tiles from its board coordinates
t_tile	*find_tile(t_data *d, t_coords *bc)
{
	int	index;

	index = (bc->y * (d->max_bx + 1)) + bc->x;
	return (d->tiles[index]);
}

//finds the number of tiles in a given input
int	find_tile_number(char *input)
{
	int	n;
	int	i;

	i = -1;
	n = 0;

	while (input[++i])
		if (input[i] != '\n')
			n++;
	return (n);
}

//finds the number of enemies in a given input
int	find_enemy_number(char *input)
{
	int	n;
	int	i;

	i = -1;
	n = 0;

	while (input[++i])
		if (input[i] == 'A')
			n++;
	return (n);
}
