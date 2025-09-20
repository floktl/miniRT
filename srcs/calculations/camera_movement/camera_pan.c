/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_pan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:06:38 by fkeitel          ###   ########.fr       */
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
	up = vec_normalize(up);
	move_vec = vec_add(vec_mul(right, x_offset), vec_mul(up, -y_offset));
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
}

/* Re-renders the scene after camera movement */
void	re_render_scene(t_app *app)
{
	mark_scene_dirty(app);
	optimized_re_render_scene(app);
}
