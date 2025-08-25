/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:07:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 09:43:58 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient(char **tokens, t_scene *scene)
{
	int			token_count;
	int			idx;
	t_color		col;
	t_float_res	fr;
	t_clr_res	cr;

	if (check_ambient_duplicate(scene))
		return (1);
	count_and_init_tokens(tokens, &token_count, &idx);
	if (parse_ambient_ratio(tokens, &idx, token_count, &fr))
		return (1);
	if (parse_ambient_color(tokens, &idx, token_count, &cr))
		return (1);
	col = cr.c;
	return (set_ambient_data(scene, fr, col));
}

int	parse_camera(char **tokens, t_scene *scene)
{
	int				token_count;
	int				idx;
	t_vec3_res		pr;
	t_vec3_res		dr;
	t_float_res		fr;

	if (check_camera_duplicate(scene))
		return (1);
	count_and_init_tokens(tokens, &token_count, &idx);
	if (parse_camera_position(tokens, &idx, token_count, &pr))
		return (1);
	if (parse_camera_direction(tokens, &idx, token_count, &dr))
		return (1);
	if (parse_camera_fov(tokens, &idx, token_count, &fr))
		return (1);
	return (set_camera_data(scene, pr, dr, fr));
}

int	parse_light(char **tokens, t_scene *scene)
{
	return (parse_light_internal(tokens, scene));
}
