/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martinmust <martinmust@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:15:25 by mmustone          #+#    #+#             */
/*   Updated: 2025/11/23 19:12:39 by martinmust       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int move_in_grid(t_game *game, char move){
    t_map *map = &game->map;
    int x;
    int y;
    find_player(map, &y, &x);
    if(move == 'r' )
    {
        if(map->grid[y][x+1] == 'C')
            map->collectiable--;
        if(map->grid[y][x+1] == 'E' && map->collectiable == 0){
            close_win(game);
            return (0);
        }
        else if (map->grid[y][x+1] != 'E' && map->grid[y][x+1] != '1' ){
            map->grid[y][x] = '0';
            map->grid[y][x+1] = 'P';  
            return(1);      
        }
        return(0);
    }
    if(move == 'l' )
    {
        if(map->grid[y][x-1] == 'C')
            map->collectiable--;
        if(map->grid[y][x-1] == 'E' && map->collectiable == 0){
            close_win(game);
            return (0);
        }
        else if (map->grid[y][x-1] != 'E' && map->grid[y][x-1] != '1'){
            map->grid[y][x] = '0';
            map->grid[y][x-1] = 'P';  
            return(1);      
        }
        return(0);
    }
    if(move == 'u')
    {
        if(map->grid[y-1][x] == 'C')
            map->collectiable--;
        if(map->grid[y-1][x] == 'E' && map->collectiable == 0){
            close_win(game);
            return (0);
        }
        else if (map->grid[y-1][x] != 'E' && map->grid[y-1][x] != '1'){
            map->grid[y][x] = '0';
            map->grid[y-1][x] = 'P';
            return(1);        
        }
        return(0);
    }
    if(move == 'd')
    {
        if(map->grid[y+1][x] == 'C')
            map->collectiable--;
        if(map->grid[y+1][x] == 'E' && map->collectiable == 0){
            close_win(game);
            return (0);
        }
        else if (map->grid[y+1][x] != 'E' && map->grid[y+1][x] != '1'){
            map->grid[y][x] = '0';
            map->grid[y+1][x] = 'P';    
            return(1);    
        }
        return(0);
    }
    return(0);
}

int move_player(t_game *game, char c){
    int moved;

    mlx_clear_window(game->vars.mlx, game->vars.win);
    moved = move_in_grid(game, c);
    if (moved) {
        if (c == 'r')
            game->player.pos_x += TILE_SIZE;
        else if (c == 'l')
            game->player.pos_x -= TILE_SIZE;
        else if (c == 'u')
            game->player.pos_y -= TILE_SIZE;
        else if (c == 'd')
            game->player.pos_y += TILE_SIZE;
        game->player.steps++;
    }
    render_map(game);
    return (0);
}

int key_hook(int keycode, t_game *game)
{
    if(keycode == 53)
        close_win(game);
    else if(keycode == 2)
        move_player(game, 'r');
    else if(keycode == 0)
        move_player(game, 'l');
    else if(keycode == 13)
        move_player(game, 'u');
    else if(keycode == 1)
        move_player(game, 'd');
    printf("Moves:%i\n", game->player.steps);
    return 0;
}
