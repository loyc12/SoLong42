/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/14 16:09:38 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//prints messages at the end of a level
void	print_level_end(t_data *d)
{
	if (d->md->state < 0)
		printf("\n  Unable to properly load the game board\nClosing state : %i \n\n", d->md->state);
	if (d->md->state == 0)
		printf("\n  I played this shitty game and all I got was this lousy message...\n\n");
	else if (d->md->state == 1)
		printf("\n  How did you get here anyways?\n\n");
	else if (d->md->state == 2)
		printf("\n  Finished level %i in %i moves!\n\n", d->md->lvl + 1, d->flag_m);
	else if (d->md->state == 3)
		printf("\n  You got got sonny... Better luck next time!\n\n");
}

//prints messages a the end of the game
void	print_game_end(t_meta *md)
{
	if (md->state < 0)
		printf("\n  Your map is bad and you should FEEL bad...\n\n\n");
	else if (md->state == 0)
		printf("\n  Didn't think you'd be a quitter...\n\n\n");
	else if (md->state == 1)
		printf("\n  Save-scumming I see...\n\n\n");
	else if (md->state == 2)
		printf("\n  CONGRATULATION! You won in %i total moves\n\n\n", md->mv);
	else if (md->state == 3)
		printf("\n  R.I.P. Next time maybe try avoiding those...\n\n\n");
}
