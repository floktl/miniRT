/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_primitive_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 14:26:51 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	validate_plane_normal(t_vec3 normal)
{
	if (is_vec_zero(normal))
	{
		printf("[Plane] Normal vector cannot be zero-length\n");
		return (1);
	}
	if (!is_vec_normalized(normal))
	{
		printf("[Plane] Normal vector must be normalized\n");
		return (1);
	}
	return (0);
}

int	validate_cylinder_dimensions(float diameter, float height)
{
	if (diameter <= 0)
	{
		printf("[Cylinder] Diameter must be positive\n");
		return (1);
	}
	if (height <= 0)
	{
		printf("[Cylinder] Height must be positive\n");
		return (1);
	}
	return (0);
}

int	init_object_and_count(t_object **obj, char **tokens, int *token_count,
		int *idx)
{
	*token_count = 0;
	while (tokens[*token_count])
		(*token_count)++;
	*idx = 1;
	*obj = malloc(sizeof(t_object));
	if (!*obj)
		return (1);
	return (0);
}
