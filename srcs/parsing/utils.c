/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:26:49 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/19 14:14:12 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static t_color	validate_color(t_color color, char **parts)
{
	int	i;

	if (color.r < 0 || color.r > 255
		|| color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
	{
		i = 0;
		while (parts[i])
			free(parts[i++]);
		free(parts);
		return ((t_color){0, 0, 0});
	}
	return (color);
}

t_color	parse_color(char *str)
{
	char	**parts;
	int		i;
	t_color	color;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		i = 0;
		while (parts && parts[i])
			free(parts[i++]);
		free(parts);
		return ((t_color){0, 0, 0});
	}
	color.r = ft_atoi(parts[0]);
	color.g = ft_atoi(parts[1]);
	color.b = ft_atoi(parts[2]);
	color = validate_color(color, parts);
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (color);
}

t_vec3	parse_vec3(char *str)
{
	char	**parts;
	t_vec3	vec;
	int		i;

	parts = ft_split(str, ',');
	i = 0;
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		while (parts && parts[i])
			free(parts[i++]);
		free(parts);
		return ((t_vec3){0, 0, 0});
	}
	vec.x = ft_atof(parts[0]);
	vec.y = ft_atof(parts[1]);
	vec.z = ft_atof(parts[2]);
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (vec);
}
