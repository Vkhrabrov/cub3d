/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:06:48 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/06/20 22:33:28 by vkhrabro         ###   ########.fr       */
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

void put_texture_pixel(t_data *data, int x, int y, int tex_x, int tex_y) {
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT && tex_x >= 0 && tex_x < data->wall_texture.width && tex_y >= 0 && tex_y < data->wall_texture.height) {
        char *src = data->wall_texture.addr + (tex_y * data->wall_texture.line_length + tex_x * (data->wall_texture.bits_per_pixel / 8));
        char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = *(unsigned int*)src;
    }
}

void render_map(t_data *data) {
    int minimap_scale = 4; // Scale down the minimap by this factor
    int minimap_cell_size = data->cell_size / minimap_scale;
    int offset_x = 30; // Position from the left
    int offset_y = WINDOW_HEIGHT - (data->map.map_height * minimap_cell_size) - 20; // Position from the bottom

    for (size_t i = 0; i < data->map.map_height; i++) {
        for (size_t j = 0; j < data->map.map_width; j++) {
            if (j < ft_strlen(data->map.map_data[i])) {
                int color = GREY_COLOR;
                if (data->map.map_data[i][j] == '1') {
                    color = WALL_COLOR;
                } else if (data->map.map_data[i][j] == '0') {
                    color = EMPTY_COLOR;
                } else if (ft_strchr("NSEW", data->map.map_data[i][j])) {
                    data->player.x = j * data->cell_size + data->cell_size / 2;
                    data->player.y = i * data->cell_size + data->cell_size / 2;
                    color = EMPTY_COLOR;
                    if (data->map.map_data[i][j] == 'N') data->player.angle = 3 * PI / 2;
                    if (data->map.map_data[i][j] == 'S') data->player.angle = PI / 2;
                    if (data->map.map_data[i][j] == 'W') data->player.angle = PI;
                    if (data->map.map_data[i][j] == 'E') data->player.angle = 0;
                    data->map.map_data[i][j] = '0';
                }
                draw_square(data, offset_x + j * minimap_cell_size, offset_y + i * minimap_cell_size, minimap_cell_size, color);
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
    int minimap_scale = 4;
    int offset_x = 30;
    int offset_y = WINDOW_HEIGHT - (data->map.map_height * (data->cell_size / minimap_scale)) - 20;

    for (int i = -num_rays / 2; i <= num_rays / 2; i++) {
        ray_angle = data->player.angle + i * angle_step;
        double ray_x = x0;
        double ray_y = y0;
        double ray_dx = cos(ray_angle);
        double ray_dy = sin(ray_angle);

        int ray_length = data->player.ray_length;
        int j;

        for (j = 0; j < ray_length; j++) {
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
                draw_line(data, x0 / minimap_scale + offset_x, y0 / minimap_scale + offset_y, (int)ray_x / minimap_scale + offset_x, (int)ray_y / minimap_scale + offset_y, PLAYER_COLOR);
                break;
            }
        }

        // If no wall was hit, draw the ray to its maximum length
        if (j >= ray_length) {
            draw_line(data, x0 / minimap_scale + offset_x, y0 / minimap_scale + offset_y, (int)ray_x / minimap_scale + offset_x, (int)ray_y / minimap_scale + offset_y, PLAYER_COLOR);
        }
    }
}

void render_3d_view(t_data *data) {
    int width = WINDOW_WIDTH;
    int height = WINDOW_HEIGHT;
    double fov = 60.0 * PI / 180.0; // Field of view in radians
    int num_rays = width; // One ray per column of the screen
    double angle_step = fov / num_rays;
    double start_angle = data->player.angle - fov / 2.0;
    
    double scale_factor = 80.0; // Scaling factor to make walls appear closer

    // Fill the top half with the ceiling color
    for (int y = 0; y < height / 2; y++) {
        for (int x = 0; x < width; x++) {
            put_pixel(data, x, y, CEILING_COLOR);
        }
    }

    // Fill the bottom half with the floor color
    for (int y = height / 2; y < height; y++) {
        for (int x = 0; x < width; x++) {
            put_pixel(data, x, y, FLOOR_COLOR);
        }
    }

    // Render the walls
    for (int x = 0; x < num_rays; x++) {
        double ray_angle = start_angle + x * angle_step;
        double ray_x = data->player.x;
        double ray_y = data->player.y;
        double ray_dx = cos(ray_angle);
        double ray_dy = sin(ray_angle);

        int hit = 0;
        double distance = 0;
        while (!hit) {
            ray_x += ray_dx;
            ray_y += ray_dy;
            distance += 1.0;  // Track the distance the ray has traveled

            int map_x = (int)(ray_x / data->cell_size);
            int map_y = (int)(ray_y / data->cell_size);

            // Check if ray is out of bounds
            if (map_x < 0 || map_x >= (int)data->map.map_width || map_y < 0 || map_y >= (int)data->map.map_height) {
                break;
            }

            // Check if ray hits a wall
            if (data->map.map_data[map_y][map_x] == '1') {
                hit = 1;
                double corrected_distance = distance * cos(ray_angle - data->player.angle); // Correct the fish-eye effect
                int wall_height = (int)((height / corrected_distance) * scale_factor);  // Calculate wall height with scaling factor

                // Calculate the texture coordinate
                double wall_hit_x = ray_x / data->cell_size - map_x;
                int tex_x = (int)(wall_hit_x * data->wall_texture.width);

                // Draw the wall slice with texture
                int draw_start = -wall_height / 2 + height / 2;
                int draw_end = wall_height / 2 + height / 2;
                int tex_y_step = data->wall_texture.height / wall_height;

                for (int y = draw_start; y < draw_end; y++) {
                    if (y >= 0 && y < height) {
                        int tex_y = (y - draw_start) * tex_y_step;
                        put_texture_pixel(data, x, y, tex_x, tex_y);
                    }
                }
                break;  // Ensure we exit after hitting a wall
            }
        }
    }
}







int render_background(t_data *data) {
    // Clear the screen
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            put_pixel(data, x, y, GREY_COLOR);
        }
    }

    render_3d_view(data); // Render the 3D view
    render_map(data); // Render the minimap (keeping your existing minimap rendering code)
    draw_player(data, data->player.x / 4 + 20, data->player.y / 4 + WINDOW_HEIGHT - (data->map.map_height * (data->cell_size / 4)) - 20, data->player_size / 4, PLAYER_COLOR); // Render the player on the minimap
    // cast_ray(data); // Cast rays for the minimap

    mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
    return 0;
}

