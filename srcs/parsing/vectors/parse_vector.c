/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:38:17 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/26 13:12:48 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3d	parse_vec3d(char *str)
{
	char	**parts;
	t_vec3d	vec;
	int		i;

	parts = ft_split(str, ',');
	i = 0;
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3]
		|| ft_strlen(parts[0]) == 0 || ft_strlen(parts[1]) == 0
		|| ft_strlen(parts[2]) == 0)
	{
		while (parts && parts[i])
			free(parts[i++]);
		free(parts);
		return ((t_vec3d){0, 0, 0});
	}
	vec.x = ft_atof(parts[0]);
	vec.y = ft_atof(parts[1]);
	vec.z = ft_atof(parts[2]);
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (vec);
}

/* Checks if vector is zero vector */
int	is_vec_zero(t_vec3d v)
{
	return (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f);
}

/* Checks if vector is normalized (unit length) */
int	is_vec_normalized(t_vec3d v)
{
	double	length;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (fabs(length - 1.0) < 0.0001);
}
