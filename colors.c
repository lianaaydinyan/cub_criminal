/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:25:51 by marihovh          #+#    #+#             */
/*   Updated: 2024/02/21 13:05:46 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_color(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == 'F' || line[i] == 'C')
		return (1);
	return (0);
}

int	init_colors(char *line, t_data *data)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	skip_sp(&line);
	if (line[++i] == 'F' || line[i] == 'C')
	{
		if (line[i] == 'C')
			flag = 1;
		i++;
	}
	if (!line[i] || !(line[i] && (line[i] == ' ' || line[i] == '\t')))
		return (1);
	line += i;
	skip_sp(&line);
	if (tree_nb(line, data, flag))
		return (1);
	return (0);
}

int	first_color(char *line, int fd, t_data *data)
{
	if (init_colors(line, data))
		return (errorik(C_ERROR));
	line = get_next_line(fd);
	while (empty_line(line))
		line = get_next_line(fd);
	if (!line)
		return (errorik(E_ERROR));
	if (init_colors(line, data))
		return (errorik(C_ERROR));
	if (is_texture(line))
	{
		if (init_textures(&line, fd, data->textures, &data->to_map))
			return (1);
	}
	else
		return (errorik(T_ERROR));
	if (parce_map(fd, line, data))
		return (1);
	return (0);
}
