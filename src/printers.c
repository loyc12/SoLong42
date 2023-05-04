/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2023/05/04 10:22:07 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//prints messages at the end of a level
void	print_level_end(t_data *d)
{
	if (d->md->state <= STATE_NULL)
		printf("\n   ERROR\n\n   Unable to properly load the game board\n");
	else if (d->md->state == STATE_RETRYING)
		printf("\n   Save-scumming I see...\n");
	else if (d->md->state == STATE_SUCCEEDING)
	{
		printf("\n   Finished level %i in", d->md->lvl_c + 1);
		printf(" %i moves after %i attempt!\n", d->mv_c, d->md->try_c);
	}
	else if (d->md->state == STATE_DYING)
		printf("\n   You got got sonny... Better luck next time!\n");
	else if (d->md->state == STATE_CLOSING)
		printf("\n   Leaving so early...\n");
}

//prints messages a the end of the game
void	print_game_end(t_meta *md)
{
	if (md->state <= STATE_NULL)
	{
		printf("\n   Your map is bad and you should FEEL bad...");
		printf("\n   (State : %i)\n\n", md->state);
	}
	else if (md->state == STATE_RETRYING)
		printf("\n   How did you get here anyways?\n\n");
	else if (md->state == STATE_SUCCEEDING)
	{
		printf("\n\n   CONGRATULATIONS!!! You completed the");
		printf(" %i levels in %i moves!", md->lvl_n, md->mv_c);
		printf("\n   It took you %i retries", md->try_n - md->lvl_n);
		printf(" and left you with %i lives!\n\n", md->lives);
	}
	else if (md->state == STATE_DYING)
		printf("\n   R.I.P. Next time maybe try avoiding those...\n\n");
	else if (md->state == STATE_CLOSING)
		printf("\n   Didn't think you'd be a such a quitter...\n\n");
}
