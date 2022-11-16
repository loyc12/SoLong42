/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/16 12:57:34 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//prints messages at the end of a level
void	print_level_end(t_data *d)
{
	if (d->md->state < 0)
		printf("\n  Unable to properly load the game board\n");
	if (d->md->state == 0)
		printf("\n  I played this shitty game and all I got was this lousy message...\n");
	else if (d->md->state == 1)
		printf("\n  How did you get here anyways?\n");
	else if (d->md->state == 2)
		printf("\n  Finished level %i in %i moves after %i tries!\n", d->md->lvl_c + 1, d->mv_c, d->md->try_c);
	else if (d->md->state == 3)
		printf("\n  You got got sonny... Better luck next time!\n");
}

//prints messages a the end of the game
void	print_game_end(t_meta *md)
{
	if (md->state < 0)
		printf("\n  Your map is bad and you should FEEL bad...\n\n");
	else if (md->state == 0)
		printf("\n  Didn't think you'd be a such a quitter...\n\n");
	else if (md->state == 1)
		printf("\n  Save-scumming I see...\n\n");
	else if (md->state == 2)
		printf("\n  CONGRATULATIONS!!! You completed the %i levels in %i moves and %i retries!\n\n", md->lvl_n, md->mv_c, md->try_n - md->lvl_n);
	else if (md->state == 3)
		printf("\n  R.I.P. Next time maybe try avoiding those...\n\n");
}
