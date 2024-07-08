/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:59:38 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/08 18:51:37 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_window(t_data *data);
int key_press(int keycode, t_data *data);
int key_release(int keycode, t_data *data);
int main_loop(t_data *data);
int render_background(t_data *data);

t_result	check_args(int argc)
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

int	free_all(t_textures *textures, t_map *map)
{
	int	i;

	i = 0;
	if (textures->array != NULL)
	{
		while (i < 4)
		{
			if (*(textures->array[i]) != NULL)
			{
				free(*(textures->array[i]));
				*(textures->array[i]) =  NULL;
			}
			i++;
		}
	}
	if (map != NULL)
	{
		free_array(map->array, map->height);
		map->array = NULL;
		free_array(map->visited, (map->height + 2));
		map->visited = NULL;
	}
	return (0);
}

void initialize_game_data(t_data *data)
{
    data->player.x = 0.0f;
    data->player.y = 0.0f;
    data->player.angle = INITIAL_ANGLE;
    data->player.move_forward = 0;
    data->player.move_backward = 0;
    data->player.rotate_left = 0;
    data->player.rotate_right = 0;
    data->player.ray_length = 0.0;
    data->player.strafe_left = 0;
    data->player.strafe_right = 0;
    data->i = 0;
    // data->j = 0;

    data->mlx = mlx_init();
    data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
    data->image = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    data->addr = mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->line_length, &data->endian);
}

int texture_load_second(t_data *data, t_textures *textures)
{
    data->west_texture.img = mlx_xpm_file_to_image(data->mlx, 
        *(textures->array[3]), &data->west_texture.width,
        &data->west_texture.height);
    if (!data->west_texture.img) 
    {
        printf("Failed to load west texture\n");
        return EXIT_FAILURE;
    }
    data->west_texture.addr = mlx_get_data_addr(data->west_texture.img,
        &data->west_texture.bits_per_pixel, &data->west_texture.line_length,
        &data->west_texture.endian);
    data->east_texture.img = mlx_xpm_file_to_image(data->mlx,
        *(textures->array[2]), &data->east_texture.width,
        &data->east_texture.height);
    if (!data->east_texture.img) 
    {
        printf("Failed to load east texture\n");
        return EXIT_FAILURE;
    }
    data->east_texture.addr = mlx_get_data_addr(data->east_texture.img,
        &data->east_texture.bits_per_pixel, &data->east_texture.line_length,
        &data->east_texture.endian);
    return (0);
}


int texture_load_first(t_data *data, t_textures *textures)
{
    data->north_texture.img = mlx_xpm_file_to_image(data->mlx,
        *(textures->array[0]), &data->north_texture.width,
        &data->north_texture.height);
	if (!data->north_texture.img) 
    {
		printf("Failed to load north texture\n");
		return EXIT_FAILURE;
	}
	data->north_texture.addr = mlx_get_data_addr(data->north_texture.img,
        &data->north_texture.bits_per_pixel, &data->north_texture.line_length,
        &data->north_texture.endian);
    data->south_texture.img = mlx_xpm_file_to_image(data->mlx,
        *(textures->array[1]), &data->south_texture.width,
        &data->south_texture.height);
    if (!data->south_texture.img) 
    {
        printf("Failed to load south texture\n");
        return EXIT_FAILURE;
    }
    data->south_texture.addr = mlx_get_data_addr(data->south_texture.img,
        &data->south_texture.bits_per_pixel, &data->south_texture.line_length,
        &data->south_texture.endian);
    if (texture_load_second(data, textures) != 0)
        return EXIT_FAILURE;
    return 0;
}

t_result	initial_checks(t_data *data, t_textures *textures, int argc, char **argv)
{
	int cell_size_width;
	int cell_size_height;

    if (check_args(argc) == FAIL)
		return (FAIL);
    initialize_game_data(data);
	init(argv[1], data, textures);
	if (file_check(argv[1]) == FAIL || find_map_dimensions(data) == FAIL
	|| check_scene_description(data) == FAIL || check_colors(data) == FAIL)
		return (FAIL);
	if (check_textures(data, textures) == FAIL)
		return (free_all(textures, NULL));
	create_arrays(data);
	if (check_player(data) == FAIL || check_walls(data) == FAIL)
		return (free_all(textures, &data->map));
    if (texture_load_first(data, textures) != 0)
        return EXIT_FAILURE;
    cell_size_width = WINDOW_WIDTH / data->map.width;
    cell_size_height = WINDOW_HEIGHT / data->map.height;
    data->cell_size = find_min(cell_size_width, cell_size_height);
    data->player_size = data->cell_size / 2;
    data->player.ray_length = data->cell_size * 100;
    return (SUCCESS);
}

int main(int argc, char **argv)
{
    t_textures	textures;
	t_data		data;

    if (initial_checks(&data, &textures, argc, argv) == FAIL)
        exit (1);
    render_background(&data);
    mlx_hook(data.window, 17, 0, close_window, &data);
    mlx_hook(data.window, 2, 1L<<0, key_press, &data); // Handle key press
    mlx_hook(data.window, 3, 1L<<1, key_release, &data); // Handle key release
    mlx_loop_hook(data.mlx, main_loop, &data); // Main loop
    mlx_loop(data.mlx);
	free_array(data.map.array, data.map.height);
	free_array(data.map.visited, (data.map.height + 2));
    return (0);
}
