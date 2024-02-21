#include "../cub3d.h"

void skip_sp(char **line)
{
	while (*line && (**line == ' ' || **line == '\t'))
		(*line)++;
}

int can_be(char ch)
{
	return ((ch != '0' && ch != '1') && ch != ' ' && ch != '\n' && ch != 'N' && ch != 'S' && ch != 'E' && ch != 'W');
}

int direction(char ch)
{
	return (ch == 'S' || ch == 'W' || ch == 'E');
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int check_neighbor(char **map_c, int i, int j)
{
	if (!map_c[i][j - 1] || map_c[i][j - 1] == ' ' || map_c[i][j - 1] == '\n')
		return (1);
	if (!map_c[i][j + 1] || map_c[i][j + 1] == ' ' || map_c[i][j + 1] == '\n')
		return (1);
	if (!map_c[i + 1][j] || map_c[i + 1][j] == ' ' || map_c[i + 1][j] == '\n')
		return (1);
	if (!map_c[i - 1][j] || map_c[i - 1][j] == ' ' || map_c[i - 1][j] == '\n')
		return (1);
	return (0);
}