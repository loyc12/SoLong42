/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/24 10:16:30 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//puts the player on the board
t_entity	*initiate_player(t_coords bc)
{
	t_entity	*player;
	t_coords	*pc;

	player = calloc(1, sizeof(t_entity));
	pc = calloc(1, sizeof(t_coords));
	pc->x = bc.x;
	pc->y = bc.y;
	player->bc = pc;
	player->info = 0;

	return (player);
}

//puts harcoded data into the d struct (prints the board)
void initiate_data(t_data *d)
{
	d->max_wx = 1024;	//window width				//hardcoded for now
	d->max_wy = 512;	//window height				//hardcoded for now
	d->window = mlx_init(d->max_wx, d->max_wy, "Test Window", true);	//the window itself

	d->max_bx = 0;		//board width
	d->max_by = 0;		//board height
	d->tiles = make_board(d, "P0C\n010\n0E0", 9);	//hardcoded for now

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
