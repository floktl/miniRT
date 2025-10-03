/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:30:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/03 21:00:14 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Parses cone center position from tokens */
int	parse_cone_center(t_object *obj, char **tokens, int *idx, int token_count)
{
	t_vec3d_res	center_res;

	center_res = parse_vec3d_tokens(tokens, idx, token_count);
	if (!center_res.success)
		return (1);
	obj->data.s_cone.center = center_res.v;
	obj->data.s_cone.vertex = center_res.v;
	return (0);
}

/* Parses cone axis direction from tokens and validates normalization */
int	parse_cone_axis(t_object *obj, char **tokens, int *idx, int token_count)
{
	t_vec3d_res	axis_res;

	axis_res = parse_vec3d_tokens(tokens, idx, token_count);
	if (!axis_res.success || !is_vec_normalized(axis_res.v))
		return (1);
	obj->data.s_cone.axis = axis_res.v;
	return (0);
}

/* Parses cone radius and height dimensions from tokens */
int	parse_cone_dimensions(t_object *obj, char **tokens, int *idx, int tok_cnt)
{
	t_float_res	radius_res;
	t_float_res	height_res;

	radius_res = parse_float_tokens(tokens, idx, tok_cnt);
	if (!radius_res.success)
		return (1);
	height_res = parse_float_tokens(tokens, idx, tok_cnt);
	if (!height_res.success)
		return (1);
	obj->data.s_cone.radius = radius_res.f;
	obj->data.s_cone.height = height_res.f;
	return (0);
}

/* Parses cone color from tokens */
int	parse_cone_color(t_object *obj, char **tokens, int *idx, int token_count)
{
	t_clr_res	colr;

	colr = parse_color_tokens(tokens, idx, token_count);
	if (!colr.success)
		return (1);
	obj->color = colr.c;
	return (0);
}

/* Validates cone radius and height are positive values */
int	validate_cone_data(t_object *obj)
{
	if (obj->data.s_cone.radius <= 0.0 || obj->data.s_cone.height <= 0.0)
		return (1);
	return (0);
}
