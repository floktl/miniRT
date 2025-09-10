/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 15:12:10 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Validates cylinder data after all parameters are parsed */
static int	validate_cylinder_final(t_object *obj)
{
	t_float_res	dr;
	t_float_res	hr;

	dr = (t_float_res){obj->data.s_cylinder.radius * 2.0, 1};
	hr = (t_float_res){obj->data.s_cylinder.height, 1};
	return (validate_cylinder_data(obj, dr, hr));
}

/* Parses optional cylinder parameters like shininess and textures */
static int	parse_cylinder_optional(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	if (parse_object_shininess(obj, tokens, idx, token_count))
		return (cleanup_object_error(obj, "[Cylinder] Failed parse shininess"));
	if (parse_texture_type(obj, tokens, idx, token_count))
		return (cleanup_object_error(obj, "[Cylinder] Failed parse txt type"));
	if (parse_texture_scale(obj, tokens, idx, token_count))
		return (cleanup_object_error(obj, "[Cylinder] Failed parse txt scale"));
	return (0);
}

/* Parses complete cylinder object from tokens and adds to scene */
int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_object	*obj;
	int			token_count;
	int			idx;

	if (init_object_and_count(&obj, tokens, &token_count, &idx))
		return (1);
	obj->type = CYLINDER;
	if (parse_cylinder_base(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cylinder] Failed to parse base"));
	if (parse_cylinder_axis(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cylinder] Failed to parse axis"));
	if (parse_cylinder_dimensions(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cylinder] Failed to parse dimen."));
	if (parse_cylinder_color(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cylinder] Failed to parse color"));
	if (parse_cylinder_optional(obj, tokens, &idx, token_count))
		return (1);
	if (validate_cylinder_final(obj))
		return (cleanup_object_error(obj, "[Cylinder] Validation failed"));
	obj->next = scene->objects;
	scene->objects = obj;
	return (0);
}
