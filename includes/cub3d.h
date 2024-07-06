/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vadimhrabrov <vadimhrabrov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:19:54 by ccarrace          #+#    #+#             */
/*   Updated: 2024/07/06 02:23:27 by vadimhrabro      ###   ########.fr       */
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

// /* --- Define preprocessor directives ------------------------------------ */

// #define SUCCESS 1
// #define FAIL 0

/* --- Enum definitions ----------------------------------------------------- */

typedef enum 
{
    FAIL = 0,
    SUCCESS = 1
} result;

typedef enum
{
	FALSE = 0,
	TRUE = 1
} boolean;

/* --- ANSI escape codes ---------------------------------------------------- */

# define GREEN "\033[1;92m"	//	bold bright green
# define RED "\033[1;91m"	//	bold bright red
# define BCK_RED "\033[0;101m"	//	background bright red
# define YELLOW "\033[1;93m"	//	bold bright yellow
# define RESET "\x1B[0m"   // resets all terminal attributes to default settings

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
// #define WINDOW_WIDTH 1024
// #define WINDOW_HEIGHT 768
#define GREY_COLOR 0x808080
#define PLAYER_COLOR 0xFF0000 // Red color for the player
// #define PLAYER_SIZE 8  // Half-size of the player square
#define MOVE_STEP WINDOW_WIDTH/100 // Step size for player movement
#define WALL_COLOR 0xFFFFFF // White color for walls
#define BLUE_COLOR 0x0000FF
#define EMPTY_COLOR 0x000000 // Black color for empty space
#define PI 3.14159265359
#define CEILING_COLOR 0x87CEEB // Light blue color for ceiling (135,206,235)
#define FLOOR_COLOR 0x8B4513 // Brown color for floor (139,69,19)

#define MINIMAP_SCALE 4
// #define DEFAULT_CELL_SIZE 20 // Default size of each cell in the map

/* --- Data structures ------------------------------------------------------ */

typedef struct s_colors
{
    int floor[3];
    int ceiling[3];
    // int red;
    // int green;
    // int blue;
	unsigned int hex_floor;
	unsigned int hex_ceiling;
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
	char		**visited_array;
	size_t		visited_height;
	size_t		visited_width;
	size_t		player_x;
	size_t		player_y;
	char		player_orientation;
	// bool		closed;
	size_t		new_x;
	size_t		new_y;

    void *north_texture;
    void *south_texture;
    void *west_texture;
    void *east_texture;
    t_colors floor_color;
    t_colors ceiling_color;
    // char** map_data;
    // size_t map_height;
    // size_t map_width;
}	t_map;

typedef struct s_textures
{
	char	*north;
    char	*south;
    char	*west;
    char	*east;
	char	**array[4];
	char	*texture_ids[4];

    void *img;
    char *addr;
    int width;
    int height;
    int bits_per_pixel;
    int line_length;
    int endian;
}	t_textures;

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
    t_colors colors;
    int cell_size;
    int player_size;
    // t_texture wall_texture;
    t_textures north_texture;
    t_textures south_texture;
    t_textures west_texture;
    t_textures east_texture;
    int minimap_scale;
    int minimap_cell_size;
    int offset_x;
    int offset_y;
    struct timespec prev_time; // Add this line

	int	minimap_x;
	int	minimap_y;
} t_data;

/* === Functions ============================================================ */

//	main.c
// int 	engine_main(t_data *data, t_textures *textures);
int		main(int argc, char **argv);

/* --- Init ----------------------------------------------------------------- */

//	init.c
void	init_map(t_data *data, char *map_file);
void  	init_textures(t_textures *textures);
void  	init_colors(t_data *data);

/* --- Parse ---------------------------------------------------------------- */

//	check_file
boolean is_directory(char *str);
boolean can_open_file(char *str);
result	file_check(char *file_name);

//	find_map_dimensions.c
result	find_map_dimensions(t_data *data);

//	check_scene_description
result	check_scene_description(t_data *data);

//	check_textures.c
result	check_textures(t_data *data, t_textures *textures);

//	check_colors.c
result	check_colors(t_data *data);

//	check_player.c
boolean all_chars_are_valid(t_data *data);
result	check_player(t_data *data);

//	create_arrays.c
// void	allocate_map_array(t_map *map);
// result	fill_map_array(t_map *map);
// void	allocate_visited_array(t_map *map);
// void	fill_visited_array(t_map *map);
result	create_arrays(t_data *data);

//	check_walls.c
// void	print_visited_map(t_map *map);
// void	dfs(t_map *map, int row, int column);
// boolean	is_map_closed(t_map *map);
// boolean	is_fully_walkable(t_map *map);
result	check_walls(t_data *data);

//	parse_utils.c
int		is_file_type_valid(char *filename, char *expected_extension);
void 	free_array(char **array, size_t height);
void	free_rgb_values(char **rgb_array);
int 	is_valid_number(const char *str);
size_t	find_file_length(char *file);

//	parse_utils2.c
int		is_whitespace(char c);
void	trim_and_reduce_spaces(char *line);

//	reading_utils.c
int 	open_file(const char *file_path);
void	read_until_line(int fd, char **line, int endline_index);
void	read_until_end_of_file(int fd, char **line);

/* --- Debug ------------------------------------------------------- */

//	debug.c
void	print_map_array(char **array, size_t height, size_t width);

#endif
