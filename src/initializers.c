/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/24 14:27:35 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_coords	*clone_coords(t_coords c1)
{
	t_coords	*c2;
	
	c2 = calloc(1, sizeof(t_coords));
	c2->x = c1.x;
	c2->y = c1.y;
	return (c2);
}

//puts harcoded data into the d struct (prints the board)
void initiate_data(t_data *d)
{
	d->max_wx = 1024;	//window width				//hardcoded for now
	d->max_wy = 512;	//window height				//hardcoded for now
	d->window = mlx_init(d->max_wx, d->max_wy, "Test Window", true);	//the window itself

	d->tiles = make_board(d, "1111111\n1P00001\n100C101\n10001C1\n10E0001\n1111111", 42);	//hardcoded for now
	connect_tiles(d);

	d->asset_s = 64;	//asset resolution (static)
} 

void	initiate_window(t_data *d)
{
	mlx_image_t	*image;

	image = mlx_new_image(d->window, d->max_wx, d->max_wy);
	memset(image->pixels, 128, image->width * image->height * sizeof(int32_t));
	mlx_image_to_window(d->window, image, 0, 0);
	mlx_image_to_window(d->window, mlx_texture_to_image(d->window, mlx_load_png("./Assets/Misc/Tittle.png")), 0, 0); //MOVE ME
}
