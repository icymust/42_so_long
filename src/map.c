/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:27:16 by mmustone          #+#    #+#             */
/*   Updated: 2025/11/20 18:47:32 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void free_map(t_map *map)
{
    int i;

    if (!map->grid)
        return;
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

int map_load(t_map *map, char *filename)
{
    int fd;
    char *line;
    int i;
    int height;

    map->grid = NULL;
    map->width = 0;
    map->height = 0;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("Error: Cannot open file '%s'\n", filename);
        return (0);
    }

    // 1. считаем количество строк
    height = 0;
    while ((line = get_next_line(fd))) {
        height++;
        free(line);
    }
    close(fd);

    if (height < 3) {
        printf("Error: Map is too small\n");
        return (0);
    }

    // 2. выделяем память под grid
    map->grid = malloc(sizeof(char *) * (height + 1));
    if (!map->grid) {
        printf("Error: Memory allocation failed\n");
        return (0);
    }

    // 3. читаем строки карты во второй проход
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("Error: Cannot reopen file '%s'\n", filename);
        free(map->grid);
        map->grid = NULL;
        return (0);
    }

    i = 0;
    while ((line = get_next_line(fd))) {
        int len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        map->grid[i] = line;
        i++;
    }
    map->grid[i] = NULL;
    close(fd);

    map->height = i;
    map->width = ft_strlen(map->grid[0]);

    // 4. проверяем, что все строки одинаковой длины
    i = 1;
    while (i < map->height)
    {
        if ((int)ft_strlen(map->grid[i]) != map->width) {
            printf("Error: Map lines are not of equal length\n");
            free_map(map);
            return (0);
        }
        i++;
    }
    
    // 5. базовая проверка стен сверху и снизу
    if (grid_check(map) < 0) {
        printf("Grid error\n");
        free_map(map);
        return (0);
    }

    if (check_path(map) < 0)
    {
        printf("Path error\n");
        free_map(map);
        return (0);
    }

    return (1);
}
