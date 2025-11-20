/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmustone <mmustone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:15:25 by mmustone          #+#    #+#             */
/*   Updated: 2025/11/20 19:17:57 by mmustone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int move_player(t_game *game, char c){
    mlx_clear_window(game->vars.mlx, game->vars.win);
    if(c == 'r'){
        game->player.pos_x += 64;
        game->player.steps ++;
        // printf("Amount of steps: %i\n", game->player.steps);
    }
    else if(c =='l'){
        game->player.pos_x -= 64;
        game->player.steps ++;
        // printf("Amount of steps: %i\n", game->player.steps);
    }
    else if(c =='u'){
        game->player.pos_y -= 64;
        game->player.steps ++;
        // printf("Amount of steps: %i\n", game->player.steps);
    }
    else if(c =='d'){
        game->player.pos_y += 64;
        game->player.steps ++;
        // printf("Amount of steps: %i\n", game->player.steps);
    }
    mlx_put_image_to_window(game->vars.mlx, game->vars.win,
                            game->player.img,
                            game->player.pos_x, game->player.pos_y);
    return(0);
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
    return 0;
}
