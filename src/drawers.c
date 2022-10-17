/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/17 10:07:50 by llord            ###   ########.fr       */
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

//draws the end
void	put_end(int bx, int by, t_data *d)
{
	mlx_image_t *image;
	t_coords 	bc;	//board coordinates
	t_coords 	wc;	//window coordinates

	bc.x = bx;
	bc.y = by;
	bc.z = 0;
	wc.x = find_wx(&bc, d);
	wc.y = find_wy(&bc, d);
	image = mlx_texture_to_image(d->window, mlx_load_png("./Assets/Misc/Hole.png"));	
	mlx_image_to_window(d->window, image, wc.x, wc.y);
}

void	put_entity(t_data *d, t_entity *e)
{
	int wx;	//window_x position
	int wy;	//window_y position

	wx = find_wx(e->bc, d);
	wy = find_wy(e->bc, d);
	mlx_image_to_window(d->window, e->image, wx, wy);
}

// draws a static board
void	draw_static_board(t_data *d)
{
	t_coords	bc;	//board coordinates
	int			wx;	//window x position
	int			wy;	//window y position

	bc.y = -1;
	bc.z = 0;
	while (++bc.y < d->max_by)
	{
	bc.x = -1;
		while (++bc.x < d->max_bx)
		{
			wx = find_wx(&bc, d);
			wy = find_wy(&bc, d);
			if (-d->asset_size < wx && wx < d->max_wx \
			&& -d->asset_size < wy && wy < d->max_wy)
			{
				if (bc.x * bc.y == 0 || bc.x + 1 == d->max_bx || bc.y + 1 == d->max_by)
					put_image(&bc, d, "./Assets/Slabs/Slab.png");
				else
					put_image(&bc, d, "./Assets/Misc/TileFloor.png");
			}
		}
	}
}
