/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:27:16 by mmustone          #+#    #+#             */
/*   Updated: 2025/12/12 19:23:31 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
}

int	validate_dimensions(t_map *map)
{
	int	i;

	if (map->height < 3 || map->width < 3)
	{
		ft_printf("Error\nMap is too small\n");
		return (0);
	}
	i = 1;
	while (i < map->height)
	{
		if ((int)ft_strlen(map->grid[i]) != map->width)
		{
			ft_printf("Error\nMap lines are not of equal length\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	alloc_and_read(t_map *map, const char *filename)
{
	int	height;

	height = count_lines(filename);
	if (height < 3)
	{
		ft_printf("Error\nMap is too small\n");
		return (0);
	}
	map->grid = malloc(sizeof(char *) * (height + 1));
	if (!map->grid)
	{
		ft_printf("Error\nMalloc\n");
		return (0);
	}
	if (!read_grid(map, filename, height))
		return (0);
	map->height = height;
	map->width = ft_strlen(map->grid[0]);
	return (1);
}

int	map_load(t_map *map, char *filename)
{
	if (!map || !filename)
		return (0);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	if (!alloc_and_read(map, filename))
		return (0);
	if (!validate_dimensions(map))
	{
		free_map(map);
		return (0);
	}
	if (grid_check(map) < 0 || check_path(map) < 0)
	{
		ft_printf("Error\nMap validation error\n");
		free_map(map);
		return (0);
	}
	return (1);
}
