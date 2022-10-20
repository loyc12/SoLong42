/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/20 14:57:46 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//draws an image
void	put_image(t_coords *bc, t_data *d, char *path)
{
	mlx_image_t *image;
	t_coords 	wc;	//window coordinates

	wc.x = find_wx(bc, d);
	wc.y = find_wy(bc, d);
	image = mlx_texture_to_image(d->window, mlx_load_png(path));	
	mlx_image_to_window(d->window, image, wc.x, wc.y);
}

// draws a dynamic board
void	draw_board(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = 0;
	while (i++ != d->board_s)
	{
		tile = d->tiles[i];
		if (tile->type == '1')
			put_image(tile->bc, d, "./Assets/Slabs/Slab.png");
		else
			put_image(tile->bc, d, "./Assets/Misc/TileFloor.png");
		
		if (tile->type == 'E')
			put_image(tile->bc, d, "./Assets/Misc/Hole.png");
		else if (tile->type == '?')
			put_image(tile->bc, d, "./Assets/Misc/Ball.png");
		else if (tile->type == '2')
			put_image(tile->bc, d, "./Assets/Misc/HalfBall.png");
	}
}
