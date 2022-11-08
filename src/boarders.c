/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boarders.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/08 13:06:50 by llord            ###   ########.fr       */
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

static void	set_default_tile_values(t_tile *tile)
{
	tile->north = NULL;
	tile->east = NULL;
	tile->south = NULL;
	tile->west = NULL;
	tile->type = TYPE_EMPTY;
	tile->flag_f = 0;
	tile->flag_e = 0;
}

//creates a single tile from its given type and coordinates
static t_tile	*make_tile(t_data *d, t_coords *bc, char type)
{
	t_tile		*tile;

	tile = ft_calloc(1, sizeof(t_tile));
	tile->bc = clone_coords(*bc);
	set_default_tile_values(tile);
	if (type == '1')
		tile->type = TYPE_WALL;
	else if (type == 'P')
	{
		tile->type = TYPE_PLAYER;
		d->pc = tile->bc;
	}
	else if (type == 'E')
	{
		tile->type = TYPE_END;
		d->ec = tile->bc;
	}
	else if (type == 'C')
	{
		tile->type = TYPE_FLAG;
		d->flag_n += 1;
	}
	return (tile);
}

static void	loop_on_tiles(t_data *d, t_coords *bc, char *input)
{
	int		pos;
	int		i;

	i = 0;
	pos = 0;
	bc->y = 0;
	while (input[i])
	{
		bc->x = 0;
		while (input[i] && input[i] != '\n')
		{
			d->tiles[pos++] = make_tile(d, bc, input[i++]);
			bc->x++;
		}
		bc->y++;
		while (input[i] == '\n')
			i++;
	}
}

//converts the inputed string into a tile array if it is valid
void	load_board(t_data *d, char *input)
{
	t_tile		**tiles;
	t_coords	bc;

	if (is_input_valid(input) && is_grid_valid(input))
		printf("input has been validated!\n");							// REMOVE ME

	tiles = ft_calloc(find_tile_number(input), sizeof(t_tile *));
	d->tiles = tiles;
	loop_on_tiles(d, &bc, input);
	d->max_by = bc.y - 1;
	d->max_bx = bc.x - 1;
	d->board_s = bc.x * bc.y;
	connect_grid(d);

}