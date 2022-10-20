/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/20 15:58:24 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//gcc -Werror -Wextra -Wall ./src/* ./libs/libmlx42.a -I include -lglfw -L "/Users/$USER/.brew/opt/glfw/lib/"

int	main(void)
{
	t_data		d;
	t_coords	pc;
	
	make_board("11111\n1P0?1\n10001\n100E1\n11111", 29);
	initiate_data(&d, &pc);
	initiate_window(&d);
	draw_board(&d);

	mlx_loop(d.window);
    mlx_terminate(d.window);

	return (0);
}
