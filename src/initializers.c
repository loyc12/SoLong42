/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/28 12:18:08 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//puts values in fields used later one to prevent garbage affecting the program
static void	set_default_values(t_data *d)
{
	d->md->state = STATE_CLOSING;	//prevents constant restarting	(default)

	d->m_flag = 0;		//re_rendering flag				(default)
	d->c_flag = 0;		//asset cleaning flag			(default)
	d->flg_c = 0;		//flags left flag				(default)
	d->mv_c = 0;		//move number flag				(default)

	d->max_bx = 0;		//board width					(uninitialized)
	d->max_by = 0;		//board height					(uninitialized)
	d->board_s = 0;		//tile amount					(uninitialized)

	d->asset_n = 7;		//number of assets				(constant)
	d->asset_s = 64;	//asset resolution				(constant)

	d->old = NULL;		//previously used assets		(uninitialized)
}

//initiate the window and window related fields
static void	initiate_window(t_data *d)
{
	d->max_wx = (d->max_bx + d->max_by + 3) * d->asset_s / 2;
	d->max_wy = (d->max_bx + d->max_by + 5) * d->asset_s / 4;
	d->window = mlx_init(d->max_wx, d->max_wy, "So Round", true);

	d->tittle = make_image(d, "./assets/XPM/Tittle.xpm42");
	mlx_image_to_window(d->window, d->tittle, 0, 0);
}

char	*make_level(char *str)
{
	char	*level;
	int		i;

	i = 0;
	while (str[i])
		i++;
	level = ft_calloc(i + 1, sizeof(char));
	i = -1;
	while (str[++i])
		level[i] = str[i];
	printf("\n%s\n", level);
	return (level);
}

//loads the level input strings from a given string
void	initiate_levels(t_meta *md, int	lvl_n, char **paths)
{
	char	**levels;

	md->difficulty = 6;			//from 0 to 8
	md->stability = 4;			//from 0 to 4
	md->no_checks = 0;			//wether to ignore the initial parsing checks or not

	md->char_limit = 2048;		//how many char a .ber can have
	md->try_c = 0;				//default value for starting first level
	md->try_n = 0;				//default value for starting first level
	md->state = STATE_RETRYING;	//default value for starting first level

	if (1 <= lvl_n)
	{
		levels = ft_calloc(md->lvl_n, sizeof(char *));
		md->levels = levels;
		md->lvl_n = lvl_n;
		md->lvl_c = -1;
		while (++md->lvl_c < lvl_n && STATE_CLOSING < md->state)
			md->state = get_level(md, paths[md->lvl_c]);
		md->lvl_c = 0;										//level # to begin at
	}
	else
		md->state = STATE_ERR_FILE;
}

//initialises the data struct used throughout the program
void	initiate_data(t_data *d, t_meta *md)
{
	d->md = md;
	set_default_values(d);
	load_board(d, md->levels[d->md->lvl_c]);
	if (STATE_CLOSING <= md->state)
	{
		initiate_window(d);
		load_assets(d);
	}
}
