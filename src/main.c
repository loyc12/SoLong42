/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/08 11:14:51 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//gcc -Werror -Wextra -Wall ./src/* ./libs/MLX42/libmlx42.a -I include -lglfw -L "/Users/$USER/.brew/opt/glfw/lib/"

static void	solve(t_data *d)
{
	t_tile	*tile;

	tile = find_tile(d, d->pc);
	if (tile->north && tile->north->flag_f < tile->flag_f)
		move_player(d, tile, 'N');
	else if (tile->east && tile->east->flag_f < tile->flag_f)
		move_player(d, tile, 'E');
	else if (tile->south && tile->south->flag_f < tile->flag_f)
		move_player(d, tile, 'S');
	else if (tile->west && tile->west->flag_f < tile->flag_f)
		move_player(d, tile, 'W');
	else
		printf("ai doesn't know where to move...\n");
}

//frees all the leftover data
static void	free_all(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		if (tile->object)
			mlx_delete_image(d->window, tile->object);
		if (tile->floor)
			mlx_delete_image(d->window, tile->floor);
		free(tile->bc);
		free(tile);
	}
	free(d->tiles);
	i = -1;
	while (++i < d->asset_n)
		if (d->assets[i])
			mlx_delete_image(d->window, d->assets[i]);
	free(d->assets);
	mlx_delete_image(d->window, d->tittle);
}

static void	hook(void *param)
{
	t_data	*d;

	d = param;
	if (mlx_is_key_down(d->window, MLX_KEY_ESCAPE))
		mlx_close_window(d->window);
	if (d->flag_r)
		draw_board(d);
	if (mlx_is_key_down(d->window, MLX_KEY_Q))
		solve(d);
}

//key hook used during the main loop
static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*d;

	d = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W)
			move_player(d, find_tile(d, d->pc), 'N');
		if (keydata.key == MLX_KEY_D)
			move_player(d, find_tile(d, d->pc), 'E');
		if (keydata.key == MLX_KEY_S)
			move_player(d, find_tile(d, d->pc), 'S');
		if (keydata.key == MLX_KEY_A)
			move_player(d, find_tile(d, d->pc), 'W');
	}
}

int	main(void) //METTRE LES NOMS DES FICHIERS DANS MAKEFILE
{
	t_data	d;
	
	initiate_data(&d);
	draw_board(&d);
	mlx_key_hook(d.window, &key_hook, &d);
	mlx_loop_hook(d.window, &hook, &d);
	mlx_loop(d.window);
	free_all(&d);
    mlx_terminate(d.window);
	return (EXIT_SUCCESS);
}
