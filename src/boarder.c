/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boarder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/02 14:03:04 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//finds the number of tiles in a given string
static int	find_tile_number(char *input)
{
	int	len;
	int	i;

	i = -1;
	len = 0;

	while (input[++i])
		if (input[i] != '\n')
			len++;
	return (len);
}

//creates a single tile from its given type and coordinates
static t_tile	*make_tile(t_data *d, t_coords bc, char type)
{
	t_tile		*tile;

	tile = ft_calloc(1, sizeof(t_tile));
	tile->bc = clone_coords(bc);
	tile->north = NULL;
	tile->east = NULL;
	tile->south = NULL;
	tile->west = NULL;
	tile->type = 0;
	if (type == '1')
		tile->type = 1;
	else if (type == 'C')
	{
		tile->type = 2;
		d->flag_n += 1;
	}
	else if (type == 'E')
	{
		tile->type = 3;
		d->ec = tile->bc;
	}
	else if (type == 'P')
	{
		tile->type = 4;
		d->pc = tile->bc;
	}
	return (tile);
}

//converts the inputed string into a tile array if it is valid
t_tile	**load_board(t_data *d, char *input)
{
	t_tile		**tiles;
	t_coords	bc;
	int			pos;
	int			i;

	if (is_valid(input))
		printf("Input has he require objects!\n\n");			// REMOVE ME
	tiles = ft_calloc(find_tile_number(input), sizeof(t_tile *));
	bc.y = 0;
	i = 0;
	pos = 0;
	while (input[i])
	{
		bc.x = 0;
		while (input[i] && input[i] != '\n')
		{
			tiles[pos++] = make_tile(d, bc, input[i++]);
			d->board_s++;
			bc.x++;
		}
		bc.y++;
		if (input[i] == '\n')
			i++;
	}
	d->max_by = bc.y;
	d->max_bx = bc.x;
	return (tiles);
}