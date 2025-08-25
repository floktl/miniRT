/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:30:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 09:43:58 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_cone_center(t_object *obj, char **tokens, int *idx, int token_count)
{
	t_vec3_res	center_res;

	center_res = parse_vec3_tokens(tokens, idx, token_count);
	if (!center_res.success)
		return (1);
	obj->data.s_cone.center = center_res.v;
	return (0);
}

int	parse_cone_axis(t_object *obj, char **tokens, int *idx, int token_count)
{
	t_vec3_res	axis_res;

	axis_res = parse_vec3_tokens(tokens, idx, token_count);
	if (!axis_res.success || !is_vec_normalized(axis_res.v))
		return (1);
	obj->data.s_cone.axis = axis_res.v;
	return (0);
}

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

int	parse_cone_color(t_object *obj, char **tokens, int *idx, int token_count)
{
	t_clr_res	colr;

	colr = parse_color_tokens(tokens, idx, token_count);
	if (!colr.success)
		return (1);
	obj->color = colr.c;
	return (0);
}

int	validate_cone_data(t_object *obj)
{
	if (obj->data.s_cone.radius <= 0.0 || obj->data.s_cone.height <= 0.0)
		return (1);
	return (0);
}
