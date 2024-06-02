/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:06:48 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/06/02 23:52:31 by vkhrabro         ###   ########.fr       */
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
        "11111111 1111111 111111111111"
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
                    data->map.map_data[i][j] = '0'; // Clear the initial position marker
                }
                draw_square(data, j * data->cell_size, i * data->cell_size, data->cell_size, color);
            }
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
    draw_player(data, data->player.x, data->player.y, data->cell_size / 4, PLAYER_COLOR); // Adjust player size
    mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
    return 0;
}

int close_window(t_data *data) {
    mlx_destroy_window(data->mlx, data->window);
    exit(0);
}

int key_hook(int keycode, t_data *data) {
    printf("Key pressed: %d\n", keycode); // Debug print

    int new_x = data->player.x;
    int new_y = data->player.y;

    if (keycode == 53) // ESC key code on MacOS
        close_window(data);
    else if (keycode == 123) // Left arrow key
        new_x -= MOVE_STEP;
    else if (keycode == 124) // Right arrow key
        new_x += MOVE_STEP;
    else if (keycode == 125) // Down arrow key
        new_y += MOVE_STEP;
    else if (keycode == 126) // Up arrow key
        new_y -= MOVE_STEP;

    printf("New position before bounds check: (%d, %d)\n", new_x, new_y);

    // Ensure the new position is within the map bounds
    int max_x = (int)(data->map.map_width * data->cell_size);
    int max_y = (int)(data->map.map_height * data->cell_size);
    if (new_x < 0) new_x = 0;
    if (new_x > max_x) new_x = max_x;
    if (new_y < 0) new_y = 0;
    if (new_y > max_y) new_y = max_y;

    // Ensure the new position is not within a wall
    int map_x = new_x / data->cell_size;
    int map_y = new_y / data->cell_size;
    if (data->map.map_data[map_y][map_x] != '1') {
        data->player.x = new_x;
        data->player.y = new_y;
    }

    printf("Player position after move: (%zu, %zu)\n", data->player.x, data->player.y);

    // Re-render the background and map after moving the player
    render_background(data);
    return 0;
}

int main() {
    t_data data;

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

    // Initialize player size based on cell size
    data.player_size = data.cell_size / 4;

    render_background(&data);

    mlx_hook(data.window, 17, 0, close_window, &data);
    mlx_key_hook(data.window, key_hook, &data);
    mlx_loop(data.mlx);

    // Free the map data before exiting
    freeMap(&data.map);

    return 0;
}







