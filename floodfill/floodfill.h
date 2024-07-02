#ifndef FLOODFILL_H
# define FLOODFILL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct	s_point
{
	int x;	//	column
	int y;	//	row
} t_point;

// void	flood_fill(char **tab, t_point size, t_point begin);
void	fill(char **tab, int row, int column, int map_height, int map_width);
int		is_closed(char **map_array, int map_height, int map_width);
int		has_non_reachable_areas(char **map_array, int map_height, int map_width);

#endif