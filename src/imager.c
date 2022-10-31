/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imager.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/31 13:26:14 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//draws an image on the window
void	move_image(mlx_image_t *image, int x, int y)
{
	image->instances[0].x = x;
	image->instances[0].y = y;
}

mlx_image_t	*put_image(t_data *d, t_coords *bc, int	id, int	z)
{
	t_coords	wc;

	wc.x = find_wx(bc, d);
	wc.y = find_wy(bc, d) - (z * d->asset_s / 8);
	mlx_image_to_window(d->window, d->assets[id], wc.x, wc.y);
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
mlx_image_t **load_assets(t_data *d)
{
	mlx_image_t	**assets;

	assets = ft_calloc(d->asset_n, sizeof(mlx_image_t *));
	assets[0] = make_image(d, "./Assets/XPM/TileFloor.xpm42");
	assets[1] = make_image(d, "./Assets/XPM/Slab.xpm42");
	assets[2] = make_image(d, "./Assets/XPM/FlagWhite.xpm42");
	assets[3] = make_image(d, "./Assets/XPM/Hole.xpm42");
	assets[4] = make_image(d, "./Assets/XPM/Ball.xpm42");
	assets[5] = make_image(d, "./Assets/XPM/Cube.xpm42");
	assets[6] = make_image(d, "./Assets/XPM/Tittle.xpm42");
	assets[7] = NULL;
	return (assets);
}