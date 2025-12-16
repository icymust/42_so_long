/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:17:36 by mmustone          #+#    #+#             */
/*   Updated: 2025/12/12 19:17:37 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

int	count_lines(const char *filename)
{
	int		fd;
	int		cnt;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	cnt = 0;
	line = get_next_line(fd);
	while (line)
	{
		cnt++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (cnt);
}

int	finalize_read(t_map *map, int i, int h)
{
	if (i != h)
	{
		free_map(map);
		return (0);
	}
	map->grid[i] = NULL;
	return (1);
}

int	read_grid(t_map *map, const char *filename, int height)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while (i < height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map->grid[i++] = line;
	}
	close(fd);
	return (finalize_read(map, i, height));
}
