/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:17:40 by llord             #+#    #+#             */
/*   Updated: 2022/11/14 11:54:49 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>	//??? (memory.h initially)
# include <time.h>		//for srand()
# include "libs/MLX42/include/MLX42/MLX42.h"

typedef enum e_id
{
	ID_FLOOR = 0,
	ID_SLAB = 1,
	ID_FLAG = 2,
	ID_HOLE = 3,
	ID_BALL = 4,
	ID_CONE = 5,
	ID_CUBE = 6
}			t_id;

typedef enum e_type
{
	TYPE_EMPTY = 0,
	TYPE_WALL = 1,
	TYPE_FLAG = 2,
	TYPE_END = 3,
	TYPE_PLAYER = 4,
	TYPE_ENEMY = 5
}			t_type;

typedef struct s_coords
{
	int 		x;		//x position (either in board or screen)
	int 		y;		//y position (either in board or screen)
	//int 		z;		//elevation (in 1/8 asset_size)
}				t_coords;

typedef struct s_tile
{
	t_coords		*bc;		//tile coordinates
	mlx_image_t		*floor;		//floor image instance
	mlx_image_t		*object;	//object image instance
	struct s_tile	*north;
	struct s_tile	*east;
	struct s_tile	*south;
	struct s_tile	*west;
	int				type;		//see e_type
	int				flag_f;		//current distance to flags / end
	int				flag_e;		//current distance to player
}					t_tile;

typedef struct s_meta
{
	char	**levels;		//list of levels (TO BECOME PATHS NOT DATA)
	int		state;			//-2 = unconnected board, -1 = unloaded board, 0 = closing game, 1 = retry level, 2 = next level, 3 = died)
	time_t	time;			//used to seed srand()

	int		mv;				//current amount of movement
	int		max_mv;			//shortest possible amount of movement (UNUSED)

	int		lvl;			//current level
	int		max_lvl;		//total amount of levels
	
	int		no_checks;		//whether or not to do the initial checks on the input
	int		difficulty;		//odds over 8 that the enemies won't take a random move
}			t_meta;

typedef struct s_data
{
	int 		max_wx;		//width (in pixels) of the window
	int 		max_wy;		//height (in pixels) of the window
	mlx_t		*window;	//where we print stuff

	int 		max_bx;		//width (in tiles) of the board
	int 		max_by;		//height (in tiles) of the board
	int			board_s;	//number of tiles in the board
	t_tile		**tiles;	//lists all tiles
	
	int			asset_n;	//number of distinct assets used	(7 assets)
	int 		asset_s;	//size (in pixels) of assets used	(64 pixels)
	mlx_image_t	**assets;	//array of currently used assets
	mlx_image_t	**old;		//array of previously used assets
	mlx_image_t	*tittle;	//tittle image (never reloaded)

	t_coords	**enemies;	//enemy positions
	t_coords	*pc;		//player position
	t_coords	*ec;		//end position

	int			flag_n;		//number of flags left to collect
	int			flag_r;		//whether the player has moved or not (wether to render or not)
	int			flag_c;		//whether to clean old assets
	int			flag_m;		//number of moves done
	int			flag_a;		//number of enemies

	t_meta		*md;		//game metadata
}				t_data;

//from libft_imports
void	*ft_calloc(size_t count, size_t	size);

//from checkers
int		is_on_edge(t_data *d, t_coords *bc);
int		is_in_window(t_data *d, t_coords *wc);
int		is_input_valid(char *input);
int		is_grid_valid(char *input);
int		is_map_valid(t_data *d);

//from initializers
char	**initiate_levels(int *n);
void	initiate_data(t_data *d, t_meta *md);

//from coordinaters
t_coords	*clone_coords(t_coords c1);
t_coords	*bc_to_wc(t_data *d, t_coords *bc);

//from boarder
void	load_board(t_data *d ,char *input);

//from tiler
t_tile	*find_tile(t_data *d, t_coords *bc);
void	connect_grid(t_data *d);
void	move_player_to(t_data *d, t_tile *dst_tile);
void	move_enemy_to(t_data *d, t_tile *dst_tile, int id);

//from filler
void	fill_test(t_data *d, t_tile *tile, int *flag_c, int *flag_e);
void	load_flag_dist(t_data *d);
void	load_player_dist(t_data *d);

//from imager
mlx_image_t	*make_image(t_data *d, char *path);
mlx_image_t	*put_image(t_data *d, t_coords *bc, int	id, int z);
void		load_assets(t_data *d);
void		clean_assets(t_data *d);

//from drawers
void	draw_board(t_data *d);

//from mover
void 	move_player(t_data *d, t_tile *src_tile, char direction);
void	solve(t_data *d);

#endif