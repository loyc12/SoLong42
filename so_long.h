/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:17:40 by llord             #+#    #+#             */
/*   Updated: 2022/11/30 14:39:22 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include "libs/MLX42/include/MLX42/MLX42.h"

typedef enum e_state
{
	STATE_ERR_FILE = -3,
	STATE_ERR_INPUT = -2,
	STATE_ERR_MAP = -1,
	STATE_NULL = 0,
	STATE_RETRYING = 1,
	STATE_SUCCEEDING = 2,
	STATE_DYING = 3,
	STATE_CLOSING = 4
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
	int			x;
	int			y;
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
	int				type;
	int				dst_f;
	int				dst_p;
}					t_tile;

typedef struct s_meta
{
	char	**levels;
	time_t	time;
	int		state;

	int		lives;
	int		difficulty;
	int		instability;
	int		char_limit;
	int		max_size;
	int		no_checks;

	int		mv_c;
	int		try_c;
	int		try_n;
	int		lvl_c;
	int		lvl_n;
}			t_meta;

typedef struct s_data
{
	int			max_wx;
	int			max_wy;
	mlx_t		*window;

	int			max_bx;
	int			max_by;
	int			board_s;
	t_tile		**tiles;

	int			asset_s;
	int			asset_n;
	mlx_image_t	**assets;
	mlx_image_t	**old;
	mlx_image_t	*tittle;

	t_coords	**enemies;
	t_coords	*pc;
	t_coords	*ec;

	int			m_flag;
	int			c_flag;

	int			flg_c;
	int			mv_c;
	int			nm_n;

	t_meta		*md;
}				t_data;

//from libft_imports
void		*ft_calloc(size_t count, size_t	size);

//from checkers
int			is_on_edge(t_data *d, t_coords *bc);
int			is_in_window(t_data *d, t_coords *wc);
int			is_input_valid(char *input);
int			is_grid_valid(char *input);
int			is_map_valid(t_data *d);

//from initializers
void		initiate_game(t_meta *md, int lvl_n, char **paths);
void		initiate_level(t_data *d, t_meta *md);

//from coordinaters
t_coords	*clone_coords(t_coords c1);
t_coords	*bc_to_wc(t_data *d, t_coords *bc);

//from boarder
void		load_board(t_data *d, char *input);

//from tiler
void		connect_grid(t_data *d);

//from filler
void		fill_test(t_data *d, t_tile *tile, int *flags);
void		load_flag_dist(t_data *d);
void		load_player_dist(t_data *d);

//from imager
mlx_image_t	*make_image(t_data *d, char *path);
mlx_image_t	*put_image(t_data *d, t_coords *bc, int id, int z);
void		load_assets(t_data *d);
void		clean_old_assets(t_data *d);

//from drawers
void		draw_board(t_data *d);

//from mover
int			can_move_to(t_tile *tile, char type);
void		move_player(t_data *d, t_tile *dst_tile);

//from printers
void		print_level_end(t_data *d);
void		print_game_end(t_meta *md);

//from hookers
void		hook(void *param);
void		key_hook(mlx_key_data_t keydata, void *param);

//from freeers
void		free_level(t_data *d);
void		free_game(t_meta *md);

//from finders
t_tile		*find_neighbor(t_tile *tile, char goal);
t_tile		*find_tile(t_data *d, t_coords *bc);
int			find_tile_number(char *input);
int			find_enemy_number(char *input);

//from readers
int			get_level(t_meta *md, char *path);

//from bonusers
void		move_enemy_to(t_data *d, t_tile *dst_tile, int id);
void		move_enemies(t_data *d);
void		solve(t_data *d);

//from randomers
char		*random_comb(void);
void		move_random(t_data *d, t_tile *src_tile, int id);

#endif