/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:24:35 by mmustone          #+#    #+#             */
/*   Updated: 2025/11/24 15:41:20 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

int	setup_mlx(t_game *game)
{
	game->vars.mlx = mlx_init();
	if (!game->vars.mlx)
		return (0);
	return (1);
}

int	setup_textures_and_window(t_game *game)
{
	if (!init_textures(game))
		return (0);
	game->vars.win = mlx_new_window(game->vars.mlx, game->vars.win_width,
			game->vars.win_height, "Escape spaceship");
	if (!game->vars.win)
		return (0);
	return (1);
}

void	place_player_and_hooks(t_game *game)
{
	int	py;
	int	px;

	find_player(&game->map, &py, &px);
	game->player.pos_x = px * TILE_SIZE;
	game->player.pos_y = py * TILE_SIZE;
	render_map(game);
	mlx_hook(game->vars.win, 2, 0, key_hook, game);
	mlx_hook(game->vars.win, 17, 0, close_win, game);
}

int	handle_args_and_map(int ac, char **av, t_game *game)
{
	if (ac != 2)
	{
		ft_printf("Error\nUsage: %s <map_file>\n", av[0]);
		return (1);
	}
	ft_memset(game, 0, sizeof(*game));
	game->player.direct = 'r';
	if (!map_load(&game->map, av[1]))
		return (1);
	game->vars.win_height = game->map.height * TILE_SIZE + TILE_SIZE;
	game->vars.win_width = game->map.width * TILE_SIZE;
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (handle_args_and_map(ac, av, &game))
		return (1);
	if (!setup_mlx(&game))
	{
		free_map(&game.map);
		ft_printf("Error\nFailed to initialize MiniLibX\n");
		return (1);
	}
	if (!setup_textures_and_window(&game))
	{
		close_win(&game);
		return (1);
	}
	place_player_and_hooks(&game);
	mlx_loop(game.vars.mlx);
	return (0);
}
