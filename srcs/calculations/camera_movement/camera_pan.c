/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_pan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/01 11:47:26 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Moves camera in X and Y directions (panning) */
void	move_camera_pan(t_app *app, double x_offset, double y_offset)
{
	t_vec3d	right;
	t_vec3d	up;
	t_vec3d	move_vec;

	right = vec_cross(app->scene.camera.direction, app->scene.camera.up);
	right = vec_normalize(right);
	up = app->scene.camera.up;
	move_vec = vec_add(vec_mul(right, x_offset), vec_mul(up, -y_offset));
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
	app->render.needs_rerender = true;
}
