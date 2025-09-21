/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_primitive_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 15:44:23 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Validates plane normal vector is non-zero and normalized */
int	validate_plane_normal(t_vec3d normal)
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

/* Validates cylinder diameter and height are positive values */
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

/* Initializes object struct and counts tokens for parsing */
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
	(*obj)->type = 0;
	(*obj)->next = NULL;
	(*obj)->shininess = 32.0;
	(*obj)->texture_type = TEXTURE_NONE;
	(*obj)->texture_scale = 1.0;
	(*obj)->is_light_sphere = false;
	return (0);
}
