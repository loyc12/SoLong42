/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/29 17:03:01 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//game loop for a given attempt
static void	play_map(t_meta *md)
{
	t_data	d;

	printf("\n  LAUNCHING LEVEL %i\n\n  Difficulty : %i/8\n  Attempt : %i\
	\n\n", md->lvl_c + 1, md->difficulty, md->try_c + 1);
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


//starting point of this program
int	main(int argc, char **argv) 							//FIX HEADER NORM
{
	t_meta	md;

	srand(time(&md.time));
	initiate_levels(&md, --argc, ++argv);
	while (STATE_CLOSING < md.state && md.lvl_c < md.lvl_n)
	{
		play_map(&md);
		if (md.state == STATE_SUCCEEDING)
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
