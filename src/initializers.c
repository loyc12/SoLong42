/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/12/05 16:08:38 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//puts values in fields used later on to prevent garbage affecting the program
static void	set_level_data(t_data *d)
{
	d->m_flag = 1;
	d->c_flag = 0;
	d->flg_c = 0;
	d->mv_c = 0;
	d->max_bx = 0;
	d->max_by = 0;
	d->board_s = 0;
	d->asset_n = 7;
	d->asset_s = 64;
	d->old = NULL;
	d->md->state = STATE_NULL;
}

//puts values in fields used later one to prevent garbage affecting the program
static void	set_game_data(t_meta *md)
{
	md->lives = 42;
	md->difficulty = 7;
	md->instability = 1;
	md->char_limit = 1560;
	md->max_size = 76;
	md->no_checks = 0;
	md->try_c = 0;
	md->try_n = 0;
	md->state = STATE_RETRYING;
}

//converts a string to a malloced level string
char	*make_level(char *str)
{
	char	*level;
	int		i;

	i = 0;
	while (str[i])
		i++;
	level = ft_calloc(i, sizeof(char));
	i = -1;
	while (str[++i])
		level[i] = str[i];
	printf("\n%s\n", level);
	return (level);
}

//loads the level input strings from a given string
void	initiate_game(t_meta *md, int lvl_n, char **paths)
{
	set_game_data(md);
	if (1 <= lvl_n)
	{
		md->levels = ft_calloc(md->lvl_n, sizeof(char *));
		md->lvl_n = lvl_n;
		md->lvl_c = -1;
		while (++md->lvl_c < lvl_n && STATE_NULL < md->state)
			md->state = get_level(md, paths[md->lvl_c]);
		md->lvl_c = 0;
	}
	else
		md->state = STATE_ERR_FILE;
}

//initialises the data struct used throughout the program
void	initiate_level(t_data *d, t_meta *md)
{
	d->md = md;
	set_level_data(d);
	load_board(d, md->levels[d->md->lvl_c]);
	if (STATE_NULL <= md->state)
	{
		d->max_wx = (d->max_bx + d->max_by + 3) * d->asset_s / 2;
		d->max_wy = (d->max_bx + d->max_by + 5) * d->asset_s / 4;
		d->window = mlx_init(d->max_wx, d->max_wy, "So Round", true);
		d->tittle = make_image(d, "./assets/XPM/Tittle.xpm42");
		mlx_image_to_window(d->window, d->tittle, 0, 0);
		load_assets(d);
	}
}
