/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_calculations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:03:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 09:47:08 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Calculate normalized screen coordinates from world point
** Math: Projects 3D world point to 2D normalized coordinates [-1,1]
** using camera's field of view and aspect ratio
** Returns: normalized coordinates (x,y) in range [-1,1]
*/
t_vec2d	calculate_normalized_coords(t_vec3d world_point, t_app *app)
{
	t_vec3d	relative;
	t_vec3d	right;
	double	aspect_ratio;
	double	fov_scale;
	t_vec2d	normalized;

	right = vec_cross(app->scene.camera.direction, app->scene.camera.up);
	right = vec_normalize(right);
	relative = vec_sub(world_point, app->scene.camera.position);
	aspect_ratio = (double)app->window.width / (double)app->window.height;
	fov_scale = tan(app->scene.camera.fov * M_PI / 360.0);
	normalized.x = vec_dot(relative, right) / (aspect_ratio * fov_scale);
	normalized.y = vec_dot(relative, app->scene.camera.up) / fov_scale;
	return (normalized);
}

/*
** Convert normalized coordinates to screen pixel coordinates
** Math: Maps normalized coords [-1,1] to screen pixels [0,width] x [0,height]
** Y-axis is flipped (1.0 - y) because screen Y increases downward
** Returns: screen position in pixels with depth information
*/
t_vec3d	normalized_to_screen_pixels(t_vec2d normalized,
		t_vec3d world_point, t_app *app)
{
	t_vec3d	screen_pos;
	t_vec3d	relative;

	relative = vec_sub(world_point, app->scene.camera.position);
	screen_pos.x = (normalized.x + 1.0) * app->window.width / 2.0;
	screen_pos.y = (1.0 - normalized.y) * app->window.height / 2.0;
	screen_pos.z = vec_dot(relative, app->scene.camera.direction);
	return (screen_pos);
}

/*
** Get world point from screen coordinates at given depth
** Math: Inverse projection from screen pixels to 3D world coordinates
** @param screen_x: X pixel coordinate
** @param screen_y: Y pixel coordinate
** @param depth: Distance from camera along view direction
** @param app: Application struct with camera data
** @return: 3D world point
*/
t_vec3d	screen_to_world_point(int screen_x, int screen_y, double depth,
			t_app *app)
{
	t_vec3d	right;
	t_vec3d	world_point;
	double	aspect_ratio;
	double	fov_scale;
	t_vec2d	normalized;

	right = vec_cross(app->scene.camera.direction, app->scene.camera.up);
	right = vec_normalize(right);
	aspect_ratio = (double)app->window.width / (double)app->window.height;
	fov_scale = tan(app->scene.camera.fov * M_PI / 360.0);
	normalized.x = (2.0 * screen_x / app->window.width) - 1.0;
	normalized.y = 1.0 - (2.0 * screen_y / app->window.height);
	world_point = vec_add(app->scene.camera.position,
			vec_mul(app->scene.camera.direction, depth));
	world_point = vec_add(world_point,
			vec_mul(right, normalized.x * aspect_ratio * fov_scale * depth));
	world_point = vec_add(world_point,
			vec_mul(app->scene.camera.up, normalized.y * fov_scale * depth));
	return (world_point);
}

/*
** Project a 3D world point to 2D screen coordinates using main camera
** Combines normalized coordinate calculation and pixel mapping
** Returns: screen position in pixels with depth information
*/
t_vec3d	project_world_to_screen(t_vec3d world_point, t_app *app)
{
	t_vec2d	normalized;
	t_vec3d	screen_pos;

	normalized = calculate_normalized_coords(world_point, app);
	screen_pos = normalized_to_screen_pixels(normalized, world_point, app);
	return (screen_pos);
}
