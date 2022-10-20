/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/20 15:02:41 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//puts the player on the board
static t_entity	*initiate_player(t_data *d, t_coords *pc)
{
	t_entity	*player;

	pc->x = 1;	//hardcoded for now
	pc->y = 1;

	player = calloc(2, sizeof(t_entity));
	player->image = mlx_texture_to_image(d->window, mlx_load_png("./Assets/Misc/Ball.png"));
	player->bc = pc;
	player->info = 0;

	return (player);
}

//puts harcoded data into the d struct (prints the board)
void initiate_data(t_data *d, t_coords *pc)
{
	d = calloc(2, sizeof(t_data));

	d->max_wx = 2048;	//window width				ALL HARDCODED FOR NOW
	d->max_wy = 1024;	//window height
	d->window = mlx_init(d->max_wx, d->max_wy, "Test Window", true);	//the window itself

	d->max_bx = 16;	//board width
	d->max_by = 32;	//board height
	d->tiles = NULL;

	d->asset_s = 64;	//asset resolution (static)
	d->p = initiate_player(d, pc);
}

void	initiate_window(t_data *d)
{
	mlx_image_t	*image;

	image = mlx_new_image(d->window, d->max_wx, d->max_wy);
	memset(image->pixels, 128, image->width * image->height * sizeof(int32_t));
	mlx_image_to_window(d->window, image, 0, 0);
	mlx_image_to_window(d->window, mlx_texture_to_image(d->window, mlx_load_png("./Assets/Misc/Tittle.png")), 0, 0); //MOVE ME
}
