/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/05/04 10:20:22 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 1024
#define HEIGHT 1024

mlx_image_t	*face;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;

	if (mlx_is_key_down(param, MLX_KEY_ESCAPE) || mlx_is_key_down(param, MLX_KEY_Q))
		mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_UP) || mlx_is_key_down(param, MLX_KEY_W))
		face->instances[0].y -= 5;
	if (mlx_is_key_down(param, MLX_KEY_DOWN) || mlx_is_key_down(param, MLX_KEY_S))
		face->instances[0].y += 5;
	if (mlx_is_key_down(param, MLX_KEY_LEFT) || mlx_is_key_down(param, MLX_KEY_A))
		face->instances[0].x -= 5;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT) || mlx_is_key_down(param, MLX_KEY_D))
		face->instances[0].x += 5;
}

int32_t	main(void)
{
	mlx_t	*mlx;

	//		initializing the mlx window
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);

	//		face square causes leaks
	xpm_t	*xpm;
	xpm = mlx_load_xpm42("./assets/XPM/dumbass.xpm42");
	face = mlx_texture_to_image(mlx, &xpm->texture);
	mlx_delete_xpm42(xpm);

	//		white square does not cause leaks
	//face = mlx_new_image(mlx, 128, 128);
	//memset(face->pixels, 255, face->width * face->height * sizeof(int));

	//		drawing the image on the window
	mlx_image_to_window(mlx, face, 0, 0);

	//staying in these two loops until window is closed
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);

	//		presence of delete_image does not solve the leak
	mlx_delete_image(mlx, face);

	//		additional free crashes the program
	//free(face);

	//		properly closing the window
	mlx_terminate(mlx);

	return (EXIT_SUCCESS);
}
