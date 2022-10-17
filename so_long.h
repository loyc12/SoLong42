/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:17:40 by llord             #+#    #+#             */
/*   Updated: 2022/10/17 08:40:41 by llord            ###   ########.fr       */
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
	int 		x;			//x position (either in board or screen)
	int 		y;			//y position (either in board or screen)
	int 		z;			//elevation (in 1/8 asset_size)
}				t_coords;

typedef struct s_tile
{
	mlx_image_t		*image;
	int				type;	//type of tile (0 for normal, 1 for walls, 2 for finish line)
	int 			z;		//elevation (in 1/8 asset_size) of the center of the tile
	struct s_tile	*north;
	struct s_tile	*east;
	struct s_tile	*south;
	struct s_tile	*west;
}					t_tile;

typedef struct s_entity
{
	mlx_image_t	*image;
	t_coords	*bc;
	int			type;		//type of entity (0 for end, 1 for player, 2 for key, 3 for doors
	int			id;			//key&door ids
}				t_entity;

typedef struct s_board
{
	t_tile		*tiles;		//lists all tiles
	t_entity	*entities;	//lists all enties
	int 		board_x;	//width (in tiles) of the board
	int 		board_y;	//height (in tiles) of the board
}				t_board;

typedef struct s_data
{
	int 	window_x;	//width (in pixels) of the window
	int 	window_y;	//height (in pixels) of the window
	mlx_t	*window;	//where we print stuff

	int 	board_x;	//width (in tiles) of the board		(temp) (to move)
	int 	board_y;	//height (in tiles) of the board	(temp) (to move)
	t_board	*board;		//where we put stuff

	int		x_offset;	//allows moving the window horizontally (useless?)
	int		y_offset;	//allows moving the window horizontally (useless?)
	
	int 	asset_size;	//size (in pixels) of assets used	(32 pixels)

	int		*inventory;	// IDs of collected keys (to activate doors)
}			t_data;

//from initializers
void	initiate_data(t_data *d);
void	initiate_player(t_data *d, t_entity *p);
void	initiate_window(t_data *d);

//from drawers
void	put_image(t_coords *bc, t_data *d, char *path);
void	put_end(int bx, int by, t_data *d);
void	put_entity(t_data *d, t_entity *e);
void	draw_static_board(t_data *d);

//from coordinaters
int		find_wx(t_coords *bc, t_data *d);
int		find_wy(t_coords *bc, t_data *d);

//from checkers
int	is_in_board(t_data *d, t_coords *bc);
int	is_in_window(t_data *d, t_coords *wc);

#endif