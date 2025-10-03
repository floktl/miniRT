/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/03 20:35:24 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Processes mouse movement for camera control */
void	process_mouse_movement(t_app *app, double yaw_angle, double pitch_angle)
{
	if (app->mouse.left_dragging)
	{
		move_camera_pan(app, -yaw_angle, -pitch_angle);
	}
	else if (app->mouse.right_dragging)
	{
		rotate_camera_horizontal(app, -yaw_angle);
		rotate_camera_vertical(app, pitch_angle);
	}
	app->mouse.accumulated_x = 0.0;
	app->mouse.accumulated_y = 0.0;
}

/* Updates accumulated mouse movement based on sensitivity */
static void	update_accumulated_movement(t_app *app, double delta_x,
			double delta_y)
{
	if (app->mouse.left_dragging)
	{
		app->mouse.accumulated_x += delta_x * app->mouse.left_sensitivity;
		app->mouse.accumulated_y += delta_y * app->mouse.left_sensitivity;
	}
	else if (app->mouse.right_dragging)
	{
		app->mouse.accumulated_x += delta_x * app->mouse.right_sensitivity;
		app->mouse.accumulated_y += delta_y * app->mouse.right_sensitivity;
	}
}

/* Processes mouse movement if threshold is exceeded */
static void	process_movement_if_needed(t_app *app)
{
	double	yaw_angle;
	double	pitch_angle;

	yaw_angle = app->mouse.accumulated_x;
	pitch_angle = app->mouse.accumulated_y;
	if (fabs(app->mouse.accumulated_x) > 0.001
		|| fabs(app->mouse.accumulated_y) > 0.001)
	{
		process_mouse_movement(app, yaw_angle, pitch_angle);
	}
}

/* Handles mouse cursor movement with accumulated smoothing */
void	cursor_hook(double xpos, double ypos, void *param)
{
	t_app	*app;
	double	delta_x;
	double	delta_y;

	app = (t_app *)param;
	if (!app->mouse.left_dragging && !app->mouse.right_dragging)
		return ;
	delta_x = xpos - app->mouse.last_x;
	delta_y = ypos - app->mouse.last_y;
	update_accumulated_movement(app, delta_x, delta_y);
	process_movement_if_needed(app);
	app->mouse.last_x = (int)xpos;
	app->mouse.last_y = (int)ypos;
}

/* Handles mouse wheel scrolling for zooming or camera roll */
void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_app	*app;
	double	amount;

	app = (t_app *)param;
	(void)xdelta;
	if (!app->input.interaction_mode)
	{
		app->input.interaction_mode = true;
		app->render.needs_rerender = true;
	}
	app->input.scroll_activity = true;
	if (app->input.ctrl_pressed)
	{
		amount = ydelta * 0.01;
		rotate_camera_roll(app, amount);
	}
	else
	{
		amount = ydelta * app->zoom.speed * 0.5;
		zoom_camera_towards_mouse(app, amount);
	}
}
