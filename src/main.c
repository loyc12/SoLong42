/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/14 14:01:18 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//gcc -Werror -Wextra -Wall ./src/* ./libs/MLX42/libmlx42.a -I include -lglfw -L "/Users/$USER/.brew/opt/glfw/lib/"

//frees all the leftover data
static void	free_all(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		if (tile->object)
			mlx_delete_image(d->window, tile->object);
		if (tile->floor)
			mlx_delete_image(d->window, tile->floor);
		free(tile->bc);
		free(tile);
	}
	if (-1 < d->md->state)
	{
		i = -1;
		while (++i < d->asset_n)
			if (d->assets[i])
				mlx_delete_image(d->window, d->assets[i]);
		mlx_delete_image(d->window, d->tittle);
		mlx_terminate(d->window);
	}
	if (-2 < d->md->state)
	{
		free(d->tiles);
		free(d->assets);
		free(d->enemies);
	}
}

static void	hook(void *param)
{
	t_data	*d;

	d = param;
	if (mlx_is_key_down(d->window, MLX_KEY_ESCAPE) || d->md->state != 0)
		mlx_close_window(d->window);
	if (d->flag_r)
		draw_board(d);
	if (mlx_is_key_down(d->window, MLX_KEY_Q))
		solve(d);
}

//key hook used during the main loop
static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*d;

	d = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W)
			move_player(d, find_tile(d, d->pc), 'N');
		if (keydata.key == MLX_KEY_D)
			move_player(d, find_tile(d, d->pc), 'E');
		if (keydata.key == MLX_KEY_S)
			move_player(d, find_tile(d, d->pc), 'S');
		if (keydata.key == MLX_KEY_A)
			move_player(d, find_tile(d, d->pc), 'W');
	}
}

static void	print_level_end(t_data *d)
{
	if (d->md->state < 0)
		printf("\n  Unable to properly load the game board. State = %i \n\n", d->md->state);
	if (d->md->state == 0)
		printf("\n  I played this shitty game and all I got was this lousy message...\n\n");
	else if (d->md->state == 1)
		printf("\n  Save-scumming I see...\n\n");
	else if (d->md->state == 2)
		printf("\n  Finished level %i in %i moves!\n\n", d->md->lvl + 1, d->flag_m);
	else if (d->md->state == 3)
		printf("\n  You got got sonny... Better luck next time!\n\n");
}

static void	play_map(t_meta *md)
{
	t_data	d;

	printf("\n  Launching level %i\n", md->lvl + 1);
	initiate_data(&d, md);
	printf("\n  State : %i\n\n", md->state);
	if (0 <= md->state)
	{
		draw_board(&d);
		mlx_key_hook(d.window, &key_hook, &d);
		mlx_loop_hook(d.window, &hook, &d);
		mlx_loop(d.window);
		md->mv += d.flag_m;
	}
	print_level_end(&d);
	free_all(&d);
}

static void	print_game_end(t_meta *md)
{
	if (md->state < 0)
		printf("\n  Your map is bad and you should FEEL bad...\n\n");
	else if (md->state == 0)
		printf("\n  Didn't think you'd be a quitter...\n\n");
	else if (md->state == 2 && md->mv <= md->max_mv)
		printf("\n  Gotta go fast to earn those chillidogs!!!\n\n");
	else if (md->state == 2)
		printf("\n  CONGRATULATION! You won in %i total moves\n\n", md->mv);
	else if (md->state == 3)
		printf("\n  R.I.P. Next time maybe try avoiding those...\n\n");
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
	md.lvl = -1;
	while (++(md.lvl) < md.state)
		free(md.levels[md.lvl]);
	free(md.levels);

	return (EXIT_SUCCESS);
}
