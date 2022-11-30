/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imagers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/30 12:52:41 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//draws an imaged on screen based on its coords and id
mlx_image_t	*put_image(t_data *d, t_coords *bc, int id, int z)
{
	t_coords	*wc;

	wc = bc_to_wc(d, bc);
	wc->y -= (z * d->asset_s / 8);
	if (is_in_window(d, wc))
		mlx_image_to_window(d->window, d->assets[id], wc->x, wc->y);
	free(wc);
	return (d->assets[id]);
}

//initializes a single asset
mlx_image_t	*make_image(t_data *d, char *path)
{
	mlx_image_t	*image;
	xpm_t		*xpm;

	xpm = mlx_load_xpm42(path);
	image = mlx_texture_to_image(d->window, &xpm->texture);
	return (image);
}

//loads all the needed assets
void	load_assets(t_data *d)
{
	mlx_image_t	**assets;

	assets = ft_calloc(d->asset_n, sizeof(mlx_image_t *));
	assets[ID_FLOOR] = make_image(d, "./assets/XPM/TileFloor.xpm42");
	assets[ID_SLAB] = make_image(d, "./assets/XPM/Slab.xpm42");
	assets[ID_CUBE] = make_image(d, "./assets/XPM/Cube.xpm42");
	if (0 < d->flg_c)
		assets[ID_HOLE] = make_image(d, "./assets/XPM/BlockedHole.xpm42");
	else
		assets[ID_HOLE] = make_image(d, "./assets/XPM/Hole.xpm42");
	if (0 < d->flg_c || d->pc != d->ec)
		assets[ID_BALL] = make_image(d, "./assets/XPM/Ball.xpm42");
	else
		assets[ID_BALL] = make_image(d, "./assets/XPM/HalfBall.xpm42");
	assets[ID_FLAG] = make_image(d, "./assets/XPM/FlagWhite.xpm42");
	assets[ID_CONE] = make_image(d, "./assets/XPM/CONE.xpm42");
	d->assets = assets;
}

//frees the memory allocated to previously used assets
void	clean_old_assets(t_data *d)
{
	int	i;

	i = -1;
	if (d->c_flag)
		while (++i < d->asset_n)
			mlx_delete_image(d->window, d->old[i]);
	d->c_flag = 0;
	free(d->old);
	d->old = NULL;
}
