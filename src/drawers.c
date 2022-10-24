/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/24 14:42:03 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//draws an image
void	put_image(t_coords *bc, t_data *d, char *path)
{
	mlx_image_t *image;
	t_coords 	wc;

	wc.x = find_wx(bc, d);
	wc.y = find_wy(bc, d);
	image = mlx_texture_to_image(d->window, mlx_load_png(path));	
	mlx_image_to_window(d->window, image, wc.x, wc.y);
}

static void	render_floor(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		put_image(tile->bc, d, "./Assets/Misc/TileFloor.png");
	}
}

static void	render_object(t_data *d, int i)
{
	t_tile	*tile;

	tile = d->tiles[i];
	if (tile->type == 0)
		return ;
	else if (tile->type == 1 && (tile->bc->x == 0 || tile->bc->y == 0))
		put_image(tile->bc, d, "./Assets/Cubes/Cube.png");
	else if (tile->type == 1 && tile->bc->x != 0 && tile->bc->x != 0)
		put_image(tile->bc, d, "./Assets/Slabs/Slab.png");
	else if (tile->type == 2)
		put_image(tile->bc, d, "./Assets/Doors&Keys/FlagWhite.png");
	else if (tile->type == 3)
		put_image(tile->bc, d, "./Assets/Misc/Hole.png");
	else if (tile->type == 4)
		put_image(tile->bc, d, "./Assets/Misc/Ball.png");
}

// draws a dynamic board
void	draw_board(t_data *d)
{
	t_tile	*tile;
	int		i;

	render_floor(d);
	i = -1;
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		render_object(d, i);
	}
}
