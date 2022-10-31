/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/31 13:35:58 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//renders all the tile floors
static void	render_floor(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		if (i == 0)
			tile->floor = put_image(d, tile->bc, 0, 4);
		tile->floor = put_image(d, tile->bc, 0, 0);
	}
}

//renders all the tile objects
static void	render_object(t_data *d, t_tile *tile)
{
	if (tile->type == 1)
	{
		if (tile->bc->x == 0 || tile->bc->y == 0)
			tile->object = put_image(d, tile->bc, 5, 0);
		else if (tile->bc->x && tile->bc->y)
			tile->object = put_image(d, tile->bc, 1, 0);
	}
	else if (tile->type == 2)
		tile->object = put_image(d, tile->bc, 2, 0);
	else if (tile->type == 3)
		tile->object = put_image(d, tile->bc, 3, 0);
	else if (tile->type == 4)
	{
		tile->object = put_image(d, tile->bc, 4, 0);
		d->player = tile->object;
	}
}

//updates the needed tile object images
static void	re_render_object(t_data *d, t_tile *tile)
{
	int	wx;
	int	wy;

	wx = find_wx(tile->bc, d);
	wy = find_wy(tile->bc, d);
	if (tile->type == 4)
	{
		tile->object = d->player;
		move_image(d->player, wx, wy);
	}
	if (tile->type != 0)
		mlx_image_to_window(d->window, tile->object, wx, wy);
}

//(re)renders the entire board
void	draw_board(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	render_floor(d);
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		if (!tile->object)
			render_object(d, tile);
		else
			re_render_object(d, tile);
	}
	d->updated = 0;
}
