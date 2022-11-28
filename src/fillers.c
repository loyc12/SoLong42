/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/28 12:13:33 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//uses a floodfill algo to see if every object is reachable
void	fill_test(t_data *d, t_tile *tile, int *flag_c, int *flag_e, int *flag_b)	//TOO MANY ARGS !!!
{
	if (tile == NULL || tile->dst_f != 0)
		return ;

	tile->dst_f = 1;
	if (tile->type == TYPE_FLAG)
		*flag_c += 1;
	if (tile->type == TYPE_END)
		*flag_e += 1;
	if (is_on_edge(d, tile->bc))
		*flag_b += 1;

	fill_test(d, tile->north, flag_c, flag_e, flag_b);
	fill_test(d, tile->east, flag_c, flag_e, flag_b);
	fill_test(d, tile->south, flag_c, flag_e, flag_b);
	fill_test(d, tile->west, flag_c, flag_e, flag_b);
}

//calculates the distance of each tile to a specific tile
static void	fill_flag_dist(t_data *d, t_tile *tile, int dist)
{
	if (tile == NULL || tile->dst_f <= dist || tile->type == TYPE_ENEMY)
		return ;
	tile->dst_f = dist;
	fill_flag_dist(d, tile->north, dist + 1);
	fill_flag_dist(d, tile->east, dist + 1);
	fill_flag_dist(d, tile->south, dist + 1);
	fill_flag_dist(d, tile->west, dist + 1);
}

//calculates the distance of each tile to the player
void	fill_player_dist(t_data *d, t_tile *tile, int dist)
{
	if (tile == NULL || tile->dst_p <= dist || tile->type == TYPE_FLAG || tile->type == TYPE_END)
		return ;
	tile->dst_p = dist;
	fill_player_dist(d, tile->north, dist + 1);
	fill_player_dist(d, tile->east, dist + 1);
	fill_player_dist(d, tile->south, dist + 1);
	fill_player_dist(d, tile->west, dist + 1);
}

//calculates the distance to the nearest objective (flag || end) for each tile
void	load_flag_dist(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->board_s)
		d->tiles[i]->dst_f = d->board_s;
	i = -1;
	if (0 < d->flg_c)
	{
		while (++i < d->board_s)
			if (d->tiles[i]->type == TYPE_FLAG)
				fill_flag_dist(d, d->tiles[i], 0);
	}
	else
		fill_flag_dist(d, find_tile(d, d->ec), 0);

	//printf("    Flags distance map reloaded!\n");							//REMOVE ME
}

//calculates the distance to the nearest objective (flag / end) for each tile
void	load_player_dist(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->board_s)
		d->tiles[i]->dst_p = d->board_s;
	fill_player_dist(d, find_tile(d, d->pc), 0);

	//printf("    Player distance map reloaded!\n");						//REMOVE ME
}