int close_window(t_data *data) {
    mlx_destroy_window(data->mlx, data->window);
    exit(0);
}

int key_press(int keycode, t_data *data) {
    if (keycode == 65307) // ESC key code on MacOS
        close_window(data);
    else if (keycode == 65361) // Left arrow key for rotation
        data->player.rotate_left = 1;
    else if (keycode == 65363) // Right arrow key for rotation
        data->player.rotate_right = 1;
    else if (keycode == 65362 || keycode == 119) // Up arrow key or 'w' key
        data->player.move_forward = 1;
    else if (keycode == 65364 || keycode == 115) // Down arrow key or 's' key
        data->player.move_backward = 1;
    else if (keycode == 97) // 'a' key for left strafe
        data->player.strafe_left = 1;
    else if (keycode == 100) // 'd' key for right strafe
        data->player.strafe_right = 1;

    return 0;
}

int key_release(int keycode, t_data *data) {
    if (keycode == 65361) // Left arrow key for rotation
        data->player.rotate_left = 0;
    else if (keycode == 65363) // Right arrow key for rotation
        data->player.rotate_right = 0;
    else if (keycode == 65362 || keycode == 119) // Up arrow key or 'w' key
        data->player.move_forward = 0;
    else if (keycode == 65364 || keycode == 115) // Down arrow key or 's' key
        data->player.move_backward = 0;
    else if (keycode == 97) // 'a' key for left strafe
        data->player.strafe_left = 0;
    else if (keycode == 100) // 'd' key for right strafe
        data->player.strafe_right = 0;

    return 0;
}

void normalize_angle(double *angle) {
    while (*angle < 0) *angle += 2 * PI;
    while (*angle >= 2 * PI) *angle -= 2 * PI;
}

