/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/28 11:22:42 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//game loop for a given level
static void	play_map(t_meta *md)
{
	t_data	d;

	printf("\n  LAUNCHING LEVEL %i\n\n  Difficulty : %i/8\n  Attempt : %i\n\n", md->lvl_c + 1, md->difficulty, md->try_c + 1);	//REMOVE ME
	//printf("Board : \n\n%s\n", md->levels[md->lvl_c]);																		//REMOVE ME
	initiate_data(&d, md);
	md->try_c++;
	if (STATE_CLOSING <= md->state)
	{
		draw_board(&d);
		mlx_key_hook(d.window, &key_hook, &d);
		mlx_loop_hook(d.window, &hook, &d);
		mlx_loop(d.window);
		md->mv_c += d.mv_c;
	}
	print_level_end(&d);
	free_level(&d);
}

//gcc -Werror -Wextra -Wall ./src/* ./libs/MLX42/libmlx42.a -I include -lglfw -L "/Users/$USER/.brew/opt/glfw/lib/"				//REMOVE ME

int	main(int argc, char **argv) //METTRE LES NOMS DES FICHIERS DANS MAKEFILE
{
	t_meta	md;
	
	srand(time(&md.time));
	initiate_levels(&md, --argc, ++argv);
	while (0 < md.state && md.lvl_c < md.lvl_n)
	{
		play_map(&md);
		if (md.state == 2)
		{
			md.lvl_c++;
			md.try_n += md.try_c;
			md.try_c = 0;
		}
	}
	print_game_end(&md);
	free_game(&md);

	return (EXIT_SUCCESS);
}
