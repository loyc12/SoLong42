/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/07 13:47:37 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//renders all the tile floors + the end
static void	render_floor(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		if (i == 0)
			tile->floor = put_image(d, tile->bc, ID_FLOOR, 4);
		tile->floor = put_image(d, tile->bc, ID_FLOOR, 0);
	}
	find_tile(d->ec, d)->object = put_image(d, d->ec, ID_HOLE , 0);
}

//renders all the tile objects
static void	render_object(t_data *d, t_tile *tile)
{
	if (tile->type == TYPE_WALL)
	{
		if (tile->bc->x != 0 && tile->bc->y != 0)
			tile->object = put_image(d, tile->bc, ID_SLAB, 0);
		else
			tile->object = put_image(d, tile->bc, ID_CUBE , 0);
	}
	else if (tile->type == TYPE_PLAYER)
	{
		tile->object = put_image(d, tile->bc, ID_BALL, 0);
		if (d->pc == d->ec)
			d->flag_r = -1;											//GAME OVER FLAG
	}
	else if (tile->type == TYPE_FLAG)
		tile->object = put_image(d, tile->bc, ID_FLAG, 0);
}

//(re)renders the entire board
void	draw_board(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	clean_assets(d);
	if (!(d->window))
		exit(EXIT_FAILURE);
	d->old = d->assets;
	load_assets(d);
	render_floor(d);
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		render_object(d, tile);
	}
	d->flag_r = 0;
	d->flag_c = 1;

	usleep(50000);													//REMOVE ME (forbidden?)
}
