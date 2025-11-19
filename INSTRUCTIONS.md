# Program: so_long

## Turn in Files
- `Makefile`
- `*.h`
- `*.c`
- `maps`
- `textures`

## Makefile Rules
- `NAME`
- `all`
- `clean`
- `fclean`
- `re`

## Arguments
- A map in the format `*.ber`

## Allowed External Functions
- `open`, `close`, `read`, `write`
- `malloc`, `free`, `perror`, `strerror`, `exit`
- All functions of the math library (`-lm` compiler option, see `man 3 math`)
- All functions of the MiniLibX
- `gettimeofday()`
- `ft_printf` or any equivalent **you coded**

## Libft
- Authorized: **Yes**

## Description
- You must create a basic 2D game in which a dolphin escapes Earth after eating some fish.  
Instead of a dolphin, fish, and the Earth, you can use any character, any collectible, and any place you want.
Your project must comply with the following rules:
- You must use MiniLibX, using either the version on the school machines or by
installing it using its sources.
- You have to turn in a Makefile which will compile your source files. It must not
relink.
- Your program must take a map description file with the extension .ber as a parametr.