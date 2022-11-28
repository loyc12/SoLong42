/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/28 13:24:33 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//finds a neighboring from a given direction
t_tile	*find_neighbor(t_tile *tile, char goal)
{
	t_tile	*neighbor;

	neighbor = NULL;
	if (goal == 'N')
		neighbor = tile->north;
	else if (goal == 'E')
		neighbor = tile->east;
	else if (goal == 'S')
		neighbor = tile->south;
	else if (goal == 'W')
		neighbor = tile->west;
	return (neighbor);
}

//finds a tile in d->tiles from its board coordinates
t_tile	*find_tile(t_data *d, t_coords *bc)
{
	int		index;

	if (bc->x < 0 || d->max_bx < bc->x)
		return (NULL);
	if (bc->y < 0 || d->max_by < bc->y)
		return (NULL);
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
