static result	find_map_starting_line(t_data *data)
{
	int		fd;
	char	*line;

	fd = open_file(data->map.file);
	if (fd < 0)
		return (FAIL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (((line[0] != ' ' && line[0] != '1') || (line[0] == ' '
			&& ft_strchr(line, '1') == NULL)) && data->map.height == 0)
			++data->map.starting_line;
		else
			break ;
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (SUCCESS);
}


