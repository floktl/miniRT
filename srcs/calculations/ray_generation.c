/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 09:33:40 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3d	calculate_camera_vectors(t_app *app)
{
	t_vec3d	right;
	t_vec3d	up;
	t_vec3d	forward;

	forward = app->scene.camera.direction;
	up = app->scene.camera.up;
	right = vec_cross(forward, up);
	right = vec_normalize(right);
	return (right);
}

static t_vec3d	calculate_pixel_world_pos(t_app *app, int x, int y)
{
	t_vec3d	pixel_world;
	double	aspect_ratio;
	double	fov_scale;

	aspect_ratio = (double)app->window.width / (double)app->window.height;
	fov_scale = tan(app->scene.camera.fov * M_PI / 360.0);
	pixel_world.x = (2.0 * (x + 0.5) / app->window.width - 1.0)
		* aspect_ratio * fov_scale;
	pixel_world.y = (1.0 - 2.0 * (y + 0.5) / app->window.height) * fov_scale;
	pixel_world.z = 0.0;
	return (pixel_world);
}

/*
** Generate a ray from camera through a specific pixel
** Variables:
**   - ray: Ray structure to be populated
**   - pixel_world: 3D world coordinates of the pixel
**   - right: Camera's right vector (X-axis)
**   - up: Camera's up vector (Y-axis)
**   - forward: Camera's forward direction (Z-axis)
** Return: Ray with origin at camera pos. and dir. pointing through pixel
*/
t_ray	get_ray(t_app *app, int x, int y)
{
	t_ray	ray;
	t_vec3d	pixel_world;
	t_vec3d	right;
	t_vec3d	up;
	t_vec3d	forward;

	right = calculate_camera_vectors(app);
	up = app->scene.camera.up;
	forward = app->scene.camera.direction;
	pixel_world = calculate_pixel_world_pos(app, x, y);
	ray.origin = app->scene.camera.position;
	ray.direction = vec_add(forward, vec_add(vec_mul(right, pixel_world.x),
				vec_mul(up, pixel_world.y)));
	ray.direction = vec_normalize(ray.direction);
	return (ray);
}
