/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/26 12:32:24 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//draws an image
mlx_image_t	*put_image(t_coords *bc, t_data *d, char *path)
{
	mlx_image_t *image;
	xpm_t		*xpm;
	t_coords 	wc;

	wc.x = find_wx(bc, d);
	wc.y = find_wy(bc, d);
	xpm = mlx_load_xpm42(path);
	image = mlx_texture_to_image(d->window, &xpm->texture);
	mlx_image_to_window(d->window, image, wc.x, wc.y);
	return (image);
}

static void	render_floor(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		if (!tile->floor)
			tile->floor = put_image(tile->bc, d, "./Assets/XPM/TileFloor.xpm42");
	}
}

static void	render_object(t_data *d, t_tile *tile)
{
	if (tile->object && tile->bc->x && tile->bc->y)
			mlx_delete_image(d->window, tile->object);
	if (tile->type == 1)
	{
		if (!tile->object && (tile->bc->x == 0 || tile->bc->y == 0))
			tile->object = put_image(tile->bc, d, "./Assets/XPM/Cube.xpm42");
		else if (tile->bc->x && tile->bc->y)
			tile->object = put_image(tile->bc, d, "./Assets/XPM/Slab.xpm42");
	}
	if (0 < tile->type)
	{
		if (tile->type == 2)
			tile->object = put_image(tile->bc, d, "./Assets/XPM/FlagWhite.xpm42");
		else if (tile->type == 3)
			tile->object = put_image(tile->bc, d, "./Assets/XPM/Hole.xpm42");
		else if (tile->type == 4)
		{
			printf("player rendered at: %i,%i\n", tile->bc->x, tile->bc->y);		//REMOVE ME
			tile->object = put_image(tile->bc, d, "./Assets/XPM/Ball.xpm42");
		}
	}
}

// draws a dynamic board
void	draw_board(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	render_floor(d);
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		render_object(d, tile);
	}
	d->updated = 0;
}
