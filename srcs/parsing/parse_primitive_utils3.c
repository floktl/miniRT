/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_primitive_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:06:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/25 09:43:58 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_cylinder_dimensions(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	t_float_res	dr;
	t_float_res	hr;

	dr = parse_float_tokens(tokens, idx, token_count);
	if (!dr.success)
	{
		return (cleanup_object_error(obj,
				"[Cylinder] Failed to parse diameter"));
	}
	obj->data.s_cylinder.radius = dr.f / 2.0;
	hr = parse_float_tokens(tokens, idx, token_count);
	if (!hr.success)
		return (cleanup_object_error(obj, "[Cylinder] Failed to parse height"));
	obj->data.s_cylinder.height = hr.f;
	return (0);
}

int	parse_cylinder_color(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	t_clr_res	colr;

	colr = parse_color_tokens(tokens, idx, token_count);
	if (!colr.success)
		return (cleanup_object_error(obj, "[Cylinder] Failed to parse color"));
	obj->color = colr.c;
	return (0);
}

int	validate_cylinder_data(t_object *obj, t_float_res dr, t_float_res hr)
{
	if (validate_cylinder_dimensions(dr.f, hr.f))
		return (cleanup_object_error(obj,
				"[Cylinder] Dimensions valid. failed"));
	if (obj->data.s_cylinder.radius <= 0 || obj->data.s_cylinder.height <= 0)
		return (cleanup_object_error(obj, "[Cylinder] Invalid dimensions"));
	return (0);
}
