/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:17:40 by llord             #+#    #+#             */
/*   Updated: 2022/11/28 10:31:41 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>		//?? for open()?
# include <string.h>	//??? (memory.h initially)
# include <time.h>		//for srand()
# include "libs/MLX42/include/MLX42/MLX42.h"

typedef enum e_state
{
	STATE_ERR_FILE = -3,
	STATE_ERR_INPUT = -2,
	STATE_ERR_MAP = -1,
	STATE_CLOSING = 0,
	STATE_RETRYING = 1,
	STATE_SUCCEEDING = 2,
	STATE_DYING = 3
}			t_state;

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
	int 		x;				//x position (either in board or screen)
	int 		y;				//y position (either in board or screen)
	//int 		z;				//elevation (in 1/8 asset_size)
}				t_coords;

typedef struct s_tile
{
	t_coords		*bc;		//tile coordinates
	mlx_image_t		*floor;		//floor image instance
	mlx_image_t		*object;	//object image instance
	struct s_tile	*north;		//northern neighbor
	struct s_tile	*east;		//eastern neighbor
	struct s_tile	*south;		//southern neighbor
	struct s_tile	*west;		//western neighbor
	int				type;		//see e_type TYPES
	int				dst_f;		//current distance to flags / end
	int				dst_p;		//current distance to player
}					t_tile;

typedef struct s_meta		//data for the entire game (aka over multiple boards/levels)
{
	char	**levels;		//list of levels (TO BECOME PATHS NOT DATA)
	time_t	time;			//used to seed srand()
	int		state;			//see e_state STATES

	int		char_limit;		//maximum nb of chars in a .ber file
	int		no_checks;		//whether or not to do the initial checks on the input
	int		difficulty;		//odds over 8 that the enemies won't take a random move
	int		stability;		//chances over n+4 that a random move will no do anything

	int		mv_c;			//current amount of movement
	int		try_c;			//current amount of level (re)started
	int		try_n;			//total amount of attempted levels
	int		lvl_c;			//current level
	int		lvl_n;			//total amount of levels
}			t_meta;

typedef struct s_data		//data for the current board only
{
	int 		max_wx;		//width (in pixels) of the window
	int 		max_wy;		//height (in pixels) of the window
	mlx_t		*window;	//where we print stuff

	int 		max_bx;		//width (in tiles) of the board
	int 		max_by;		//height (in tiles) of the board
	int			board_s;	//number of tiles in the board
	t_tile		**tiles;	//lists all tiles
	
	int 		asset_s;	//size (in pixels) of assets used	(64 pixels)
	int			asset_n;	//number of distinct assets used	(7 assets)
	mlx_image_t	**assets;	//array of currently used assets
	mlx_image_t	**old;		//array of previously used assets
	mlx_image_t	*tittle;	//tittle image (never reloaded)

	t_coords	**enemies;	//enemy positions
	t_coords	*pc;		//player position
	t_coords	*ec;		//end position

	int			m_flag;		//whether the player has moved or not (wether to render or not)
	int			c_flag;		//whether to clean old assets

	int			flg_c;		//number of flags left to collect on this board
	int			mv_c;		//number of moves done on this board
	int			nm_n;		//number of enemies on this board

	t_meta		*md;		//game metadata
}				t_data;

//from libft_imports
void	*ft_calloc(size_t count, size_t	size);

//from checkers
int	is_on_edge(t_data *d, t_coords *bc);
int	is_in_window(t_data *d, t_coords *wc);
int	is_input_valid(char *input);
int	is_grid_valid(char *input);
int	is_map_valid(t_data *d);

//from initializers
void	initiate_levels(t_meta *md, int	lvl_n, char **paths);
void	initiate_data(t_data *d, t_meta *md);

//from coordinaters
t_coords	*clone_coords(t_coords c1);
t_coords	*bc_to_wc(t_data *d, t_coords *bc);

//from boarder
void	load_board(t_data *d ,char *input);

//from tiler
void	connect_grid(t_data *d);

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
int		can_move_to(t_tile *tile, char type);
void	move_player(t_data *d, t_tile *dst_tile);

//from printers
void	print_level_end(t_data *d);
void	print_game_end(t_meta *md);

//from hookers
void	hook(void *param);
void	key_hook(mlx_key_data_t keydata, void *param);

//from freeers
void	free_level(t_data *d);
void	free_game(t_meta *md);

//from finders
t_tile *find_neighbor(t_tile *tile, char goal);
t_tile	*find_tile(t_data *d, t_coords *bc);
int		find_tile_number(char *input);
int		find_enemy_number(char *input);

//from readers
int		get_level(t_meta *md, char *path);

//from bonusers
void	move_enemy_to(t_data *d, t_tile *dst_tile, int id);
void	move_enemies(t_data *d);
void	solve(t_data *d);

//from randomers
char	*random_comb(void);
void	move_random(t_data *d, t_tile *src_tile, int id);

#endif