/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:26:49 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 15:12:10 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	cleanup_and_return_error(char **parts, char *clean_str,
	char **trimmed_parts)
{
	int	i;

	if (trimmed_parts)
	{
		i = 0;
		while (i < 3)
		{
			if (trimmed_parts[i])
				free(trimmed_parts[i]);
			i++;
		}
	}
	if (parts)
	{
		i = 0;
		while (parts[i])
			free(parts[i++]);
		free(parts);
	}
	if (clean_str)
		free(clean_str);
	return ((t_color){0, 0, 0});
}

static t_color	parse_color_internal(char *str)
{
	char	**parts;
	t_color	color;
	char	*trimmed_parts[3];
	char	*clean_str;

	clean_str = ft_strdup(str);
	if (!clean_str)
		return ((t_color){0, 0, 0});
	clean_newlines(clean_str);
	parts = ft_split(clean_str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3]
		|| ft_strlen(parts[0]) == 0 || ft_strlen(parts[1]) == 0
		|| ft_strlen(parts[2]) == 0)
		return (cleanup_and_return_error(parts, clean_str, NULL));
	if (!process_parts(parts, trimmed_parts)
		|| !validate_and_parse_parts(trimmed_parts, parts, clean_str))
		return (cleanup_and_return_error(parts, clean_str, trimmed_parts));
	color.r = ft_atoi(trimmed_parts[0]);
	color.g = ft_atoi(trimmed_parts[1]);
	color.b = ft_atoi(trimmed_parts[2]);
	cleanup_memory(trimmed_parts, parts, clean_str);
	if (validate_color_values(color))
		return ((t_color){0, 0, 0});
	return (color);
}

t_color	parse_color(char *str)
{
	return (parse_color_internal(str));
}

/* Checks if color is zero (black) */
int	is_color_zero(t_color c)
{
	return (c.r == 0 && c.g == 0 && c.b == 0);
}
