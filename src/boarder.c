/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boarder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/20 16:01:08 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static t_tile	*make_tile(char type, t_coords bc)
{
	t_tile		*tile;
	t_coords	*c;

	tile = calloc(2, sizeof(t_tile));
	c = calloc(2, sizeof(t_coords));

	c->x = bc.x;
	c->y = bc.y;
	tile->bc = c;
	tile->north = NULL;
	tile->east = NULL;
	tile->south = NULL;
	tile->west = NULL;
	
	if (type == '0')
		tile->type = 0;
	if (type == '1')
		tile->type = 1;
	if (type == '?')			//symbol for flag???
		tile->type = 2;
	if (type == 'E')
		tile->type = 3;
	if (type == 'P')
		tile->type = 4;

	return (tile);
}

t_tile	**make_board(char *input, int size)
{
	t_tile		**tiles;
	t_coords	bc;
	int			i;

	tiles = calloc(size, sizeof(t_tile*));
	bc.y = 0;
	i = 0;
	while (input[i])
	{
		bc.x = 0;
		while (input[i] && input[i] != '\n')
		{
			tiles[i] = make_tile(input[i], bc);
			bc.x++;
			i++;
		}
		bc.y++;
		if (input[i] == '\n')
			i++;
	}
	return (tiles);
}