/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/06 12:08:06 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_sphere_center(t_object *obj, char **tokens, int *idx,
		int token_count);
int	parse_sphere_color(t_object *obj, char **tokens, int *idx, int token_count);
int	validate_sphere_data(t_object *obj, t_float_res dr);

/* Parses sphere diameter from tokens and converts to radius */
int	parse_sphere_diameter(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	t_float_res	dr;

	dr = parse_float_tokens(tokens, idx, token_count);
	if (!dr.success)
		return (cleanup_object_error(obj, "[Sphere] Failed to parse diameter"));
	obj->data.s_sphere.radius = dr.f / 2.0;
	return (0);
}

/* Parses optional sphere parameters like shininess and textures */
static int	parse_sphere_optional(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	if (parse_object_shininess(obj, tokens, idx, token_count))
		return (cleanup_object_error(obj, "[Sphere] Failed parse shininess"));
	if (parse_texture_type(obj, tokens, idx, token_count))
		return (cleanup_object_error(obj, "[Sphere] Failed parse txt type"));
	if (parse_texture_scale(obj, tokens, idx, token_count))
		return (cleanup_object_error(obj, "[Sphere] Failed parse txt scale"));
	return (0);
}

/* Parses complete sphere object from tokens and adds to scene */
int	parse_sphere(char **tokens, t_scene *scene)
{
	t_object	*obj;
	int			token_count;
	int			idx;
	t_float_res	dr;

	if (init_object_and_count(&obj, tokens, &token_count, &idx))
		return (1);
	obj->type = SPHERE;
	if (parse_sphere_center(obj, tokens, &idx, token_count))
		return (1);
	dr = parse_float_tokens(tokens, &idx, token_count);
	if (!dr.success)
		return (cleanup_object_error(obj, "[Sphere] Failed to parse diameter"));
	obj->data.s_sphere.radius = dr.f / 2.0;
	if (parse_sphere_color(obj, tokens, &idx, token_count))
		return (1);
	if (parse_sphere_optional(obj, tokens, &idx, token_count))
		return (1);
	if (validate_sphere_data(obj, dr))
		return (1);
	obj->is_light_sphere = false;
	obj->next = scene->objects;
	scene->objects = obj;
	return (0);
}
