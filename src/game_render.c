/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:58:23 by mmustone        #+#    #+#             */
/*   Updated: 2025/12/09 15:29:58 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	load_texture(t_game *game, void **dst, char *path)
{
	int	w;
	int	h;

	if (!game->vars.mlx)
		return (0);
	*dst = mlx_png_file_to_image(game->vars.mlx, path, &w, &h);
	if (!*dst)
		return (0);
	return (1);
}

int	init_textures(t_game *game)
{
	if (!load_texture(game, &game->img_wall, "textures/wall.png"))
		return (0);
	if (!load_texture(game, &game->img_floor, "textures/floor.png"))
		return (0);
	if (!load_texture(game, &game->img_exit, "textures/exit.png"))
		return (0);
	if (!load_texture(game, &game->img_key, "textures/key.png"))
		return (0);
	if (!load_texture(game, &game->player.img, "textures/player1.png"))
		return (0);
	return (1);
}

void	*choose_img(t_game *game, char c)
{
	if (c == '1')
		return (game->img_wall);
	if (c == '0')
		return (game->img_floor);
	if (c == 'E')
		return (game->img_exit);
	if (c == 'C')
		return (game->img_key);
	if (c == 'P')
		return (game->player.img);
	return (game->img_floor);
}

void	draw_cell(t_game *game, int y, int x)
{
	void	*img;
	t_pos	pos;
	char	c;

	c = game->map.grid[y][x];
	img = choose_img(game, c);
	if (!img)
		return ;
	pos.x = x * TILE_SIZE;
	pos.y = y * TILE_SIZE;
	mlx_put_image_to_window(game->vars.mlx, game->vars.win, img, pos.x, pos.y);
}

void	render_map(t_game *game)
{
	int	y;
	int	x;

	if (!game || !game->vars.mlx || !game->vars.win)
		return ;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			draw_cell(game, y, x);
			x++;
		}
		y++;
	}
}
