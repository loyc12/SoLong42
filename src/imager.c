/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imager.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/02 15:52:27 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//draws an image on the window
void	move_image(mlx_image_t *image, int x, int y)
{
	image->instances[0].x = x;
	image->instances[0].y = y;
}

//draws an imaged on screen based on its coords and id
mlx_image_t	*put_image(t_data *d, t_coords *bc, int	id, int	z)
{
	t_coords	*wc;

	wc = bc_to_wc(d, bc);
	wc->y -= (z * d->asset_s / 8);
	mlx_image_to_window(d->window, d->assets[id], wc->x, wc->y);
	free(wc);
	return (d->assets[id]);
}

//initializes a single asset
static mlx_image_t	*make_image(t_data *d, char *path)
{
	mlx_image_t	*image;
	xpm_t		*xpm;

	xpm = mlx_load_xpm42(path);
	image = ft_calloc(1, sizeof(mlx_image_t));
	image = mlx_texture_to_image(d->window, &xpm->texture);
	return (image);
}

//loads all the needed assets
mlx_image_t	**load_assets(t_data *d)
{
	mlx_image_t	**assets;

	assets = ft_calloc(d->asset_n, sizeof(mlx_image_t *));
	assets[0] = make_image(d, "./Assets/XPM/TileFloor.xpm42");
	assets[1] = make_image(d, "./Assets/XPM/Slab.xpm42");
	assets[2] = make_image(d, "./Assets/XPM/Cube.xpm42");

	if (d->flag_n > 0)
		assets[3] = make_image(d, "./Assets/XPM/BlockedHole.xpm42");
	else 
		assets[3] = make_image(d, "./Assets/XPM/Hole.xpm42");
	if (d->pc != d->ec)
		assets[4] = make_image(d, "./Assets/XPM/Ball.xpm42");
	else
		assets[4] = make_image(d, "./Assets/XPM/HalfBall.xpm42");

	assets[5] = make_image(d, "./Assets/XPM/FlagWhite.xpm42");
	assets[6] = make_image(d, "./Assets/XPM/Tittle.xpm42");
	return (assets);
}

//frees the memory allocated to previously used assets
void	clean_assets(t_data *d)
{
	int	i;

	i = -1;
	if (d->flag_c)
		while (++i < d->asset_n)
			mlx_delete_image(d->window, d->old[i]);
	d->flag_c = 0;
	free(d->old);
	d->old = NULL;
}