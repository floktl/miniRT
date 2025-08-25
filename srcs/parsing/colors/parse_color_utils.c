/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 15:23:13 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	validate_color(t_color color, char **parts)
{
	int	i;

	if (color.r < 0 || color.r > 255
		|| color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
	{
		printf("color invalid");
		i = 0;
		while (parts[i])
			free(parts[i++]);
		free(parts);
		return ((t_color){0, 0, 0});
	}
	return (color);
}

int	validate_color_values(t_color c)
{
	if (c.r < 0 || c.r > 255)
		return (1);
	if (c.g < 0 || c.g > 255)
		return (1);
	if (c.b < 0 || c.b > 255)
		return (1);
	return (0);
}

int	clean_newlines(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			return (1);
		}
		i++;
	}
	return (0);
}

int	trim_part(char *part, char **trimmed)
{
	int	len;

	while (*part == ' ' || *part == '\t')
		part++;
	len = ft_strlen(part);
	while (len > 0 && (part[len - 1] == ' ' || part[len - 1] == '\t'))
		len--;
	*trimmed = malloc(len + 1);
	if (!*trimmed)
		return (0);
	ft_strlcpy(*trimmed, part, len + 1);
	return (1);
}

int	process_parts(char **parts, char **trimmed_parts)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!trim_part(parts[i], &trimmed_parts[i]))
		{
			while (i > 0)
			{
				i--;
				if (trimmed_parts[i])
					free(trimmed_parts[i]);
			}
			return (0);
		}
		i++;
	}
	return (1);
}
