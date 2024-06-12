/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:06:48 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/06/12 21:53:13 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void freeMap(t_map* map) {
    for (size_t i = 0; i < map->map_height; ++i) {
        free(map->map_data[i]);
    }
    free(map->map_data);
}

void map_reading(t_map *map) {
    const char* example_map[] = {
        "1111111111111111111111111",
        "1000000000110000000000001",
        "1011000001110000000000001",
        "100100000000000000000000111111111",
        "111111111011000001110000000000001",
        "100000000011000001110111100011111",
        "11110111111111011100000010001",
        "11110111111111011101010010001",
        "11000000110101011100000010001",
        "10000000000000001100000010001",
        "10000000000000001101010010001",
        "11000001110101011101011010N01",
        "11110111 1110101 101111010001",
        "11111111 1111111 11111111111"
    };

    map->map_height = sizeof(example_map) / sizeof(example_map[0]);
    map->map_width = 0;
    for (size_t i = 0; i < map->map_height; ++i) {
        size_t row_length = ft_strlen(example_map[i]);
        if (row_length > map->map_width) {
            map->map_width = row_length;
        }
    }

    map->map_data = malloc(map->map_height * sizeof(char*));
    for (size_t i = 0; i < map->map_height; ++i) {
        map->map_data[i] = ft_strdup(example_map[i]);
    }
}

