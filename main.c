#include "so_long.h"
#include <string.h> // для memset, strlen, strcmp

typedef struct s_vars {
    void  *mlx;
    void  *win;
    int x;
} t_vars;

typedef struct s_map {
    char    **grid;   // массив строк, каждая строка = одна строка карты
    int     width;    // длина строки
    int     height;   // количество строк
} t_map;

typedef struct player{
    int pos_x;
    int pos_y;
    void *img;
    int steps;
} t_player;

typedef struct s_game {
    t_vars vars;
    t_player player;
    t_map map;
} t_game;

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

int close_win(t_game *game) {
    printf("Close window\n");
    if (game->player.img)
        mlx_destroy_image(game->vars.mlx, game->player.img);
    if (game->vars.win)
        mlx_destroy_window(game->vars.mlx, game->vars.win);
    free_map(&game->map);
    exit(0);
    return (0);
}

int move_player(t_game *game, char c){
    mlx_clear_window(game->vars.mlx, game->vars.win);
    if(c == 'r' && game->player.pos_x<435){
        game->player.pos_x += 15;
        game->player.steps ++;
        printf("Amount of steps: %i\n", game->player.steps);
    }
    else if(c =='l'){
        game->player.pos_x -= 15;
        game->player.steps ++;
        printf("Amount of steps: %i\n", game->player.steps);
    }
    else if(c =='u'){
        game->player.pos_y -= 15;
        game->player.steps ++;
        printf("Amount of steps: %i\n", game->player.steps);
    }
    else if(c =='d'){
        game->player.pos_y += 15;
        game->player.steps ++;
        printf("Amount of steps: %i\n", game->player.steps);
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

// пока grid_check проверяет только верхнюю и нижнюю строку на стены
int grid_check(t_map *map){
    int i = 0;

    while (map->grid[0][i])
    {
        if (map->grid[0][i] != '1'
            || map->grid[map->height - 1][i] != '1')
            return (-1);
        i++;
    }
    return (0);
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
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        map->grid[i] = line;
        i++;
    }
    map->grid[i] = NULL;
    close(fd);

    map->height = i;
    map->width = strlen(map->grid[0]);

    // 4. проверяем, что все строки одинаковой длины
    i = 1;
    while (i < map->height)
    {
        if ((int)strlen(map->grid[i]) != map->width) {
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

    return (1);
}

int main(int ac, char **av)
{
    t_game game;
    char *path = "./textures/player.png";
    int img_width = 64;
    int img_height = 64;

    if (ac < 2) {
        printf("Usage: %s <map_file> [--test]\n", av[0]);
        return (1);
    }

    // обнуляем всю структуру игры, чтобы все указатели были NULL
    memset(&game, 0, sizeof(t_game));

    if (!map_load(&game.map, av[1])) {
        printf("Failed in map_load\n");
        return (1);
    }

    printf("Map loaded: %d x %d\n", game.map.width, game.map.height);

    // режим без графики для проверки ликов карты
    if (ac == 3 && strcmp(av[2], "--test") == 0) {
        free_map(&game.map);
        printf("Test mode: Exiting without launching graphics.\n");
        return (0);
    }

    // -- MLX --

    game.vars.mlx = mlx_init();
    if (!game.vars.mlx) {
        free_map(&game.map);
        printf("Error: Failed to initialize MiniLibX\n");
        return (1);
    }

    game.player.img = mlx_png_file_to_image(game.vars.mlx,
                                            path,
                                            &img_width,
                                            &img_height);
    if (!game.player.img) {
        free_map(&game.map);
        // если ты на Linux, можно добавить:
        // mlx_destroy_display(game.vars.mlx);
        // free(game.vars.mlx);
        printf("Error: Failed to load image '%s'\n", path);
        return (1);
    }

    game.vars.win = mlx_new_window(game.vars.mlx, 500, 500, "Escape from aliens");
    mlx_put_image_to_window(game.vars.mlx, game.vars.win,
                            game.player.img, 0, 0);

    mlx_hook(game.vars.win, 2, 0, key_hook, &game);
    mlx_hook(game.vars.win, 17, 0, close_win, &game);

    mlx_loop(game.vars.mlx);
    return (0);
}
