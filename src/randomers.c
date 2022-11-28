/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:21:27 by llord             #+#    #+#             */
/*   Updated: 2022/11/28 13:23:46 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//returns a random 4-combination of 'N' 'E' 'S' 'W'
char	*random_comb(void)
{
	char	*all_comb;
	char	*output;
	int		pos;
	int		i;

	i = -1;
	pos = (rand() % 4);
	pos *= 6;
	pos += (rand() % 4);
	output = ft_calloc(5, sizeof(char));
	all_comb = "ESNWESNESWNESENWSENSEWNSE";
	while (++i < 4)
		output[i] = all_comb[pos + i];
	return (output);
}

//tries to move the entity to a random tile 4/n times, and stays put otherwise
void	move_random(t_data *d, t_tile *src_tile, int id)
{
	t_tile	*dst_tile;
	char	*order;
	int		i;

	if (id < 0 || (d->md->instability) <= (rand() % 8))
	{
		order = random_comb();
		i = -1;
		while (++i < 4)
		{
			dst_tile = find_neighbor(src_tile, order[i]);
			if (id < 0 && can_move_to(dst_tile, 'P'))
			{
				move_player(d, dst_tile);
				break ;
			}
			else if (0 <= id && can_move_to(dst_tile, 'A'))
			{
				move_enemy_to(d, dst_tile, id);
				break ;
			}
		}
		free(order);
	}
}
