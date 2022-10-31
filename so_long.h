/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:17:40 by llord             #+#    #+#             */
/*   Updated: 2022/10/31 13:25:52 by llord            ###   ########.fr       */
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
	//int 			z;		//elevation (in 1/8 asset_size) of the center of the tile
}					t_tile;

typedef struct s_data
{
	int 		max_wx;		//width (in pixels) of the window
	int 		max_wy;		//height (in pixels) of the window
	mlx_t		*window;	//where we print stuff

	int 		max_bx;		//width (in tiles) of the board
	int 		max_by;		//height (in tiles) of the board
	int			board_s;	//number of tiles in the board
	t_tile		**tiles;	//lists all tiles
	
	int			asset_n;	//number of different assets used	(8 assets)
	int 		asset_s;	//size (in pixels) of assets used	(64 pixels)
	mlx_image_t	**assets;	//

	t_coords	*pc;		//player position
	mlx_image_t	*player;	//player image
	int			updated;	//wether the player has moved or not (wether to render or not)

}			t_data;

//from initializers
void		initiate_data(t_data *d);
void		initiate_window(t_data *d);

//from drawers
void		draw_board(t_data *d);

//from coordinaters
t_coords	*clone_coords(t_coords c1);
int			find_wx(t_coords *bc, t_data *d);
int			find_wy(t_coords *bc, t_data *d);
t_tile		*find_tile(t_coords *bc, t_data *d);

//from checkers
int		is_in_board(t_data *d, t_coords *bc);
int		is_in_window(t_data *d, t_coords *wc);
int		is_valid(char *input);
int		is_in_range(t_data *d, t_tile *tile);

//from imager
void	move_image(mlx_image_t *image, int x, int y);
mlx_image_t **load_assets(t_data *d);
mlx_image_t	*put_image(t_data *d, t_coords *bc, int	id, int z);

//from boarder
t_tile	**load_board(t_data *d ,char *input, int size);

//from tiler
void	connect_tiles(t_data *d);

//from mover
void move_player(t_data *d, t_tile *tile, char direction);

//from libft_imports
void	*ft_calloc(size_t count, size_t	size);

#endif