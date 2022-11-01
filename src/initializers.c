/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/01 11:00:27 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//initialises the d struct
void initiate_data(t_data *d)
{
	d->flag_n = 0;		//flags to collect				(uninitialized)
	d->updated = 0;		//graphic update flag

	d->max_wx = 1024;	//window width					(constant)
	d->max_wy = 512;	//window height					(constant)
	d->window = mlx_init(d->max_wx, d->max_wy, "So Round", true);	//the window itself

	d->max_bx = 0;		//board width					(uninitialized)
	d->max_by = 0;		//board height					(uninitialized)
	d->board_s = 0;		//tile amount					(uninitialized)
	d->tiles = load_board(d, "1111111\n1000001\n10P0001\n100C001\n1000E01\n1000001\n1111111", 49);	// CHANGE ME
	connect_tiles(d);

	d->asset_s = 64;	//asset resolution				(constant)
	d->asset_n = 10;	//number of assets				(constant)
	d->assets = load_assets(d);

	d->end = d->assets[3];		//3 = end asset id
	d->player = d->assets[4];	//4 = player asset id
} 

//initialises the window
void	initiate_window(t_data *d)
{
	mlx_image_t	*background;

	background = mlx_new_image(d->window, d->max_wx, d->max_wy);
	memset(background->pixels, 128, background->width * background->height * sizeof(int32_t));
	mlx_image_to_window(d->window, background, 0, 0);
	d->assets[9] = background;
	
	mlx_image_to_window(d->window, d->assets[6], 0, 0);
}
