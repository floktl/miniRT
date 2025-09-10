/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 15:22:04 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Validates color and cleans up memory on invalid color */
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

/* Validates color values are within valid RGB range */
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

/* Removes newline characters from string */
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

/* Trims whitespace from color part and allocates trimmed string */
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

/* Processes all color parts and trims whitespace from each */
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
