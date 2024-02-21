#include "../cub3d.h"

int set_texture(char *line, char **textures, int i)
{
	if (*(line + ft_strlen(line) - 1) == '\n')
		*(line + ft_strlen(line) - 1) = '\0';
	textures[i] = ft_strdup(line);
	if (!textures[i])
		return (T_ERROR);
	return (0);
}

int fill_textures(char *line, char **textures)
{	
	char **splited;
	int ret;

	ret = 0;
	splited = ft_split(line, ' ');
	if (!splited || !splited[0] || !splited[1] || (splited[2] && splited[2][0] != '\n'))
		return (T_ERROR);
	if (ft_strlen(splited[0]) > 2)
		return (T_ERROR);
	if (!ft_strncmp(splited[0], "NO", 2) && !textures[0])
		ret = set_texture(splited[1], textures, 0);
	else if (!ft_strncmp(splited[0], "SO", 2) && !textures[1])
		ret = set_texture(splited[1], textures, 1);
	else if (!ft_strncmp(splited[0], "WE", 2) && !textures[2])
		ret = set_texture(splited[1], textures, 2);
	else if (!ft_strncmp(splited[0], "EA", 2) && !textures[3])
		ret = set_texture(splited[1], textures, 3);
	else
		return (T_ERROR);
	return (ret);
}

int init_textures(char **line, int fd, char **textures, int *to_map)
{
	int i = -1;
	while (++i < 4)
	{
		if (!(*line) || fill_textures(*line, textures))
			return (errorik(T_ERROR));
		*line = get_next_line(fd);
		(*to_map)++;
		while (empty_line(*line))
		{
			*line = get_next_line(fd);
			(*to_map)++;
		}
	}
	return (0);
}

int first_texture(char *line, int fd, t_data *data)
{
	if (init_textures(&line, fd, data->textures, &data->to_map))
		return (1);
	if (line && is_color(line))
	{
		if (init_colors(line, data))
			return (errorik(C_ERROR));
		line = get_next_line(fd);
		while (empty_line(line) && ++data->to_map)
			line = get_next_line(fd);
		if (!line || init_colors(line, data))
			return (errorik(C_ERROR));
		data->to_map+=2;
	}
	else
		return (errorik(C_ERROR));
	if (parce_map(fd ,line, data))
		return (1);
	return (0);
}
