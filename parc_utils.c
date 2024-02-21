/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:28:12 by marihovh          #+#    #+#             */
/*   Updated: 2024/01/17 19:29:06 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n')
		return (1);
	return (0);
}

int	is_texture(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		return (1);
	return (0);
}

int	ft_strlen_t(const char *str)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\t')
			ret += 3;
		i++;
		ret++;
	}
	return (ret);
}

void	*ft_memcpy_t(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)dest;
	str2 = (unsigned char *)src;
	while (n--)
	{
		while (*str2 == '\t')
		{
			i = 0;
			while (i++ < 4)
				*str1++ = ' ';
			str2++;
		}
		*str1++ = *str2++;
	}
	return (dest);
}

char	*ft_strdup_t(const char *s1)
{
	int		i;
	int		len;
	char	*ptr;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen_t(s1) + 1;
	ptr = malloc(len * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr = ft_memcpy_t(ptr, s1, len);
	return (ptr);
}
