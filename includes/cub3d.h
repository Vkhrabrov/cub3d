/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:19:54 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/07 22:40:46 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <time.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

/* --- Define preprocessor statements ------------------------------------ */

# define WINDOW_WIDTH 2048
# define WINDOW_HEIGHT 1536
// #define WINDOW_WIDTH 1024
// #define WINDOW_HEIGHT 768
# define GREY_COLOR 0x808080
# define PLAYER_COLOR 0xFF0000 // Red color for the player
# define MOVE_STEP WINDOW_WIDTH / 100 // Step size for player movement
# define WALL_COLOR 0xFFFFFF // White color for walls
# define BLUE_COLOR 0x0000FF
# define EMPTY_COLOR 0x000000 // Black color for empty space
# define PI 3.14159265359
# define CEILING_COLOR 0x87CEEB // Light blue color for ceiling (135,206,235)
# define FLOOR_COLOR 0x8B4513 // Brown color for floor (139,69,19)
# define INITIAL_ANGLE PI / 2
# define MINIMAP_SCALE 4

/* --- Enum definitions ----------------------------------------------------- */

typedef enum result
{
	FAIL = 0,
	SUCCESS = 1
}	t_result;

typedef enum boolean
{
	FALSE = 0,
	TRUE = 1
}	t_boolean;

/* --- ANSI escape codes ---------------------------------------------------- */

# define GREEN "\033[1;92m"	//	bold bright green
# define RED "\033[1;91m"	//	bold bright red
# define BCK_RED "\033[0;101m"	//	background bright red
# define YELLOW "\033[1;93m"	//	bold bright yellow
# define RESET "\x1B[0m"   // resets all terminal attributes to default settings

/* --- Data structures ------------------------------------------------------ */

typedef struct s_colors
{
	int				floor[3];
	int				ceiling[3];
	unsigned int	hex_floor;
	unsigned int	hex_ceiling;
}	t_colors;

typedef struct s_map
{
	char		*file;
	size_t		starting_line;
	size_t		ending_line;
	size_t		width;
	size_t		height;
	char		**array;
	size_t		i;
	size_t		j;
	char		**visited;
	size_t		visited_height;
	size_t		visited_width;
	size_t		player_x;
	size_t		player_y;
	char		player_orientation;
	size_t		new_x;
	size_t		new_y;
	void		*north_texture;
	void		*south_texture;
	void		*west_texture;
	void		*east_texture;
	t_colors	floor_color;
	t_colors	ceiling_color;
}	t_map;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	**array[4];
	char	*texture_ids[4];
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_textures;

typedef struct s_player
{
	float	x;
	float	y;
	double	angle;
	int		move_forward;
	int		move_backward;
	int		rotate_left;
	int		rotate_right;
	double	ray_length;
	int		strafe_left;
	int		strafe_right;
}	t_player;

typedef struct s_data
{
	void			*mlx;
	void			*window;
	void			*image;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int i;
	int j;
	int minimap_cell_size;
	t_map			map;
	t_player		player;
	int				cell_size;
	int				player_size;
	t_textures		north_texture;
	t_textures		south_texture;
	t_textures		west_texture;
	t_textures		east_texture;
	t_textures 		texture;
	struct timespec	prev_time;
	t_colors		colors;
	int				minimap_x;
	int				minimap_y;
	int tex_x;
	int tex_y;
}	t_data;

/* === Functions ============================================================ */

//	main.c
int				main(int argc, char **argv);

//	debug.c
void			print_map_by_lines(char **array, size_t height, size_t width);
void			print_map_by_chars(char **array, size_t height, size_t width);
void			debug_x_collision(t_data *data, double new_x, double new_y);
void			debug_y_collision(t_data *data, double new_x, double new_y);

/* --- Init ----------------------------------------------------------------- */

//	init.c
void			init_map(t_data *data, char *map_file);
void			init_textures(t_textures *textures);
void			init_colors(t_data *data);

/* --- Parse ---------------------------------------------------------------- */

//	check_file
t_boolean		is_directory(char *str);
t_boolean		can_open_file(char *str);
t_result		file_check(char *file_name);

//	find_map_dimensions.c
t_result		find_map_dimensions(t_data *data);

//	check_scene_description.c
t_result		check_scene_description(t_data *data);

//	check_scene_description2.c
t_result		find_textures_and_colors(t_data *data);
t_result		find_map(t_data *data);
t_boolean		is_map_empty(char *file);
t_boolean		is_map_last(t_data *data);

//	check_textures.c
t_result		check_textures(t_data *data, t_textures *textures);

//	check_textures2.c
t_result		store_texture_path(char *line, t_textures *textures);
t_result		create_textures_array(t_data *data, t_textures *textures);
t_boolean		are_all_textures_defined(t_textures *textures);
t_boolean		are_texture_paths_valid(t_textures *textures);
t_boolean		are_textures_unique(t_textures *textures);

//	check_colors.c
t_result		check_colors(t_data *data);

//	check_player.c
t_boolean		all_chars_are_valid(t_data *data);
t_result		check_player(t_data *data);

//	create_arrays.c
t_result		create_arrays(t_data *data);

//	create_arrays2.c
void			allocate_map_array(t_data *data);
t_result		fill_map_array(t_data *data);
void			allocate_visited(t_data *data);
void			fill_visited(t_data *data);

//	check_walls.c
t_result		check_walls(t_data *data);

//	check_walls2.c
void			start_dfs_search(t_data *data);
t_boolean		is_map_closed(t_data *data);
t_boolean		is_fully_walkable(t_data *data);

//	parse_utils.c
int				is_file_type_valid(char *filename, char *expected_extension);
void			free_array(char **array, size_t height);
void			free_rgb_values(char **rgb_array);
int				is_valid_number(const char *str);
size_t			find_file_length(char *file);

//	parse_utils2.c
int				is_whitespace(char c);
void			trim_and_reduce_spaces(char *line);

//	parse_utils3.c
unsigned int	rgb_to_hex(int *rgb_array);
int				find_min(int a, int b);

//	reading_utils.c
int				open_file(const char *file_path);
void			read_until_line(int fd, char **line, int endline_index);
void			read_until_end_of_file(int fd, char **line);

/* --- ?????? --------------------------------------------------------------- */
int				is_wall(t_data *data, double x, double y);

#endif
