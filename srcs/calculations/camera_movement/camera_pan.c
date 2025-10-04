/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_pan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/04 12:00:05 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	handle_x_rotation(t_app *app, double x_offset, t_vec3d origin,
		t_vec3d relative_pos)
{
	t_vec3d	right;
	t_vec3d	new_position;
	double	angle;

	angle = x_offset * 0.1;
	new_position.x = relative_pos.x * cos(angle) - relative_pos.z * sin(angle);
	new_position.y = relative_pos.y;
	new_position.z = relative_pos.x * sin(angle) + relative_pos.z * cos(angle);
	app->scene.camera.position = vec_add(origin, new_position);
	app->scene.camera.direction = vec_normalize(vec_sub(origin,
				app->scene.camera.position));
	right = vec_cross(app->scene.camera.direction, (t_vec3d){0, 1, 0});
	right = vec_normalize(right);
	app->scene.camera.up = vec_cross(right, app->scene.camera.direction);
	app->scene.camera.up = vec_normalize(app->scene.camera.up);
}

static void	handle_y_rotation(t_app *app, double y_offset, t_vec3d origin,
		t_vec3d relative_pos)
{
	t_vec3d	right;
	t_vec3d	rotated_dir;
	double	angle;
	double	distance;

	angle = -y_offset * 0.1;
	distance = sqrt(vec_dot(relative_pos, relative_pos));
	right = vec_cross(app->scene.camera.direction, app->scene.camera.up);
	right = vec_normalize(right);
	rotated_dir.x = app->scene.camera.direction.x * cos(angle)
		+ app->scene.camera.up.x * sin(angle);
	rotated_dir.y = app->scene.camera.direction.y * cos(angle)
		+ app->scene.camera.up.y * sin(angle);
	rotated_dir.z = app->scene.camera.direction.z * cos(angle)
		+ app->scene.camera.up.z * sin(angle);
	app->scene.camera.direction = vec_normalize(rotated_dir);
	app->scene.camera.position = vec_add(origin, vec_mul(
				app->scene.camera.direction, -distance));
	right = vec_cross(app->scene.camera.direction, (t_vec3d){0, 1, 0});
	right = vec_normalize(right);
	app->scene.camera.up = vec_cross(right, app->scene.camera.direction);
	app->scene.camera.up = vec_normalize(app->scene.camera.up);
}

/* Rotates main camera around the origin (0,0,0) using mouse movement */
void	move_camera_pan(t_app *app, double x_offset, double y_offset)
{
	t_vec3d	origin;
	t_vec3d	relative_pos;

	origin = (t_vec3d){0, 0, 0};
	relative_pos = vec_sub(app->scene.camera.position, origin);
	if (fabs(x_offset) > 0.001)
		handle_x_rotation(app, x_offset, origin, relative_pos);
	if (fabs(y_offset) > 0.001)
		handle_y_rotation(app, y_offset, origin, relative_pos);
	app->render.needs_rerender = true;
}
