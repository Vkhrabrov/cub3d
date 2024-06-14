/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:19:54 by ccarrace          #+#    #+#             */
/*   Updated: 2024/06/14 23:28:36 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "libft.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GREY_COLOR 0x808080
#define PLAYER_COLOR 0xFF0000 // Red color for the player
// #define PLAYER_SIZE 8  // Half-size of the player square
#define MOVE_STEP WINDOW_WIDTH/100 // Step size for player movement
#define WALL_COLOR 0xFFFFFF // White color for walls
#define EMPTY_COLOR 0x000000 // Black color for empty space
#define PI 3.14159265359
// #define DEFAULT_CELL_SIZE 20 // Default size of each cell in the map

/* --- Data structures ------------------------------------------------------ */

typedef struct s_color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} t_color;

typedef struct s_player {
    float x;
    float y;
    double angle;
    int move_forward;
    int move_backward;
    int rotate_left;
    int rotate_right;
    double ray_length;
    int strafe_left;
    int strafe_right; // Length of the ray
} t_player;

typedef struct s_map {
    char* north_texture;
    char* south_texture;
    char* west_texture;
    char* east_texture;
    t_color floor_color;
    t_color ceiling_color;
    char** map_data;
    size_t map_height;
    size_t map_width;
} t_map;

typedef struct s_data {
    void *mlx;
    void *window;
    void *image;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    t_map map;
    t_player player;
    int cell_size;
    int player_size;
    struct timespec prev_time; // Add this line
} t_data;

/* --- Functions ------------------------------------------------------------ */

void freeMap(t_map* map);
void map_reading(t_map *map);
void put_pixel(t_data *data, int x, int y, int color);
void draw_square(t_data *data, int x, int y, int size, int color);
void draw_player(t_data *data, int x, int y, int size, int color);
void render_map(t_data *data);
int render_background(t_data *data);
int close_window(t_data *data);
int key_hook(int keycode, t_data *data);

#endif
