/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boarder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/07 12:12:24 by llord            ###   ########.fr       */
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
	tile->type = TYPE_EMPTY;
	tile->flag_f = 0;
	if (type == '1')
		tile->type = TYPE_WALL;
	else if (type == 'C')
	{
		tile->type = TYPE_FLAG;
		d->flag_n += 1;
	}
	else if (type == 'E')
	{
		tile->type = TYPE_END;
		d->ec = tile->bc;
	}
	else if (type == 'P')
	{
		tile->type = TYPE_PLAYER;
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

	if (is_input_valid(input))
		printf("\ninput has been validated!\n");						// REMOVE ME
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
			bc.x++;
		}
		bc.y++;
		while (input[i] == '\n')
			i++;
	}
	d->max_by = bc.y - 1;
	d->max_bx = bc.x - 1;
	d->board_s = bc.x * bc.y;
	return (tiles);
}