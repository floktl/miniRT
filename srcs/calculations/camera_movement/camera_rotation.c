/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 09:02:49 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Rotates camera horizontally (yaw) around the up vector */
void	rotate_camera_horizontal(t_app *app, double angle)
{
	t_vec3d	up;
	t_vec3d	right;
	t_vec3d	new_direction;
	t_vec3d	new_up;

	up = app->scene.camera.up;
	right = vec_cross(app->scene.camera.direction, up);
	right = vec_normalize(right);
	new_direction.x = app->scene.camera.direction.x * cos(angle)
		+ right.x * sin(angle);
	new_direction.y = app->scene.camera.direction.y * cos(angle)
		+ right.y * sin(angle);
	new_direction.z = app->scene.camera.direction.z * cos(angle)
		+ right.z * sin(angle);
	app->scene.camera.direction = vec_normalize(new_direction);
	new_up = vec_cross(right, app->scene.camera.direction);
	app->scene.camera.up = vec_normalize(new_up);
	app->needs_rerender = true;
}

/* Rotates camera vertically (pitch) around the right vector */
void	rotate_camera_vertical(t_app *app, double angle)
{
	t_vec3d	up;
	t_vec3d	right;
	t_vec3d	new_direction;
	t_vec3d	new_up;

	up = app->scene.camera.up;
	right = vec_cross(app->scene.camera.direction, up);
	right = vec_normalize(right);
	new_direction.x = app->scene.camera.direction.x * cos(angle)
		+ up.x * sin(angle);
	new_direction.y = app->scene.camera.direction.y * cos(angle)
		+ up.y * sin(angle);
	new_direction.z = app->scene.camera.direction.z * cos(angle)
		+ up.z * sin(angle);
	app->scene.camera.direction = vec_normalize(new_direction);
	new_up = vec_cross(right, app->scene.camera.direction);
	app->scene.camera.up = vec_normalize(new_up);
	app->needs_rerender = true;
}

/* Rotates camera around its forward axis (roll) */
void	rotate_camera_roll(t_app *app, double angle)
{
	t_vec3d	forward;
	t_vec3d	up;
	t_vec3d	right;
	t_vec3d	new_up;

	forward = app->scene.camera.direction;
	forward = vec_normalize(forward);
	up = app->scene.camera.up;
	right = vec_cross(forward, up);
	right = vec_normalize(right);
	new_up.x = up.x * cos(angle) + right.x * sin(angle);
	new_up.y = up.y * cos(angle) + right.y * sin(angle);
	new_up.z = up.z * cos(angle) + right.z * sin(angle);
	app->scene.camera.up = vec_normalize(new_up);
	app->needs_rerender = true;
}
