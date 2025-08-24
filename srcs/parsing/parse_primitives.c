/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_primitives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:07:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 16:45:49 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	cleanup_object_error(t_object *obj, const char *message)
{
	printf("[Object] %s\n", message);
	free(obj);
	return (1);
}

static int	validate_cylinder_final(t_object *obj)
{
	float_res	dr;
	float_res	hr;

	dr = (float_res){obj->data.s_cylinder.radius * 2.0, 1};
	hr = (float_res){obj->data.s_cylinder.height, 1};
	return (validate_cylinder_data(obj, dr, hr));
}

int	parse_sphere(char **tokens, t_scene *scene)
{
	t_object	*obj;
	int			token_count;
	int			idx;
	float_res	dr;

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
	if (validate_sphere_data(obj, dr))
		return (cleanup_object_error(obj, "[Sphere] Validation failed"));
	obj->next = scene->objects;
	scene->objects = obj;
	return (0);
}

int	parse_plane(char **tokens, t_scene *scene)
{
	t_object	*obj;
	int			token_count;
	int			idx;

	if (init_object_and_count(&obj, tokens, &token_count, &idx))
		return (1);
	obj->type = PLANE;
	if (parse_plane_point(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Plane] Failed to parse point"));
	if (parse_plane_normal(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Plane] Failed to parse normal"));
	if (parse_plane_color(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Plane] Failed to parse color"));
	obj->next = scene->objects;
	scene->objects = obj;
	return (0);
}

int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_object		*obj;
	int				token_count;
	int				idx;

	if (init_object_and_count(&obj, tokens, &token_count, &idx))
		return (1);
	obj->type = CYLINDER;
	if (parse_cylinder_base(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cylinder] Failed to parse base"));
	if (parse_cylinder_axis(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cylinder] Failed to parse axis"));
	if (parse_cylinder_dimensions(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cylinder] Failed to parse dimensions"));
	if (parse_cylinder_color(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cylinder] Failed to parse color"));
	if (validate_cylinder_final(obj))
		return (cleanup_object_error(obj, "[Cylinder] Validation failed"));
	obj->next = scene->objects;
	scene->objects = obj;
	return (0);
}
