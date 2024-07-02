#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <time.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"


typedef struct s_colors
{
    int floor[3];
    int ceiling[3];
    unsigned char red;
    unsigned char green;
    unsigned char blue;
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
	bool		closed;
	size_t		new_x;
	size_t		new_y;

    void *north_texture;
    void *south_texture;
    void *west_texture;
    void *east_texture;
    t_colors floor_color;
    t_colors ceiling_color;
}	t_map;

typedef struct s_textures
{
	char	*north;
    char	*south;
    char	*west;
    char	*east;
	char	**paths_array[4];
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
    int cell_size;
    int player_size;
    t_textures north_texture;
    t_textures south_texture;
    t_textures west_texture;
    t_textures east_texture;
    struct timespec prev_time; // Add this line
} t_data;
