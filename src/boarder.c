/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boarder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/24 10:20:14 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static t_tile	*make_tile(char type, t_coords bc)
{
	t_tile		*tile;
	t_coords	*c;

	tile = calloc(1, sizeof(t_tile));
	c = calloc(1, sizeof(t_coords));

	c->x = bc.x;
	c->y = bc.y;
	tile->bc = c;
	tile->north = NULL;
	tile->east = NULL;
	tile->south = NULL;
	tile->west = NULL;
	
	tile->type = 0;
	if (type == '1')
		tile->type = 1;
	else if (type == 'C')
		tile->type = 2;
	else if (type == 'E')
		tile->type = 3;

	return (tile);
}

t_tile	**make_board(t_data *d, char *input, int size)
{
	t_tile		**tiles;
	t_coords	bc;
	int			pos;
	int			i;

	tiles = calloc(size, sizeof(t_tile *));
	bc.y = 0;
	i = 0;
	while (input[i])
	{
		bc.x = 0;
		while (input[i] && input[i] != '\n')
		{
			if (input[i] == 'P')
				d->p = initiate_player(bc);
			tiles[pos] = make_tile(input[i], bc);
			pos++;
			bc.x++;
			i++;
		}
		d->board_s += bc.x;
		if (d->max_bx == 0)
			d->max_bx = bc.x;
		bc.y++;
		if (input[i] == '\n')
			i++;
	}
	if (d->max_by == 0)
		d->max_by = bc.y;
	return (tiles);
}