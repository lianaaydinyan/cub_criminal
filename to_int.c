#include "../cub3d.h"

int	get_height(char **map)
{
	int		height;
	int		i = -1;

	height = 0;
	while (map[++i])
		height++;
	return (height);
}

int	get_max_width(char **map)
{
	int		widht;
	int max = 0;
	int i;

	i = -1;
	while (map[++i])
	{
		widht = ft_strlen(map[i]);
		if (max < widht)
			max = widht;
	}
	return (max);
}


void	to_int(t_data *data)
{
	int		i = -1;
	int j;

	// printf("%i\n", data->map_h);
	data->map = (int **)malloc(sizeof(int *) * (data->map_h));
	data->widht = get_max_width(data->map_c);
	// printf("%f\n", data->widht);
	while (++i < data->map_h)
		data->map[i] = (int *)malloc(sizeof(int *) * (data->widht));
	i = -1;
	while (data->map_c[++i])
	{
		j = -1;
		while (data->map_c[i][++j])
			data->map[i][j] = (int)data->map_c[i][j];
	}
}