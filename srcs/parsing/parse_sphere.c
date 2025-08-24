/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:25:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 14:43:17 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	validate_sphere_diameter(float diameter)
{
	if (diameter <= 0)
	{
		printf("[Sphere] Diameter must be positive\n");
		return (1);
	}
	return (0);
}

int	parse_sphere_center(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	vec3_res	cr;

	cr = parse_vec3_tokens(tokens, idx, token_count);
	if (!cr.success)
		return (cleanup_object_error(obj, "[Sphere] Failed to parse center"));
	obj->data.s_sphere.center = cr.v;
	return (0);
}

int	parse_sphere_diameter(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	float_res	dr;

	dr = parse_float_tokens(tokens, idx, token_count);
	if (!dr.success)
		return (cleanup_object_error(obj, "[Sphere] Failed to parse diameter"));
	obj->data.s_sphere.radius = dr.f / 2.0;
	return (0);
}

int	parse_sphere_color(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	color_res	colr;

	colr = parse_color_tokens(tokens, idx, token_count);
	if (!colr.success || *idx != token_count)
		return (cleanup_object_error(obj, "[Sphere] Failed to parse color"));
	obj->color = colr.c;
	return (0);
}

int	validate_sphere_data(t_object *obj, float_res dr)
{
	if (validate_sphere_diameter(dr.f))
		return (cleanup_object_error(obj, "[Sphere] Diameter valid. failed"));
	if (obj->data.s_sphere.radius <= 0)
		return (cleanup_object_error(obj, "[Sphere] Invalid radius"));
	return (0);
}
