/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_left_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:06:38 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Moves camera left (perpendicular to camera direction) */
void	move_camera_left(t_app *app)
{
	t_vec3d	right_vector;
	t_vec3d	move_vec;

	right_vector = vec_cross(app->scene.camera.direction, (t_vec3d){0, 1, 0});
	right_vector = vec_normalize(right_vector);
	move_vec = vec_mul(right_vector, -app->move_speed);
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
}

/* Moves camera right (perpendicular to camera direction) */
void	move_camera_right(t_app *app)
{
	t_vec3d	right_vector;
	t_vec3d	move_vec;

	right_vector = vec_cross(app->scene.camera.direction, (t_vec3d){0, 1, 0});
	right_vector = vec_normalize(right_vector);
	move_vec = vec_mul(right_vector, app->move_speed);
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
}
