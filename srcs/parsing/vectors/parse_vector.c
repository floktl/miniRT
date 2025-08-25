/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:38:17 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 13:40:24 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <math.h>

t_vec3	parse_vec3(char *str)
{
	char	**parts;
	t_vec3	vec;
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

int	is_vec_zero(t_vec3 v)
{
	return (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f);
}

int	is_vec_normalized(t_vec3 v)
{
	double	length;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (fabs(length - 1.0) < 0.0001);
}
