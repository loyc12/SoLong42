/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/24 14:46:43 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//gcc -Werror -Wextra -Wall ./src/* ./libs/MLX42/libmlx42.a -I include -lglfw -L "/Users/$USER/.brew/opt/glfw/lib/"

int	main(void)
{
	t_data		d;	//CHANGER LES CALLOC EN FT_CALLOC
	
	initiate_data(&d);
	initiate_window(&d);
	
	draw_board(&d);
	//mlx_loop_hook(d.window, hook, d.window);
	mlx_loop(d.window);
    mlx_terminate(d.window);

	return (0);
}
