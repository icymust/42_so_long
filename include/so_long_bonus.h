/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:42:11 by mmustone          #+#    #+#             */
/*   Updated: 2025/12/10 14:58:02 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>

# define TILE_SIZE 64

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
}				t_vars;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			collectiable;
	int			alien;
	int			spawn;
	int			exit;
}				t_map;

typedef struct player
{
	int			pos_x;
	int			pos_y;
	void		*img[2];
	void		*imgl[2];
	void		*imgu;
	int			steps;
	char		direct;
}				t_player;

typedef struct s_enemy
{
	int			pos_x;
	int			pos_y;
	void		*frames[2];
	int			current_frame;
}				t_enemy;

typedef struct s_game
{
	t_vars		vars;
	t_player	player;
	t_map		map;
	t_enemy		enemy;
	void		*img_wall;
	void		*img_floor;
	void		*img_exit;
	void		*img_key[2];
	int			end_game;
}				t_game;

typedef struct s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct s_flood
{
	char		**grid;
	t_map		*map;
	int			found_c;
	int			exit_ok;
}				t_flood;

int				close_win(t_game *game);
void			free_map(t_map *map);
int				map_load(t_map *map, char *filename);
int				grid_check(t_map *map);
int				key_hook(int keycode, t_game *game);
char			**dup_grid(t_map *m);
void			free_grid_copy(char **cp, int h);
int				check_path(t_map *m);
int				find_player(t_map *map, int *start_y, int *start_x, char c);
int				init_textures(t_game *game);
void			render_map(t_game *game);
int				count_lines(const char *filename);
int				read_grid(t_map *map, const char *filename, int height);
int				move_in_grid(t_game *game, char move);
void			alien_update(t_game *game);
int				loop_tick(void *param);
void			render_map_end(t_game *game);
void			draw_cell(t_game *game, int y, int x);
int				check_alien_move(t_map *m, int ny, int nx, t_pos *d);

#endif
