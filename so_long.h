/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:17:40 by llord             #+#    #+#             */
/*   Updated: 2022/10/26 12:37:49 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <memory.h>
# include "libs/MLX42/include/MLX42/MLX42.h"

typedef struct s_coords
{
	int 		x;		//x position (either in board or screen)
	int 		y;		//y position (either in board or screen)
	
	//int 		z;		//elevation (in 1/8 asset_size)
}				t_coords;
/*
typedef struct s_entity //aka the flag(s) (for now)
{
	t_coords	*bc;
	int			info;

	//int			type;		//type of entity (0 for end, 1 for player, 2 for key, 3 for doors
	//int			id;			//key&door ids
}				t_entity;
*/
typedef struct s_tile
{
	t_coords		*bc;
	mlx_image_t		*floor;
	mlx_image_t		*object;
	struct s_tile	*north;
	struct s_tile	*east;
	struct s_tile	*south;
	struct s_tile	*west;
	int				type;	// 0 for empty, 1 for walls, 2 for flag, 3 for end, 4 for player
	//int 			z;				//elevation (in 1/8 asset_size) of the center of the tile
	//struct s_entity	*entity;	//the entity present on this tile
}					t_tile;

typedef struct s_data
{
	int 		max_wx;		//width (in pixels) of the window
	int 		max_wy;		//height (in pixels) of the window
	mlx_t		*window;	//where we print stuff

	int 		max_bx;		//width (in tiles) of the board
	int 		max_by;		//height (in tiles) of the board
	t_tile		**tiles;	//lists all tiles
	
	int			board_s;	//number of tiles in the board
	int 		asset_s;	//size (in pixels) of assets used	(32 pixels)
	t_coords	*pc;		//player position

	mlx_image_t	**atlas;	//stores all image template
	int			updated;

	//int		*inventory;	//IDs of collected keys (to activate doors)
}			t_data;

//from initializers
t_coords	*clone_coords(t_coords c1);
void		initiate_data(t_data *d);
void		initiate_window(t_data *d);

//from drawers
mlx_image_t	*put_image(t_coords *bc, t_data *d, char *path);
void		draw_board(t_data *d);

//from coordinaters
int		find_wx(t_coords *bc, t_data *d);
int		find_wy(t_coords *bc, t_data *d);
t_tile	*find_tile(t_coords *bc, t_data *d);

//from checkers
int		is_in_board(t_data *d, t_coords *bc);
int		is_in_window(t_data *d, t_coords *wc);

//from boarder
t_tile	**make_board(t_data *d ,char *input, int size);

//from tiler
void	connect_tiles(t_data *d);

//from mover
void move_player(t_data *d, t_tile *tile, char direction);

#endif