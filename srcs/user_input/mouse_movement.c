/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/21 14:13:53 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Processes mouse movement for camera control */
void	process_mouse_movement(t_app *app, double yaw_angle, double pitch_angle)
{
	if (app->left_mouse_dragging)
	{
		move_camera_pan(app, -yaw_angle, -pitch_angle);
	}
	else if (app->right_mouse_dragging)
	{
		rotate_camera_horizontal(app, -yaw_angle);
		rotate_camera_vertical(app, pitch_angle);
	}
	app->accumulated_mouse_x = 0.0;
	app->accumulated_mouse_y = 0.0;
	app->needs_rerender = true;
}

/* Updates accumulated mouse movement based on sensitivity */
static void	update_accumulated_movement(t_app *app, double delta_x,
			double delta_y)
{
	if (app->left_mouse_dragging)
	{
		app->accumulated_mouse_x += delta_x * app->left_mouse_sensitivity;
		app->accumulated_mouse_y += delta_y * app->left_mouse_sensitivity;
	}
	else if (app->right_mouse_dragging)
	{
		app->accumulated_mouse_x += delta_x * app->right_mouse_sensitivity;
		app->accumulated_mouse_y += delta_y * app->right_mouse_sensitivity;
	}
}

/* Processes mouse movement if threshold is exceeded */
static void	process_movement_if_needed(t_app *app)
{
	double	yaw_angle;
	double	pitch_angle;

	yaw_angle = app->accumulated_mouse_x;
	pitch_angle = app->accumulated_mouse_y;
	if (fabs(app->accumulated_mouse_x) > 0.001
		|| fabs(app->accumulated_mouse_y) > 0.001)
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
	if (!app->left_mouse_dragging && !app->right_mouse_dragging)
		return ;
	delta_x = xpos - app->last_mouse_x;
	delta_y = ypos - app->last_mouse_y;
	update_accumulated_movement(app, delta_x, delta_y);
	process_movement_if_needed(app);
	app->last_mouse_x = (int)xpos;
	app->last_mouse_y = (int)ypos;
}

/* Handles mouse wheel scrolling for zooming or camera roll */
void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_app	*app;
	double	amount;

	app = (t_app *)param;
	(void)xdelta;
	if (!app->interaction_mode)
	{
		app->interaction_mode = true;
		app->needs_rerender = true;
	}
	app->scroll_activity = true;
	if (app->shift_pressed)
	{
		amount = ydelta * 0.01; /* Different sensitivity for roll */
		rotate_camera_roll(app, amount);
	}
	else
	{
		amount = ydelta * app->zoom_speed * 0.5;
		zoom_camera_towards_mouse(app, amount);
	}
	app->needs_rerender = true;
}
