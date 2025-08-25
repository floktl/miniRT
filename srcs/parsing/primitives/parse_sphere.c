/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 19:06:22 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_sphere_center(t_object *obj, char **tokens, int *idx,
		int token_count);
int	parse_sphere_color(t_object *obj, char **tokens, int *idx, int token_count);
int	validate_sphere_data(t_object *obj, t_float_res dr);

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
		return (cleanup_object_error(obj, "[Sphere] Failed to parse center"));
	dr = parse_float_tokens(tokens, &idx, token_count);
	if (!dr.success)
		return (cleanup_object_error(obj, "[Sphere] Failed to parse diameter"));
	obj->data.s_sphere.radius = dr.f / 2.0;
	if (parse_sphere_color(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Sphere] Failed to parse color"));
	if (parse_sphere_optional(obj, tokens, &idx, token_count))
		return (1);
	if (validate_sphere_data(obj, dr))
		return (cleanup_object_error(obj, "[Sphere] Validation failed"));
	obj->next = scene->objects;
	scene->objects = obj;
	return (0);
}
