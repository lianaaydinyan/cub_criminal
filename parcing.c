#include "../cub3d.h"

int tree_nb(char *line, t_data *data, int flag)
{
	int i;
	int j;
	int nb[3];

	j = 0;
	while (j < 3)
	{
		i = 0;
		while (line[i] != '\n' && line[i] >= '0' && line[i] <= '9')
			i++;
		if (line[i] != '\n' && line[i] != ' ' && line[i] != ',')
			return (1);
		nb[j] = ft_atoi(line);
		line += i;
		skip_sp(&line);
		if (any_invalid(&line, i, j))
			return (1);
		if (j == 2)
			line++;
		j++;
	}
	if (!flag)
		data->c = create_trgb(0, nb[0], nb[1], nb[2]);
	else
		data->f = create_trgb(0, nb[0], nb[1], nb[2]);
	return (0);
}

int check_map(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (data->map_c[++i])
	{
		j = -1;
		while (data->map_c[i][++j])
		{
			if (can_be(data->map_c[i][j]))
				return (1);
			data->nb += direction(data->map_c[i][j]);
			if (data->map_c[i][j] == 'N')
			{
				data->pos_x = i;
				data->pos_y = j;
				data->count++;
			}
			//chose path;
			if (data->map_c[i][j] == 'W' || data->map_c[i][j] == 'E' || data->map_c[i][j] == 'S' || data->map_c[i][j] == '0' || data->map_c[i][j] == 'N')
				if (check_neighbor(data->map_c, i, j))
					return (1);
		}
	}
	if (data->count != 1 || data->nb > 1)
		return (1);
	return (0);
}

int parce_map(int fd, char *line, t_data* data)
{
	int	i;

	i = 0;
	line = get_next_line(fd);
	data->to_map++;
	while (empty_line(line))
	{
		line = get_next_line(fd);
		data->to_map++;
	}
	if (!line)
		return (errorik(M_ERROR));
	while (line)
	{
		data->map_h++;
		line = get_next_line(fd);
		if (empty_line(line))
			break ;
	}
	close(fd);
	fd = open(data->filename, O_RDONLY);
	while (i++ < data->to_map)
	{
		line = get_next_line(fd);
	}
	i = 0;
	data->map_c = malloc(sizeof(char *) * data->map_h);
	while (i < data->map_h)
	{
		data->map_c[i++] = ft_strdup_t(line);
		line = get_next_line(fd);
	}
	data->size = data->map_h;
	data->map_c[i] = NULL;
	if (check_map(data))
		return (errorik(M_ERROR));
	to_int(data);
	return (0);
}

int	inner_map(int fd, t_data *data)
{
	char	*line;
	int		i;

	i = -1;
	line = get_next_line(fd);
	while (empty_line(line))
	{
		line = get_next_line(fd);
		data->to_map++;
	}
	if (line && is_texture(line))
	{
		if (first_texture(line, fd, data))
			return (1);
	}
	else if (line && is_color(line))
	{
		if (first_color(line, fd, data))
			return (1);
	}
	else
		return (errorik(E_ERROR));
	i = 0;
	while (data->map_c[i])
		printf("%s", data->map_c[i++]);
	return (0);
}

int	parcing(t_data *data, char **argv)
{
	char	*file_ext;
	int		fd;

	file_ext = argv[1];
	data->filename = ft_strdup(argv[1]);
	if (ft_strlen(file_ext) <= 4)
		return (errorik(F_ERROR));
	file_ext += ft_strlen(file_ext) - 4;
	if (ft_strncmp(file_ext, ".cub", 4))
		return (errorik(F_ERROR));
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (errorik(M_ERROR));
	if (inner_map(fd, data))
		return (1);
	return (0);
}
