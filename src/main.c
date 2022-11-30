/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/30 14:40:15 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//game loop for a given attempt
static void	play_map(t_meta *md)
{
	t_data	d;

	printf("\n   LAUNCHING LEVEL %i\n", md->lvl_c + 1);
	printf("\n   Difficulty  :  %i/8", md->difficulty);
	printf("\n   Instability :  %i/8", md->instability);
	printf("\n   Attempt     :  %i", md->try_c + 1);
	printf("\n   Lives       :  %i\n\n", md->lives);
	initiate_level(&d, md);
	if (STATE_NULL <= md->state && md->state != STATE_CLOSING)
	{
		md->try_c++;
		mlx_key_hook(d.window, &key_hook, &d);
		mlx_loop_hook(d.window, &hook, &d);
		mlx_loop(d.window);
		md->mv_c += d.mv_c;
	}
	print_level_end(&d);
	free_level(&d);
}

//starting point of this program
int	main(int argc, char **argv)
{
	t_meta	md;

	srand(time(&md.time));
	initiate_game(&md, --argc, ++argv);
	while (STATE_NULL < md.state && md.state != STATE_CLOSING \
		&& md.lvl_c < md.lvl_n && 0 < md.lives)
	{
		play_map(&md);
		if (md.state == STATE_DYING)
			md.lives--;
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
