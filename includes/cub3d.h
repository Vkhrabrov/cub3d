/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:19:54 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/10 23:47:39 by ccarrace         ###   ########.fr       */
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
# define GREY_COLOR 0x808080
# define PLAYER_COLOR 0xFF0000 // Red color for the player
# define WALL_COLOR 0xFFFFFF // White color for walls
# define BLUE_COLOR 0x0000FF
# define EMPTY_COLOR 0x000000 // Black color for empty space
# define PI 3.14159265359
# define CEILING_COLOR 0x87CEEB // Light blue color for ceiling (135,206,235)
# define FLOOR_COLOR 0x8B4513 // Brown color for floor (139,69,19)
# define MINIMAP_SCALE 4
# define DEBUG_MODE 0

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

typedef struct s_moves
{
	double		delta_time;
	double		move_speed;
	double		rot_speed;
	double		cos_angle;
	double		sin_angle;
	double		new_x;
	double		new_y;
	double		half_size;
}	t_moves;

typedef struct s_render
{
	double		fov;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		plane_x;
	double		plane_y;
	double		ray_x;
	double		ray_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		d_dist_x;
	double		d_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	double		step;
	double		tex_pos;
}	t_render;

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
	int				i;
	int				j;
	int				color;
	int				minimap_cell_size;
	t_map			map;
	t_player		player;
	t_render		render;
	t_moves			moves;
	int				cell_size;
	int				player_size;
	t_textures		north_texture;
	t_textures		south_texture;
	t_textures		west_texture;
	t_textures		east_texture;
	t_textures		texture;
	struct timespec	prev_time;
	t_colors		colors;
	int				minimap_x;
	int				minimap_y;
	int				tex_x;
	int				tex_y;
}	t_data;

/* === Functions ============================================================ */

//	main.c
int				main(int argc, char **argv);
int				render_background(t_data *data);
int				main_loop(t_data *data);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
int				close_window(t_data *data);

/* --- Init ----------------------------------------------------------------- */

//	init.c
void			init_map(t_data *data, char *map_file);
void			init_textures(t_textures *textures);
void			init_colors(t_data *data);
void			initialize_game_data(t_data *data);
void			init(char *file_name, t_data *data, t_textures *textures);

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
t_result		is_map_last(t_data *data);

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
int				allocate_map_array(t_data *data);
t_result		fill_map_array(t_data *data);
int				allocate_visited(t_data *data);
void			fill_visited(t_data *data);

//	check_walls.c
t_result		check_walls(t_data *data);

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
int				free_all(t_textures *textures, t_map *map);
void			display_map_error(char *str, int code);

//	reading_utils.c
int				open_file(const char *file_path);
void			read_until_line(int fd, char **line, int endline_index);
t_result		read_until_end_of_file(int fd, char **line, t_result res);

/* --- Engine --------------------------------------------------------------- */

// player_move.c
void			rotate_player(t_data *data);
void			move_player(t_data *data);
void			strafe_player(t_data *data);
void			update_player_x(t_data *data);
void			update_player_y(t_data *data);
void			update_player(t_data *data);

int				is_wall(t_data *data, double x, double y);
void			normalize_angle(double *angle);
void			init_player(t_data *data);
void			init_minimap(t_data *data);
void			calculate_ray(t_data *data, int x);
void			init_player_movement(t_data *data);
void			render_background_colors(t_data *data);
void			render_map(t_data *data);
void			render_map_row(t_data *data);
int				render_background(t_data *data);
void			render_3d_view(t_data *data);
void			cast_ray(t_data *data);
int				close_window(t_data *data);
	// walls
void			render_wall(t_data *data, int x);
void			draw_textured_wall(t_data *data, int x);
void			select_texture(t_data *data);
void			process_map_cell(t_data *data);
void			calculate_wall_distance(t_data *data);
	// drawing
void			put_pixel(t_data *data, int x, int y, unsigned int color);
void			draw_square(t_data *data, int x, int y, int color);
void			draw_player(t_data *data, int x, int y, int size);
void			put_texture_pixel(t_data *data, int x, int y);
void			draw_map_square(t_data *data, int is_wall);
	// move
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
void			normalize_angle(double *angle);

/* --- Debug ---------------------------------------------------------------- */

//	debug.c
void			print_map_by_lines(char **array, size_t height, size_t width);
void			print_map_by_chars(char **array, size_t height, size_t width);
void			debug_x_collision(t_data *data, double new_x, double new_y);
void			debug_y_collision(t_data *data, double new_x, double new_y);

//	print_visited_map.c
void			display_checks(void);
void			print_visited_map(t_data *data);
#endif
