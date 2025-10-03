/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_camera_rotation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/01 14:23:25 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Rotates debug camera horizontally (yaw) around the world up vector
 * Used for K/L key rotation controls
 * @param app: Pointer to application struct
 * @param angle: Rot angle in radians (positive = clockwise when look down)
 */
void	rotate_debug_camera_horizontal(t_app *app, double angle)
{
	t_vec3d	world_up;
	t_vec3d	right;
	t_vec3d	new_direction;

	if (!app->scene.has_debug_camera)
		return ;
	world_up = (t_vec3d){0, 1, 0};
	right = vec_cross(app->scene.debug_camera.direction, world_up);
	right = vec_normalize(right);
	new_direction.x = app->scene.debug_camera.direction.x * cos(angle)
		+ right.x * sin(angle);
	new_direction.y = app->scene.debug_camera.direction.y * cos(angle)
		+ right.y * sin(angle);
	new_direction.z = app->scene.debug_camera.direction.z * cos(angle)
		+ right.z * sin(angle);
	app->scene.debug_camera.direction = vec_normalize(new_direction);
	right = vec_cross(app->scene.debug_camera.direction, world_up);
	right = vec_normalize(right);
	app->scene.debug_camera.up = vec_cross(right,
			app->scene.debug_camera.direction);
	app->scene.debug_camera.up = vec_normalize(app->scene.debug_camera.up);
	app->render.needs_rerender = true;
}

/*
 * Rotates debug camera vertically (pitch) around the right vector
 * Used for I/N key rotation controls
 * @param app: Pointer to application struct
 * @param angle: Rotation angle in radians (positive = pitch up)
 */
void	rotate_debug_camera_vertical(t_app *app, double angle)
{
	t_vec3d	up;
	t_vec3d	right;
	t_vec3d	new_direction;
	t_vec3d	new_up;

	if (!app->scene.has_debug_camera)
		return ;
	up = app->scene.debug_camera.up;
	right = vec_cross(app->scene.debug_camera.direction, up);
	right = vec_normalize(right);
	new_direction.x = app->scene.debug_camera.direction.x * cos(angle)
		+ up.x * sin(angle);
	new_direction.y = app->scene.debug_camera.direction.y * cos(angle)
		+ up.y * sin(angle);
	new_direction.z = app->scene.debug_camera.direction.z * cos(angle)
		+ up.z * sin(angle);
	app->scene.debug_camera.direction = vec_normalize(new_direction);
	new_up = vec_cross(right, app->scene.debug_camera.direction);
	app->scene.debug_camera.up = vec_normalize(new_up);
	app->input.interaction_mode = true;
}

/*
 * Rotates debug camera around its forward axis (roll)
 * Used for additional rotation control
 * @param app: Pointer to application struct
 * @param angle: Rotation angle in radians (positive = roll clockwise)
 */
void	rotate_debug_camera_roll(t_app *app, double angle)
{
	t_vec3d	forward;
	t_vec3d	up;
	t_vec3d	right;
	t_vec3d	new_up;

	if (!app->scene.has_debug_camera)
		return ;
	forward = app->scene.debug_camera.direction;
	forward = vec_normalize(forward);
	up = app->scene.debug_camera.up;
	right = vec_cross(forward, up);
	right = vec_normalize(right);
	new_up.x = up.x * cos(angle) + right.x * sin(angle);
	new_up.y = up.y * cos(angle) + right.y * sin(angle);
	new_up.z = up.z * cos(angle) + right.z * sin(angle);
	app->scene.debug_camera.up = vec_normalize(new_up);
	app->input.interaction_mode = true;
}
