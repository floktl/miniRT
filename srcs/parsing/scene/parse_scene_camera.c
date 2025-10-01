/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/01 12:46:25 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_camera_duplicate(t_scene *scene)
{
	if (scene->camera.fov != 0.0)
	{
		printf("[Camera] Duplicate camera element not allowed\n");
		return (1);
	}
	return (0);
}

int	check_debug_camera_duplicate(t_scene *scene)
{
	if (scene->has_debug_camera)
	{
		printf("[Debug Camera] Duplicate debug camera element not allowed\n");
		return (1);
	}
	return (0);
}

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

int	set_debug_camera_data(t_scene *scene, t_vec3d_res pr, t_vec3d_res dr,
	t_float_res fr)
{
	t_vec3d	right;
	t_vec3d	up;

	scene->debug_camera.position = pr.v;
	scene->debug_camera.direction = vec_normalize(dr.v);
	scene->debug_camera.fov = fr.f;
	right = vec_cross(scene->debug_camera.direction, (t_vec3d){0, 1, 0});
	right = vec_normalize(right);
	up = vec_cross(right, scene->debug_camera.direction);
	scene->debug_camera.up = vec_normalize(up);
	scene->has_debug_camera = true;
	if (validate_camera_fov(scene->debug_camera.fov))
		return (1);
	return (0);
}
