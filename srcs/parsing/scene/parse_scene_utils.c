/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:07:49 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Checks if color is invalid (zero but not explicitly 0,0,0) */
int	color_invalid(t_color c, const char *raw)
{
	if (c.r == 0 && c.g == 0 && c.b == 0 && ft_strncmp(raw, "0,0,0", 5) != 0)
		return (1);
	return (0);
}

/* Checks if ambient element already exists in scene */
int	check_ambient_duplicate(t_scene *scene)
{
	if (scene->ambient.ratio != 0.0)
	{
		printf("[Ambient] Duplicate ambient element not allowed\n");
		return (1);
	}
	return (0);
}

/* Validates ambient ratio is within valid range */
int	validate_ambient_ratio(float ratio)
{
	if (ratio < 0 || ratio > 1)
	{
		printf("[Ambient][ERROR] Ratio out of range [0..1]\n");
		return (1);
	}
	return (0);
}

/* Checks if camera element already exists in scene */
int	check_camera_duplicate(t_scene *scene)
{
	if (scene->camera.fov != 0.0)
	{
		printf("[Camera] Duplicate camera element not allowed\n");
		return (1);
	}
	return (0);
}

/* Sets camera data in scene after validation */
int	set_camera_data(t_scene *scene, t_vec3d_res pr, t_vec3d_res dr,
	t_float_res fr)
{
	t_vec3d	right;
	t_vec3d	up;

	scene->camera.position = pr.v;
	scene->camera.direction = vec_normalize(dr.v);
	scene->camera.fov = fr.f;
	right = vec_cross(scene->camera.direction, (t_vec3d){0, 1, 0});
	right = vec_normalize(right);
	up = vec_cross(right, scene->camera.direction);
	scene->camera.up = vec_normalize(up);
	if (validate_camera_fov(scene->camera.fov))
		return (1);
	return (0);
}