void put_pixel(t_data *data, int x, int y, int color) {
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
        char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

void draw_square(t_data *data, int x, int y, int size, int color) {
    for (int j = y; j < y + size; j++) {
        for (int i = x; i < x + size; i++) {
            put_pixel(data, i, j, color);
        }
    }
}

void draw_player(t_data *data, int x, int y, int size, int color) {
    draw_square(data, x - size / 2, y - size / 2, size, color);
}

void render_map(t_data *data) {
    for (size_t i = 0; i < data->map.map_height; i++) {
        for (size_t j = 0; j < data->map.map_width; j++) {
            if (j < ft_strlen(data->map.map_data[i])) {
                int color = GREY_COLOR;
                if (data->map.map_data[i][j] == '1') {
                    color = WALL_COLOR;
                } else if (data->map.map_data[i][j] == '0') {
                    color = EMPTY_COLOR;
                } else if (ft_strchr("NSEW", data->map.map_data[i][j])) {
                    // Set player initial position
                    data->player.x = j * data->cell_size + data->cell_size / 2;
                    data->player.y = i * data->cell_size + data->cell_size / 2;
                    color = EMPTY_COLOR; // Set the cell to empty after placing the player
                    if (data->map.map_data[i][j] == 'N') data->player.angle = 3 * PI / 2;
                    if (data->map.map_data[i][j] == 'S') data->player.angle = PI / 2;
                    if (data->map.map_data[i][j] == 'W') data->player.angle = PI;
                    if (data->map.map_data[i][j] == 'E') data->player.angle = 0;
                    data->map.map_data[i][j] = '0'; // Clear the initial position marker
                }
                draw_square(data, j * data->cell_size, i * data->cell_size, data->cell_size, color);
            }
        }
    }
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1) {
        put_pixel(data, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void cast_ray(t_data *data) {
    int x0 = data->player.x;
    int y0 = data->player.y;
    double fov = 33.0 * PI / 180.0; // 33 degrees to radians
    int num_rays = 180; // Number of rays to cast
    double angle_step = fov / num_rays;
    double ray_angle;

    for (int i = -num_rays / 2; i <= num_rays / 2; i++) {
        ray_angle = data->player.angle + i * angle_step;
        double ray_x = x0;
        double ray_y = y0;
        double ray_dx = cos(ray_angle);
        double ray_dy = sin(ray_angle);

        int ray_length = data->player.ray_length;

        for (int j = 0; j < ray_length; j++) {
            ray_x += ray_dx;
            ray_y += ray_dy;

            int map_x = (int)(ray_x / data->cell_size);
            int map_y = (int)(ray_y / data->cell_size);

            // Check if ray is out of bounds
            if (map_x < 0 || map_x >= (int)data->map.map_width || map_y < 0 || map_y >= (int)data->map.map_height) {
                break;
            }

            // Check if ray hits a wall
            if (data->map.map_data[map_y][map_x] == '1') {
                draw_line(data, x0, y0, (int)ray_x, (int)ray_y, PLAYER_COLOR);
                break;
            }
        }

        // If no wall was hit, draw the ray to its maximum length
        if (ray_x < x0 + ray_length * ray_dx && ray_y < y0 + ray_length * ray_dy) {
            draw_line(data, x0, y0, (int)ray_x, (int)ray_y, PLAYER_COLOR);
        }
    }
}





int render_background(t_data *data) {
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            put_pixel(data, x, y, GREY_COLOR);
        }
    }
    render_map(data);
    draw_player(data, data->player.x, data->player.y, data->player_size, PLAYER_COLOR);
    cast_ray(data); // Adjust player size
    mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
    return 0;
}

int close_window(t_data *data) {
    mlx_destroy_window(data->mlx, data->window);
    exit(0);
}

#include <math.h>

int key_hook(int keycode, t_data *data) {
    // printf("Key pressed: %d\n", keycode); // Debug print

    double move_step = data->cell_size / 1.5; // Dynamic move step, ensure it's a double
    double rot_step = PI / 10; // Rotation step

    // Save the original position
    int original_x = data->player.x;
    int original_y = data->player.y;

    if (keycode == 65307) // ESC key code on MacOS
        close_window(data);
    else if (keycode == 65361) // Left arrow key for rotation
        data->player.angle -= rot_step;
    else if (keycode == 65363) // Right arrow key for rotation
        data->player.angle += rot_step;
    else if (keycode == 65362 || keycode == 119) { // Up arrow key or 'w' key
        // Move forward
        data->player.x += (int)(move_step * cos(data->player.angle));
        data->player.y += (int)(move_step * sin(data->player.angle));
    } else if (keycode == 65364 || keycode == 115) { // Down arrow key or 's' key
        // Move backward
        data->player.x -= (int)(move_step * cos(data->player.angle));
        data->player.y -= (int)(move_step * sin(data->player.angle));
    } else if (keycode == 97) { // 'a' key for left strafe
        // Move left (strafe)
        data->player.x += (int)(move_step * cos(data->player.angle - PI / 2));
        data->player.y += (int)(move_step * sin(data->player.angle - PI / 2));
    } else if (keycode == 100) { // 'd' key for right strafe
        // Move right (strafe)
        data->player.x += (int)(move_step * cos(data->player.angle + PI / 2));
        data->player.y += (int)(move_step * sin(data->player.angle + PI / 2));
    }

    // Calculate the player's bounding box
    int half_size = data->player_size / 2;
    int left_x = (data->player.x - half_size) / data->cell_size;
    int right_x = (data->player.x + half_size) / data->cell_size;
    int top_y = (data->player.y - half_size) / data->cell_size;
    int bottom_y = (data->player.y + half_size) / data->cell_size;

    // Ensure the new position is not within a wall
    if (!(left_x >= 0 && right_x < (int)data->map.map_width &&
          top_y >= 0 && bottom_y < (int)data->map.map_height &&
          data->map.map_data[top_y][left_x] != '1' &&
          data->map.map_data[top_y][right_x] != '1' &&
          data->map.map_data[bottom_y][left_x] != '1' &&
          data->map.map_data[bottom_y][right_x] != '1')) {
        // Revert to original position if new position is invalid
        data->player.x = original_x;
        data->player.y = original_y;
    }

    // printf("Player position after move: (%d, %d)\n", data->player.x, data->player.y);

    // Re-render the background and map after moving the player
    render_background(data);
    return 0;
}




int main() {
    t_data data;
    // Initialize player movement flags
    data.player.move_forward = 0;
    data.player.move_backward = 0;
    data.player.rotate_left = 0;
    data.player.rotate_right = 0;

    data.mlx = mlx_init();
    if (data.mlx == NULL) {
        fprintf(stderr, "Failed to initialize mlx\n");
        return EXIT_FAILURE;
    }

    data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Grey Background");
    if (data.window == NULL) {
        fprintf(stderr, "Failed to create window\n");
        return EXIT_FAILURE;
    }

    data.image = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (data.image == NULL) {
        fprintf(stderr, "Failed to create image\n");
        return EXIT_FAILURE;
    }

    data.addr = mlx_get_data_addr(data.image, &data.bits_per_pixel, &data.line_length, &data.endian);
    if (data.addr == NULL) {
        fprintf(stderr, "Failed to get image data address\n");
        return EXIT_FAILURE;
    }

    map_reading(&data.map);

    // Calculate the cell size based on the map and window dimensions
    int cell_size_width = WINDOW_WIDTH / data.map.map_width;
    int cell_size_height = WINDOW_HEIGHT / data.map.map_height;
    data.cell_size = (cell_size_width < cell_size_height) ? cell_size_width : cell_size_height;
    // data.player.ray_length = ((data.map.map_width < data.map.map_height) ? data.map.map_width : data.map.map_height) * data.cell_size;
    // Initialize player size based on cell size
    data.player_size = data.cell_size / 3;
    data.player.ray_length = data.cell_size * 100;

    render_background(&data);

    mlx_hook(data.window, 17, 0, close_window, &data);
    mlx_key_hook(data.window, key_hook, &data); // Use key_hook for key press handling
    mlx_loop(data.mlx);

    // Free the map data before exiting
    freeMap(&data.map);

    return 0;
}








