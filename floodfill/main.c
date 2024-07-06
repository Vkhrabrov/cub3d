/*
	- MARCA TODOS LOS CEROS VISITADOS, LOS ESPACIOS NO 
	- Arranca desde la esquina superior izquierda
*/

#include "floodfill.h"

char** allocate_map(char** map, int map_width, int map_height)
{
	char** new;

	new = malloc(sizeof(char*) * map_height);
	for (int i = 0; i < map_height; ++i)
	{
		new[i] = malloc(map_width + 2); // extra space to allocate null-termination
		for (int j = 0; j < map_width; ++j)
			new[i][j] = map[i][j];
		new[i][map_width] = '\0';
	}

	return new;
}

int main(void)
{
	// t_point size = {8, 5};
	char *map[] = {
		"             ",
		"  111111     ",
		" 100011001    ",
		" 100100011   ",
		" 10110N00011 ",
		" 111000001   ",
		"  1111111    "
		"             ",
	};
	// t_point size = {4, 3};	
	int	map_width = 12;
	int	map_height = 7;
	// char *map[] = {
	// 	"1111",
	// 	"1001",
	// 	"1111",
	// 	NULL
	// };

	char**  map_array = allocate_map(map, map_width, map_height);
	int	row = 0;
	while (row < map_height)
	{
		printf("%s\n", map_array[row]);
		row++;
	}
	printf("\n");

	//	Start the dfs search from the player's position (replace all
	//	walkable cells (that is, zeros) with '@')
	row = 4;
	while (row < map_height)
	{
		int	column = 6;
		while (column < map_width)
		{
			fill(map_array, row, column, map_height, map_width);
			column++;
		}
		map_array[row][column++] = '\0';
		row++;
	}

	//	Print visited map
	for (int i = 0; i < map_height; ++i)
		printf("%s\n", map_array[i]);


	//	Search if the map is closed (all visited cells ('@' should be
	//	adjacent to other visited cells or walls ('@', '1'), never to 
	//	a whitespace)
	if (!is_closed(map_array, map_height, map_width))
		printf("Error\nMap: Is not closed\n");
	else
		printf("Map is closed!\n");

	//	Search if the map has non-reachable parts in the map (any cell
	//	remaining with zero value after running dfs)
	if (!has_non_reachable_parts(map_array, map_height, map_width))
		printf("Warning: Map has non-reachable parts\n");
	else
		printf("Map is fully walkable!\n");

	return (0);
}