/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vadimhrabrov <vadimhrabrov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:59:38 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/06 02:00:55 by vadimhrabro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_window(t_data *data);
int key_press(int keycode, t_data *data);
int key_release(int keycode, t_data *data);
int main_loop(t_data *data);
int render_background(t_data *data);

result	check_args(int argc)
{
    if (argc!= 2)
    {
      printf("Error\nWrong arguments (usage: ./cub3d <path_to_file>)\n");
      return (FAIL);
    }
	return (SUCCESS);
}

void	init(char *file_name, t_data *data, t_textures *textures)
{
    init_map(data, file_name);
    init_textures(textures);
    init_colors(data);	
}

int	free_and_exit(t_textures *textures, t_map *map)
{
	free(textures->north);
	free(textures->south);
	free(textures->west);
	free(textures->east);
	free_array(map->array, map->height);
	free_array(map->visited_array, (map->height + 2));
	return (0);
}

int main(int argc, char **argv)
{
    t_map		map;
    t_textures	textures;
	t_data		data;

	if (check_args(argc) == FAIL)
		return (FAIL);
	init(argv[1], &data, &textures);
	if (file_check(argv[1]) == FAIL || find_map_dimensions(&data) == FAIL
	|| check_scene_description(&data) == FAIL || check_colors(&data) == FAIL)
		return (FAIL);
	// print_map_array(map.array, map.height, map.width);

    printf("Ceiling Color: 0x%X\n", data.colors.hex_ceiling);
    printf("Floor Color: 0x%X\n", data.colors.hex_floor);

	if (check_textures(&data, &textures) == 	FAIL)
	{	
		free(textures.north);
		free(textures.south);
		free(textures.west);
		free(textures.east);
		return (FAIL);
	}
	create_arrays(&data);
	if (check_player(&data) == FAIL)
		return (free_and_exit(&textures, &data.map));
	// print_map_array(map.visited_array, map.height + 2, map.width + 1);
	if (check_walls(&data) == FAIL)
		return (free_and_exit(&textures, &data.map));


	// engine_main(&data, &textures);

	data.player.move_forward = 0;
    data.player.move_backward = 0;
    data.player.strafe_left = 0;
    data.player.strafe_right = 0;
    data.player.rotate_left = 0;
    data.player.rotate_right = 0;

    // // Calculate the cell size based on the map and window dimensions
    // int cell_size_width = WINDOW_WIDTH / data.map.width;
    // int cell_size_height = WINDOW_HEIGHT / data.map.height;
    // data.cell_size = (cell_size_width < cell_size_height) ? cell_size_width : cell_size_height;
    // data.player_size = data.cell_size / 2;
    // data.player.ray_length = data.cell_size * 100;

    data.mlx = mlx_init();
    data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Grey Background");
    data.image = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    data.addr = mlx_get_data_addr(data.image, &data.bits_per_pixel, &data.line_length, &data.endian);
 
    // Load textures using map struct
	data.north_texture.img = mlx_xpm_file_to_image(data.mlx, *(textures.array[0]), &data.north_texture.width, &data.north_texture.height);
	if (!data.north_texture.img) {
		fprintf(stderr, "Failed to load north texture\n");
		return EXIT_FAILURE;
	}
	data.north_texture.addr = mlx_get_data_addr(data.north_texture.img, &data.north_texture.bits_per_pixel, &data.north_texture.line_length, &data.north_texture.endian);

    data.south_texture.img = mlx_xpm_file_to_image(data.mlx, *(textures.array[1]), &data.south_texture.width, &data.south_texture.height);
    if (!data.south_texture.img) {
        fprintf(stderr, "Failed to load south texture\n");
        return EXIT_FAILURE;
    }
    data.south_texture.addr = mlx_get_data_addr(data.south_texture.img, &data.south_texture.bits_per_pixel, &data.south_texture.line_length, &data.south_texture.endian);

    data.west_texture.img = mlx_xpm_file_to_image(data.mlx, *(textures.array[3]), &data.west_texture.width, &data.west_texture.height);
    if (!data.west_texture.img) {
        fprintf(stderr, "Failed to load west texture\n");
        return EXIT_FAILURE;
    }
    data.west_texture.addr = mlx_get_data_addr(data.west_texture.img, &data.west_texture.bits_per_pixel, &data.west_texture.line_length, &data.west_texture.endian);

    data.east_texture.img = mlx_xpm_file_to_image(data.mlx, *(textures.array[2]), &data.east_texture.width, &data.east_texture.height);
    if (!data.east_texture.img) {
        fprintf(stderr, "Failed to load east texture\n");
        return EXIT_FAILURE;
    }
    data.east_texture.addr = mlx_get_data_addr(data.east_texture.img, &data.east_texture.bits_per_pixel, &data.east_texture.line_length, &data.east_texture.endian);
    
    
//     // Calculate the cell size based on the map and window dimensions
    int cell_size_width = WINDOW_WIDTH / data.map.width;
    int cell_size_height = WINDOW_HEIGHT / data.map.height;
    data.cell_size = (cell_size_width < cell_size_height) ? cell_size_width : cell_size_height;
    data.player_size = data.cell_size / 2;
    data.player.ray_length = data.cell_size * 100;

// printf("map.height = %ld\n", map.height);
// printf("map.width =%ld\n", map.width);
// printf("data.map.height = %ld\n", data.map.height);
// printf("data.map.width = %ld\n", data.map.width);
// printf("map.player_x = %ld\n", map.player_x);
// printf("map.player_y = %ld\n", map.player_y);
// printf("data.map.player_x = %ld\n", data.map.player_x);
// printf("data.map.player_y = %ld\n", data.map.player_y);
// printf("data.cell_size = %d\n", data.cell_size);
// printf("data.player.x = %f\n", data.player.x);
// printf("data.player.y = %f\n", data.player.y);

    // Initialize prev_time
    // clock_gettime(CLOCK_MONOTONIC, &data.prev_time);
	
    render_background(&data);
	
    mlx_hook(data.window, 17, 0, close_window, &data);
    mlx_hook(data.window, 2, 1L<<0, key_press, &data); // Handle key press
    mlx_hook(data.window, 3, 1L<<1, key_release, &data); // Handle key release
	

    mlx_loop_hook(data.mlx, main_loop, &data); // Main loop

    mlx_loop(data.mlx);

	free_array(data.map.array, data.map.height);
	free_array(data.map.visited_array, (data.map.height + 2));
    return (0);
}
