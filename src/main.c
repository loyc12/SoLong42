/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/14 16:11:01 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//gcc -Werror -Wextra -Wall ./src/* ./libs/MLX42/libmlx42.a -I include -lglfw -L "/Users/$USER/.brew/opt/glfw/lib/"

static void	play_map(t_meta *md)
{
	t_data	d;

	printf("\n  Launching level %i\n", md->lvl + 1);
	initiate_data(&d, md);
	printf("\n  State : %i\n  Difficulty : %i/8\n\n", md->state, md->difficulty);
	if (0 <= md->state)
	{
		draw_board(&d);
		mlx_key_hook(d.window, &key_hook, &d);
		mlx_loop_hook(d.window, &hook, &d);
		mlx_loop(d.window);
		md->mv += d.flag_m;
	}
	print_level_end(&d);
	free_level(&d);
}

int	main(void) //METTRE LES NOMS DES FICHIERS DANS MAKEFILE
{

	t_meta	md;

	md.state = 1;			//default value
	
	srand(time(&md.time));
	initiate_levels(&md);
	while (0 < md.state && md.lvl < md.max_lvl)
	{
		play_map(&md);
		if (md.state == 2)
			md.lvl++;
	}
	print_game_end(&md);
	free_game(&md);

	return (EXIT_SUCCESS);
}
