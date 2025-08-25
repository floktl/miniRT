/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 17:58:59 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	color_invalid(t_color c, const char *raw)
{
	if (c.r == 0 && c.g == 0 && c.b == 0 && ft_strncmp(raw, "0,0,0", 5) != 0)
		return (1);
	return (0);
}

int	check_ambient_duplicate(t_scene *scene)
{
	if (scene->ambient.ratio != 0.0)
	{
		printf("[Ambient] Duplicate ambient element not allowed\n");
		return (1);
	}
	return (0);
}

int	validate_ambient_ratio(float ratio)
{
	if (ratio < 0 || ratio > 1)
	{
		printf("[Ambient][ERROR] Ratio out of range [0..1]\n");
		return (1);
	}
	return (0);
}

int	check_camera_duplicate(t_scene *scene)
{
	if (scene->camera.fov != 0.0)
	{
		printf("[Camera] Duplicate camera element not allowed\n");
		return (1);
	}
	return (0);
}

int	set_camera_data(t_scene *scene, t_vec3_res pr, t_vec3_res dr,
	t_float_res fr)
{
	scene->camera.position = pr.v;
	scene->camera.direction = vec_normalize(dr.v);
	scene->camera.fov = fr.f;
	if (validate_camera_fov(scene->camera.fov))
		return (1);
	return (0);
}
