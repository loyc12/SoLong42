/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/26 12:35:08 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//gcc -Werror -Wextra -Wall ./src/* ./libs/MLX42/libmlx42.a -I include -lglfw -L "/Users/$USER/.brew/opt/glfw/lib/"

static void	free_all(t_data *d)
{
	int		i;

	i = -1;
	while (++i < d->board_s)
	{
		free(d->tiles[i]->bc);
		free(d->tiles[i]);
	}
	free(d->tiles);
	free(d->window);
}

static void	hook(void *param)
{
	t_data	*d;

	d = param;
	if (!d->updated)
	{
	if (mlx_is_key_down(d->window, MLX_KEY_ESCAPE))
		mlx_close_window(d->window);
	if (mlx_is_key_down(d->window, MLX_KEY_W))
		move_player(d, find_tile(d->pc, d), 'N');
	if (mlx_is_key_down(d->window, MLX_KEY_D))
		move_player(d, find_tile(d->pc, d), 'E');
	if (mlx_is_key_down(d->window, MLX_KEY_S))
		move_player(d, find_tile(d->pc, d), 'S');
	if (mlx_is_key_down(d->window, MLX_KEY_A))
		move_player(d, find_tile(d->pc, d), 'W');
	}
	else
		draw_board(d);
	usleep(50000);
}

int	main(void)
{
	t_data	d;	//CHANGER LES CALLOC EN FT_CALLOC
				//METTRE LES FICHIERS DANS MAKEFILE
	
	initiate_data(&d);
	initiate_window(&d);
	if (!(d.window))
		exit(EXIT_FAILURE);
	draw_board(&d);
	mlx_loop_hook(d.window, &hook, &d);
	mlx_loop(d.window);
    mlx_terminate(d.window);
	free_all(&d);
	return (EXIT_SUCCESS);
}
