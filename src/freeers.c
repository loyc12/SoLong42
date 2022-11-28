/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/28 08:53:09 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//static void	free_tile;

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
	if (-1 < d->md->state)
	{
		i = -1;
		while (++i < d->asset_n)
			if (d->assets[i])
				mlx_delete_image(d->window, d->assets[i]);
		mlx_delete_image(d->window, d->tittle);
		mlx_terminate(d->window);
	}
	if (-2 < d->md->state)
	{
		free(d->tiles);
		free(d->assets);
		free(d->enemies);
	}
}

void	free_game(t_meta *md)
{
	int i;
	
	printf("\nlol\n\n");
	
	i = -1;
	while (++i < md->lvl_c)
		free(md->levels[i]);
	free(md->levels);
}