void update_player(t_data *data) {
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    double delta_time = (current_time.tv_sec - data->prev_time.tv_sec) + (current_time.tv_nsec - data->prev_time.tv_nsec) / 1e9;
    data->prev_time = current_time;

    double move_speed = data->cell_size * 15.0 * delta_time; // Adjust speed as needed
    double rot_speed = PI / 2.0 * delta_time; // Adjust rotation speed as needed

    // Save the original position
    double original_x = data->player.x;
    double original_y = data->player.y;

    if (data->player.rotate_left) {
        data->player.angle -= rot_speed;
        normalize_angle(&data->player.angle);
    }
    if (data->player.rotate_right) {
        data->player.angle += rot_speed;
        normalize_angle(&data->player.angle);
    }

    double cos_angle = cos(data->player.angle);
    double sin_angle = sin(data->player.angle);

    if (data->player.move_forward) {
        data->player.x += move_speed * cos_angle;
        data->player.y += move_speed * sin_angle;
    }
    if (data->player.move_backward) {
        data->player.x -= move_speed * cos_angle;
        data->player.y -= move_speed * sin_angle;
    }
    if (data->player.strafe_left) {
        data->player.x += move_speed * cos(data->player.angle - PI / 2);
        data->player.y += move_speed * sin(data->player.angle - PI / 2);
    }
    if (data->player.strafe_right) {
        data->player.x += move_speed * cos(data->player.angle + PI / 2);
        data->player.y += move_speed * sin(data->player.angle + PI / 2);
    }

    // Calculate the player's bounding box
    double half_size = data->player_size / 2.0;
    int left_x = ((data->player.x - half_size) / data->cell_size);
    int right_x = ((data->player.x + half_size) / data->cell_size);
    int top_y = ((data->player.y - half_size) / data->cell_size);
    int bottom_y = ((data->player.y + half_size) / data->cell_size);

    // Ensure the new position is not within a wall
    if (left_x >= 0 && right_x < (int)data->map.map_width &&
        top_y >= 0 && bottom_y < (int)data->map.map_height &&
        data->map.map_data[top_y][left_x] != '1' &&
        data->map.map_data[top_y][right_x] != '1' &&
        data->map.map_data[bottom_y][left_x] != '1' &&
        data->map.map_data[bottom_y][right_x] != '1') {
        // New position is valid, nothing to revert
    } else {
        // Revert to original position if new position is invalid
        data->player.x = original_x;
        data->player.y = original_y;
    }
}

int main_loop(t_data *data) {
    update_player(data);
    render_background(data);
    return 0;
}

int main() {
    t_data data;
    // Initialize player movement flags
    data.player.move_forward = 0;
    data.player.move_backward = 0;
    data.player.strafe_left = 0;
    data.player.strafe_right = 0;
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

    data.wall_texture.img = mlx_xpm_file_to_image(data.mlx, "/home/vkhrabro/Projects/cub3d_second/color_stone.xpm", &data.wall_texture.width, &data.wall_texture.height);
    if (!data.wall_texture.img) {
        fprintf(stderr, "Failed to load texture\n");
        return EXIT_FAILURE;
    }
    data.wall_texture.addr = mlx_get_data_addr(data.wall_texture.img, &data.wall_texture.bits_per_pixel, &data.wall_texture.line_length, &data.wall_texture.endian);
    map_reading(&data.map);
    // Calculate the cell size based on the map and window dimensions
    int cell_size_width = WINDOW_WIDTH / data.map.map_width;
    int cell_size_height = WINDOW_HEIGHT / data.map.map_height;
    data.cell_size = (cell_size_width < cell_size_height) ? cell_size_width : cell_size_height;
    data.player_size = data.cell_size / 2;
    data.player.ray_length = data.cell_size * 100;

    // Initialize prev_time
    clock_gettime(CLOCK_MONOTONIC, &data.prev_time);

    render_background(&data);

    mlx_hook(data.window, 17, 0, close_window, &data);
    mlx_hook(data.window, 2, 1L<<0, key_press, &data); // Handle key press
    mlx_hook(data.window, 3, 1L<<1, key_release, &data); // Handle key release
    mlx_loop_hook(data.mlx, main_loop, &data); // Main loop
    mlx_loop(data.mlx);

    // Free the map data before exiting
    freeMap(&data.map);

    return 0;
}












