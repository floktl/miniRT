/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/04 11:33:14 by fkeitel          ###   ########.fr       */
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

