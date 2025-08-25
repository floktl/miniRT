/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:10:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 09:43:58 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_sphere_center(t_object *obj, char **tokens, int *idx, int token_count)
{
	t_vec3_res	cr;

	cr = parse_vec3_tokens(tokens, idx, token_count);
	if (!cr.success)
		return (cleanup_object_error(obj, "[Sphere] Failed to parse center"));
	obj->data.s_sphere.center = cr.v;
	return (0);
}

int	parse_sphere_color(t_object *obj, char **tokens, int *idx, int token_count)
{
	t_clr_res	colr;

	colr = parse_color_tokens(tokens, idx, token_count);
	if (!colr.success)
		return (cleanup_object_error(obj, "[Sphere] Failed to parse color"));
	obj->color = colr.c;
	return (0);
}

int	validate_sphere_data(t_object *obj, t_float_res dr)
{
	if (dr.f <= 0)
		return (cleanup_object_error(obj, "[Sphere] Invalid diameter"));
	if (obj->data.s_sphere.radius <= 0)
		return (cleanup_object_error(obj, "[Sphere] Invalid radius"));
	return (0);
}
