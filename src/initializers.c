/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/26 12:38:53 by llord            ###   ########.fr       */
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

//static mlx_image_t(t_data *d)
//{
	
//}

//puts harcoded data into the d struct (prints the board)
void initiate_data(t_data *d)
{
	d->max_wx = 1024;	//window width				//hardcoded for now
	d->max_wy = 512;	//window height				//hardcoded for now
	d->window = mlx_init(d->max_wx, d->max_wy, "Test Window", true);	//the window itself

	d->tiles = make_board(d, "1111111\n1000001\n1000001\n100P001\n1000001\n1000001\n1111111", 49);	//hardcoded for now
	connect_tiles(d);

	//d->atlas = load_images(d);
	d->asset_s = 64;	//asset resolution (static)
} 

void	initiate_window(t_data *d)
{
	mlx_image_t	*image1;
	mlx_image_t	*image2;
	xpm_t		*xpm;

	image1 = mlx_new_image(d->window, d->max_wx, d->max_wy);
	memset(image1->pixels, 128, image1->width * image1->height * sizeof(int32_t));
	mlx_image_to_window(d->window, image1, 0, 0);
	
	xpm = mlx_load_xpm42("./Assets/XPM/Tittle.xpm42");
	image2 = mlx_texture_to_image(d->window, &xpm->texture);
	mlx_image_to_window(d->window, image2, 0, 0); //MOVE ME
}
