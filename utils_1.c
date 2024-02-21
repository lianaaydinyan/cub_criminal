#include "../cub3d.h"

int any_invalid(char **line, int i, int j)
{
	if ((*line[0] == '\n' && j != 2) || i == 0)
		return (1);
	if (*line[0] == ',' && j == 2)
		return (1);
	if (*line[0] == ',' &&  j != 2)
	{
		(*line)++;
		skip_sp(line);
		if (*line[0] == '\n')
			return (1);
	}
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	int	i;

	i = 0;
	
	if (keycode == 53)
	{
		ft_putstr_fd ("The session is over!\n", 1);
		mlx_destroy_window(data->mlx->ptr, data->mlx->win);
		exit(0);
	}
	return (0);
}

int	key_cross(int keycode)
{
	(void)keycode;
	ft_putstr_fd ("The session is over!\n", 1);
	exit(0);
}

