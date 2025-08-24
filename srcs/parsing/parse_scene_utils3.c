/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:02:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 14:43:17 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_ambient_color(char **tokens, int *idx, int token_count,
		color_res *cr)
{
	*cr = parse_color_tokens(tokens, idx, token_count);
	if (!(*cr).success || *idx != token_count)
		return (parse_error("Ambient", "Failed to parse color"));
	printf("[Ambient] Parsed color: r=%d g=%d b=%d\n", (*cr).c.r, (*cr).c.g,
		(*cr).c.b);
	return (0);
}

int	set_ambient_data(t_scene *scene, float_res fr, t_color col)
{
	if (validate_ambient_ratio(fr.f))
		return (1);
	scene->ambient.ratio = fr.f;
	scene->ambient.color = col;
	printf("[Ambient] OK (ratio=%f, color=%d,%d,%d)\n", fr.f, col.r, col.g,
		col.b);
	return (0);
}

int	parse_camera_position(char **tokens, int *idx, int token_count,
		vec3_res *pr)
{
	*pr = parse_vec3_tokens(tokens, idx, token_count);
	if (!(*pr).success)
		return (parse_error("Camera", "Failed to parse position"));
	return (0);
}

int	parse_camera_direction(char **tokens, int *idx, int token_count,
		vec3_res *dr)
{
	*dr = parse_vec3_tokens(tokens, idx, token_count);
	if (!(*dr).success)
		return (parse_error("Camera", "Failed to parse direction"));
	if (is_vec_zero((*dr).v))
		return (parse_error("Camera", "Dir-vect cannot be 0-len"));
	return (0);
}

int	parse_camera_fov(char **tokens, int *idx, int token_count,
		float_res *fr)
{
	*fr = parse_float_tokens(tokens, idx, token_count);
	if (!(*fr).success || *idx != token_count)
		return (parse_error("Camera", "Failed to parse FOV"));
	return (0);
}
