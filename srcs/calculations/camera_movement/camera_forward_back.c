/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_forward_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 08:59:37 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Moves camera forward in the direction it's facing */
void	move_camera_forward(t_app *app)
{
	t_vec3d	move_vec;

	move_vec = vec_mul(app->scene.camera.direction, app->move_speed);
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
	app->needs_rerender = true;
}

/* Moves camera backward from the direction it's facing */
void	move_camera_backward(t_app *app)
{
	t_vec3d	move_vec;

	move_vec = vec_mul(app->scene.camera.direction, -app->move_speed);
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
	app->needs_rerender = true;
}
