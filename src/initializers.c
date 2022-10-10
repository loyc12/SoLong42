/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/10 15:30:15 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	initiate_data(t_data *d)
{
	d->window_x = 2048;	//window width				ALL HARDCODED FOR NOW
	d->window_y = 1024;	//window height
	d->window = mlx_init(d->window_x, d->window_y, "Test Window", true);	//the window itself

	d->board_x = 16;	//board width
	d->board_y = 24;	//board height
	//d->board ...

	d->x_offset = 0;	//allow screen movement
	d->y_offset = 0;	//allow screen movement

	d->asset_size = 64;	//asset resolution (static)

	mlx_image_t	*image;
		
	image = mlx_new_image(d->window, d->window_x, d->window_y);
	memset(image->pixels, 128, image->width * image->height * sizeof(int32_t));
	mlx_image_to_window(d->window, image, 0, 0);
	mlx_image_to_window(d->window, mlx_texture_to_image(d->window, mlx_load_png("./Assets/Misc/Tittle.png")), 0, 0);
}

void	initiate_player(t_data *d, t_entity *p)
{

	p->image = mlx_texture_to_image(d->window, mlx_load_png("./Assets/Misc/Ball.png"));
	p->type = 1;
	p->bc->x = 4;	//hardocded (temp)
	p->bc->y = 2;	//hardocded (temp)
	p->bc->z = 0;	//hardocded (temp)
}
