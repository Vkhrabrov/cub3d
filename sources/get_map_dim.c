// gcc get_map_dim.c libft/get_next_line.c -Llibft -lft -g

#include "cub3d.h"

int	count_columns(const char *str)
{
	// int	num_columns;

	// num_columns = 0;
	// while (str[num_columns])
	// 	num_columns++;
	// return (num_columns - 1);
	return (ft_strlen(str));
}

void	get_map_dim(char *file_name)
{
	int	fd;
	int	width;
	int length;
	char *line;
	int flag;

	fd = open(file_name, O_RDONLY, 0);
	line = "";
	flag = 0;
	width = 0;
	length = -1;

	while (line != NULL)
	{
		line = get_next_line(fd);
		if (flag == 0 && line)
		{
			width = count_columns(line);
			flag = 1;
		}
		length++;
		free(line);
	}
	free(line);
	close(fd);
	printf("map width is %d\n", width);
	printf("map length is %d\n", length);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("wrong args!\n");
		return (0);
	}
	get_map_dim(argv[1]);
	return (0);
}
