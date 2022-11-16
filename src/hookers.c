/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/15 15:14:55 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//normal hook used during the game loop
void	hook(void *param)
{
	t_data	*d;

	d = param;
	if (d->m_flag)
		draw_board(d);
	if (mlx_is_key_down(d->window, MLX_KEY_Q))
		solve(d);
	if (mlx_is_key_down(d->window, MLX_KEY_E))
		d->md->state = 1;
	if (mlx_is_key_down(d->window, MLX_KEY_ESCAPE) || d->md->state != 0)
		mlx_close_window(d->window);
}

//key hook used during the game loop
void	key_hook(mlx_key_data_t keydata, void *param)
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
