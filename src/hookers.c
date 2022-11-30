/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/30 14:35:29 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//normal hook used during the game loop
void	hook(void *param)
{
	t_data	*d;

	d = param;
	if (mlx_is_key_down(d->window, MLX_KEY_ESCAPE))
		d->md->state = STATE_CLOSING;
	else if (mlx_is_key_down(d->window, MLX_KEY_E))
		d->md->state = STATE_RETRYING;
	if (d->m_flag)
		draw_board(d);
	else if (mlx_is_key_down(d->window, MLX_KEY_Q))
		solve(d);
	if (d->md->state != STATE_NULL)
		mlx_close_window(d->window);
}

//key hook used during the game loop
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_tile	*src_tile;
	t_data	*d;

	d = param;
	if (d->md->state == STATE_NULL && \
		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		src_tile = find_tile(d, d->pc);
		if (keydata.key == MLX_KEY_W)
			move_player(d, src_tile->north);
		if (keydata.key == MLX_KEY_D)
			move_player(d, src_tile->east);
		if (keydata.key == MLX_KEY_S)
			move_player(d, src_tile->south);
		if (keydata.key == MLX_KEY_A)
			move_player(d, src_tile->west);
	}
}
