/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:18:10 by mmustone          #+#    #+#             */
/*   Updated: 2025/12/16 16:03:29 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	map_name_check(const char *filename)
{
	int	length;

	length = ft_strlen(filename);
	if (length < 4)
		return (0);
	if (ft_strncmp(&filename[length - 4], ".ber", 4) == 0)
		return (1);
	return (0);
}

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

	if (!map_name_check(filename))
		return (0);
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
