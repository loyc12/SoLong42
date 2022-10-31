/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/31 12:34:12 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//initialises the d struct
void initiate_data(t_data *d)
{
	d->max_wx = 1024;	//window width				//hardcoded for now
	d->max_wy = 512;	//window height				//hardcoded for now
	d->window = mlx_init(d->max_wx, d->max_wy, "Test Window", true);	//the window itself

	d->tiles = load_board(d, "1111111\n1000001\n10P0001\n100C001\n1000E01\n1000001\n1111111", 49);	//hardcoded for now
	connect_tiles(d);

	d->asset_s = 64;	//asset resolution (static)
	d->asset_n = 8;		//number of assets (static)
	d->assets = load_assets(d);
	
} 

//initialises the window
void	initiate_window(t_data *d)
{
	mlx_image_t	*background;

	background = mlx_new_image(d->window, d->max_wx, d->max_wy);
	memset(background->pixels, 128, background->width * background->height * sizeof(int32_t));
	mlx_image_to_window(d->window, background, 0, 0);
	d->assets[7] = background;
	
	mlx_image_to_window(d->window, d->assets[6], 0, 0); //MOVE ME
}
