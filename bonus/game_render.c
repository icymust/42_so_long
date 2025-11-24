/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:58:23 by martinmust        #+#    #+#             */
/*   Updated: 2025/11/24 16:43:45 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

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
	if (!load_texture(game, &game->player.img, "textures/player.png"))
		return (0);
	if (!load_texture(game, &game->player.imgl, "textures/playerl.png"))
		return (0);
	if (!load_texture(game, &game->player.imgu, "textures/playeru.png"))
		return (0);
	if (!load_texture(game, &game->img_alien, "textures/alien.png"))
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
	if (c == 'A')
		return (game->img_alien);
	if (c == 'P')
	{
		if (game->player.direct == 'u')
			return (game->player.imgu);
		else if (game->player.direct == 'l')
			return (game->player.imgl);
		else
			return (game->player.img);
	}
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
	int		y;
	int		x;
	char	*str;

	if (!game || !game->vars.mlx || !game->vars.win)
		return ;
	str = ft_itoa(game->player.steps);
	if (!str)
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
	mlx_string_put(game->vars.mlx, game->vars.win, 10, game->vars.win_height
		- 10, 0xFFFFFF, "Moves");
	mlx_string_put(game->vars.mlx, game->vars.win, 50, game->vars.win_height
		- 10, 0xFFFFFF, str);
	free(str);
}
