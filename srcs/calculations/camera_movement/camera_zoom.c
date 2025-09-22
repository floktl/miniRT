/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_zoom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 09:30:21 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Calculate zoom direction towards mouse cursor position
** Math: Gets world point under mouse cursor and calculates direction vector
** @param app: Pointer to application struct
** @param mouse_x: Mouse X coordinate in pixels
** @param mouse_y: Mouse Y coordinate in pixels
** @return: Normalized direction vector from camera to mouse world point
*/
static t_vec3d	calculate_mouse_zoom_direction(t_app *app, int mouse_x,
			int mouse_y)
{
	t_vec3d	mouse_world_point;
	t_vec3d	zoom_direction;

	mouse_world_point = screen_to_world_point(mouse_x, mouse_y, 1.0, app);
	zoom_direction = vec_normalize(vec_sub(mouse_world_point,
				app->scene.camera.position));
	app->render.needs_rerender = true;
	return (zoom_direction);
}

/*
** Zoom camera towards mouse cursor position
** Math: Moves camera along calculated direction vector
** @param app: Pointer to application struct
** @param zoom_amount: Amount to zoom (positive = zoom in, negative = zoom out)
*/
void	zoom_camera_towards_mouse(t_app *app, double zoom_amount)
{
	t_vec3d	zoom_direction;
	int		mouse_x;
	int		mouse_y;

	mlx_get_mouse_pos(app->window.mlx, &mouse_x, &mouse_y);
	zoom_direction = calculate_mouse_zoom_direction(app, mouse_x, mouse_y);
	app->scene.camera.position = vec_add(app->scene.camera.position,
			vec_mul(zoom_direction, zoom_amount));
	app->render.needs_rerender = true;
}
