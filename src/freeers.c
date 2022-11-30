/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/30 13:56:01 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//frees some leftover level data
static void	free_level_plus(t_data *d)
{
	int		i;

	if (STATE_ERR_MAP < d->md->state)
	{
		i = -1;
		while (++i < d->asset_n)
			if (d->assets[i])
				mlx_delete_image(d->window, d->assets[i]);
		free(d->assets);
		clean_old_assets(d);
		mlx_delete_image(d->window, d->tittle);
		mlx_terminate(d->window);
	}
	if (STATE_ERR_INPUT < d->md->state)
	{
		free(d->tiles);
		free(d->enemies);
	}
}

//frees all the leftover level data
void	free_level(t_data *d)
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
	free_level_plus(d);
}

//frees leftover game data
void	free_game(t_meta *md)
{
	int	i;

	i = -1;
	while (++i < md->lvl_n)
		free(md->levels[i]);
	free(md->levels);
}
