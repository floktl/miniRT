/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_pan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/03 09:47:08 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Rotates main camera around the origin (0,0,0) using mouse movement */
void	move_camera_pan(t_app *app, double x_offset, double y_offset)
{
	t_vec3d	origin;
	t_vec3d	right;
	t_vec3d	new_position;
	t_vec3d	relative_pos;
	double	rotation_speed;

	origin = (t_vec3d){0, 0, 0};
	rotation_speed = 0.1;
	relative_pos = vec_sub(app->scene.camera.position, origin);
	if (fabs(x_offset) > 0.001)
	{
		double angle = x_offset * rotation_speed;
		double cos_a = cos(angle);
		double sin_a = sin(angle);
		new_position.x = relative_pos.x * cos_a - relative_pos.z * sin_a;
		new_position.y = relative_pos.y;
		new_position.z = relative_pos.x * sin_a + relative_pos.z * cos_a;
		app->scene.camera.position = vec_add(origin, new_position);
		app->scene.camera.direction = vec_normalize(vec_sub(origin, app->scene.camera.position));
		right = vec_cross(app->scene.camera.direction, (t_vec3d){0, 1, 0});
		right = vec_normalize(right);
		app->scene.camera.up = vec_cross(right, app->scene.camera.direction);
		app->scene.camera.up = vec_normalize(app->scene.camera.up);
	}
	if (fabs(y_offset) > 0.001)
	{
		double angle = -y_offset * rotation_speed;
		double cos_a = cos(angle);
		double sin_a = sin(angle);
		double distance = sqrt(vec_dot(relative_pos, relative_pos));
		right = vec_cross(app->scene.camera.direction, app->scene.camera.up);
		right = vec_normalize(right);
		t_vec3d rotated_dir;
		rotated_dir.x = app->scene.camera.direction.x * cos_a + app->scene.camera.up.x * sin_a;
		rotated_dir.y = app->scene.camera.direction.y * cos_a + app->scene.camera.up.y * sin_a;
		rotated_dir.z = app->scene.camera.direction.z * cos_a + app->scene.camera.up.z * sin_a;
		app->scene.camera.direction = vec_normalize(rotated_dir);
		app->scene.camera.position = vec_add(origin, vec_mul(app->scene.camera.direction, -distance));
		right = vec_cross(app->scene.camera.direction, (t_vec3d){0, 1, 0});
		right = vec_normalize(right);
		app->scene.camera.up = vec_cross(right, app->scene.camera.direction);
		app->scene.camera.up = vec_normalize(app->scene.camera.up);
	}
	app->render.needs_rerender = true;
}
