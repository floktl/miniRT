/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_up_down.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:06:38 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Moves camera up (Y-axis) */
void	move_camera_up(t_app *app)
{
	t_vec3d	move_vec;

	move_vec = (t_vec3d){0, app->move_speed, 0};
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
}

/* Moves camera down (Y-axis) */
void	move_camera_down(t_app *app)
{
	t_vec3d	move_vec;

	move_vec = (t_vec3d){0, -app->move_speed, 0};
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
}
