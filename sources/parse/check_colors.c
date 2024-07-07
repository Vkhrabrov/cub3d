/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:28:00 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 19:10:01 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_boolean	are_colors_defined(int *color_found)
{
	if (*color_found == 0)
	{
		printf("Error\nColors: Not defined in the file\n");
		return (FALSE);
	}
	else if (*color_found == 1)
	{
		printf("Error\nColors: Ceiling is wrong or missing\n");
		return (FALSE);
	}
	else if (*color_found == 2)
	{
		printf("Error\nColors: Floor is wrong or missing\n");
		return (FALSE);
	}
	else if (*color_found == 3)
		return (TRUE);
	else
		printf("Error\nColors: Only two colors needed\n");
	return (FALSE);
}

static t_boolean	rgb_triplet_is_valid(char **rgb_array, int *color)
{
	int	i;

	i = 0;
	while (rgb_array[i] != NULL && ft_strncmp(rgb_array[i], "\n", 1) && i < 3)
	{
		if (!(is_valid_number(rgb_array[i])))
		{
			printf("Error\nColor: ");
			printf("Negative value or non-numeric characters found\n");
			return (FALSE);
		}
		color[i] = ft_atoi(rgb_array[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			printf("Error\nColor: Parameter out of range found\n");
			return (FALSE);
		}
		i++;
	}
	if (i != 3 || rgb_array[i] != NULL)
	{
		printf("Error\nColor: RGB must have three parameters\n");
		return (FALSE);
	}
	return (TRUE);
}

static t_result	store_rgb_color(const char *line, int *color)
{
	char	**rgb_array;

	rgb_array = ft_split(line, ',');
	if (!rgb_array)
	{
		printf("Error\nFailed to split RGB values.\n");
		return (FAIL);
	}
	if (rgb_triplet_is_valid(rgb_array, color) == FALSE)
	{
		free_rgb_values(rgb_array);
		return (FAIL);
	}
	free_rgb_values(rgb_array);
	return (SUCCESS);
}

static t_result	process_color_line(t_data *data, char *line, int *colors_found)
{
	char			surface;
	int				*color;
	unsigned int	*hex_color;

	surface = *line;
	line++;
	while (*line == ' ' && *line != '\n')
		line++;
	if (surface == 'F')
	{
		color = data->colors.floor;
		hex_color = &data->colors.hex_floor;
		*colors_found += 1;
	}
	else
	{
		color = data->colors.ceiling;
		hex_color = &data->colors.hex_ceiling;
		*colors_found += 2;
	}
	if (store_rgb_color(line, color) != SUCCESS)
		return (FAIL);
	*hex_color = rgb_to_hex(color);
	return (SUCCESS);
}

t_result	check_colors(t_data *data)
{
	int		fd;
	char	*line;
	char	*original_line;
	int		colors_found;

	fd = open_file(data->map.file);
	if (fd < 0)
		return (FAIL);
	colors_found = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		trim_and_reduce_spaces(line);
		original_line = line;
		if ((*line == 'F' || *line == 'C')
			&& (process_color_line(data, line, &colors_found) == FAIL))
			return (FAIL);
		free(original_line);
		line = get_next_line(fd);
	}
	close(fd);
	if (are_colors_defined(&colors_found) == FALSE)
		return (FAIL);
	return (SUCCESS);
}
