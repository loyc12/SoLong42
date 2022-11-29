/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boarders.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/29 11:41:31 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//sets the default values of a tile (used during tile initialization)
static void	set_default_tile_values(t_tile *tile)
{
	tile->type = TYPE_EMPTY;
	tile->north = NULL;
	tile->east = NULL;
	tile->south = NULL;
	tile->west = NULL;
	tile->dst_f = 0;
	tile->dst_p = 0;
}

//creates a single tile from its given type and coordinates
static t_tile	*make_tile(t_data *d, t_coords *bc, char type, int *id)
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
		d->flg_c += 1;
	}
	else if (type == 'A')
	{
		tile->type = TYPE_ENEMY;
		d->enemies[(*id)++] = tile->bc;
	}
	return (tile);
}

//creates each tile base on the inputed string
static void	load_tiles(t_data *d, t_coords *bc, char *input)
{
	int		pos;
	int		id;
	int		i;

	i = 0;
	id = 0;
	pos = 0;
	bc->y = 0;
	while (input[i])
	{
		bc->x = 0;
		while (input[i] && input[i] != '\n')
		{
			d->tiles[pos++] = make_tile(d, bc, input[i++], &id);
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
	t_coords	*bc;

	bc = ft_calloc(1, sizeof(t_coords));
	if ((is_input_valid(input) && is_grid_valid(input)) || d->md->no_checks)
	{
		d->nm_n = find_enemy_number(input);
		d->enemies = ft_calloc(d->nm_n, sizeof(t_coords *));
		d->tiles = ft_calloc(find_tile_number(input), sizeof(t_tile *));
		load_tiles(d, bc, input);
		d->max_by = bc->y - 1;
		d->max_bx = bc->x - 1;
		d->board_s = bc->x * bc->y;
		connect_grid(d);
	}
	else
	{
		d->md->state = STATE_ERR_INPUT;
		d->board_s = 0;
	}
	free(bc);
}
