/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/17 10:03:27 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//gcc -Werror -Wextra -Wall ./src/* ./libs/libmlx42.a -I include -lglfw -L "/Users/$USER/.brew/opt/glfw/lib/"

int	main(void)
{
	t_data		d;
	t_entity	p;
	
	initiate_data(&d);
	initiate_player(&d, &p);
	initiate_window(&d);

	//draws a plane of squares
	draw_static_board(&d);

	//displays the end (hole)
	put_end(6, 9, &d);		//hardocded (temp)

	//displays the player (ball)
	put_entity(&d, &p);

	mlx_loop(d.window);
    mlx_terminate(d.window);

	return (0);
}
