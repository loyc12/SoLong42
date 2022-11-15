/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/15 13:35:46 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//puts values in fields used later one to prevent garbage affecting the program
static void	set_default_values(t_data *d)
{
	d->md->state = 0;	//prevents constant restarting

	d->flag_n = 0;		//flags left flag				(default)
	d->flag_r = 0;		//re_rendering flag				(default)
	d->flag_c = 0;		//asset cleaning flag			(default)
	d->flag_m = 0;		//move number flag				(default)

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
void	initiate_levels(t_meta *md, int	max_lvl, char **paths)
{
	char	**levels;

	md->tries = 0;				//default value for starting first level
	md->state = 1;				//default value for starting first level
	md->no_checks = 0;			//wether to ignore the initial parsing checks or not
	md->difficulty = 7;			//from 1 to 8
	md->char_limit = 2048;		//how many char a .ber can have

	if (1 < max_lvl)
	{
		levels = ft_calloc(md->max_lvl, sizeof(char *));
		md->levels = levels;
		md->max_lvl = max_lvl;
		printf("Lvl_no = %i\n", max_lvl);			//REMOVE ME
		md->lvl = -1;
		while (++md->lvl < max_lvl && 0 < md->state)
			md->state = get_level(md, paths[md->lvl]);
		md->lvl = 5;			//level to begin at
	}
	else
		md->state = -3;
}

//initialises the data struct used throughout the program
void	initiate_data(t_data *d, t_meta *md)
{ 
	d->md = md;
	set_default_values(d);
	load_board(d, md->levels[d->md->lvl]);
	if (0 <= md->state)
	{
		initiate_window(d);
		load_assets(d);
	}
}

/*
levels[0] = make_level("1111111\n1P0C0E1\n1111111\n");
levels[1] = make_level("111\n1P1\n101\n1C1\n101\n1E1\n111\n");
levels[2] = make_level("111111\n1P00E1\n101111\n101000\n1C1000\n111000\n");
levels[3] = make_level("111111\n1P00E1\n100001\n100001\n1C00A1\n111111\n");
levels[4] = make_level("1111111111111111\n1000000000000001\n10P0000000000001\n10000000000C0001\n1000000011000001\n100000001C000001\n1000000000000001\n10000000000A0001\n10000C1000000001\n1101001100000001\n100000001000C001\n100000001000CC01\n1000000000111001\n10E0000000000001\n1000000000000001\n1111111111111111\n");
levels[5] = make_level("1111111111111111111111111111111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100C00100000000000000000000C001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1110111111111110111110111111111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100A00000000000000100C00100C001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1111111110111111111111111110111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100000000000000P001000000000001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1110111110111110111110111110111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100C001000001000000000001000001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1111111110111111111110111110111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100C00000000100E00000000100C001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1111111111111111111111111111111\n");
*/