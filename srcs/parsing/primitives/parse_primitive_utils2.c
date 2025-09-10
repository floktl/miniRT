/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_primitive_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:05:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/26 13:12:48 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Parses plane point position from tokens */
int	parse_plane_point(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	t_vec3d_res	pr;

	pr = parse_vec3d_tokens(tokens, idx, token_count);
	if (!pr.success)
		return (cleanup_object_error(obj, "[Plane] Failed to parse point"));
	obj->data.s_plane.point = pr.v;
	return (0);
}

/* Parses plane normal vector from tokens and validates it */
int	parse_plane_normal(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	t_vec3d_res	nr;

	nr = parse_vec3d_tokens(tokens, idx, token_count);
	if (!nr.success)
		return (cleanup_object_error(obj, "[Plane] Failed to parse normal"));
	if (validate_plane_normal(nr.v))
		return (cleanup_object_error(obj, "[Plane] Normal valid. failed"));
	obj->data.s_plane.normal = vec_normalize(nr.v);
	return (0);
}

/* Parses plane color from tokens */
int	parse_plane_color(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	t_clr_res	colr;

	colr = parse_color_tokens(tokens, idx, token_count);
	if (!colr.success)
		return (cleanup_object_error(obj, "[Plane] Failed to parse color"));
	obj->color = colr.c;
	return (0);
}

/* Parses cylinder base position from tokens */
int	parse_cylinder_base(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	t_vec3d_res	br;

	br = parse_vec3d_tokens(tokens, idx, token_count);
	if (!br.success)
		return (cleanup_object_error(obj, "[Cylinder] Failed to parse base"));
	obj->data.s_cylinder.base = br.v;
	return (0);
}

/* Parses cylinder axis direction from tokens and normalizes it */
int	parse_cylinder_axis(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	t_vec3d_res	ar;

	ar = parse_vec3d_tokens(tokens, idx, token_count);
	if (!ar.success)
		return (cleanup_object_error(obj, "[Cylinder] Failed to parse axis"));
	if (is_vec_zero(ar.v))
		return (cleanup_object_error(obj, "[Cylinder] Axs-vec can't be 0-len"));
	obj->data.s_cylinder.axis = vec_normalize(ar.v);
	return (0);
}
