/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:23:20 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/03 20:35:24 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Initializes all application variables for miniRT ray tracer
**
** Camera Variables:
** - camera_original_pos: Stores initial camera position for reset functionality
** - camera_original_dir: Stores initial camera direction for res. functionality
** - move_speed: Speed multiplier for camera movement (world units per input)
**
** Mouse Control Variables:
** - left_mouse_dragging: Flag indicating left mouse button is being dragged
** - right_mouse_dragging: Flag indicating right mouse button is being dragged
** - last_mouse_x/y: Previous mouse position for calculating movement delta
** - left_mouse_sensitivity: Multi. for left mouse movement to camera panning
** - right_mouse_sensitivity: Multi. for right mouse move. to camera rotation
** - accumulated_mouse_x/y: Accumulated mouse movement for smooth rotation
**
** Zoom Variables:
** - zoom_factor: Current zoom level (1.0 = normal, >1.0 = zoomed in)
** - zoom_speed: Speed multiplier for zoom operations
** - min_zoom: Minimum allowed zoom level (prevents over-zooming out)
** - max_zoom: Maximum allowed zoom level (prevents over-zooming in)
**
** Performance Optimization Variables:
** - needs_rerender: Flag indicating scene needs re-rendering
** - frame_counter: Counter for frame-based performance optimization
** - render_skip_frames: Number of frames to skip during interaction
** - interaction_mode: Flag indicating user is actively interacting
** - render_scale: Resolution scale (1 = full, 2 = half resolution)
*/

int	init_app(t_app *app)
{
	app->window.width = WINDOW_WIDTH;
	app->window.height = WINDOW_HEIGHT;
	app->window.mlx = mlx_init(app->window.width, app->window.height, "miniRT",
			false);
	if (!app->window.mlx)
		return (1);
	app->window.img = mlx_new_image(app->window.mlx, app->window.width,
			app->window. height);
	if (!app->window.img
		|| mlx_image_to_window(app->window.mlx, app->window.img, 0, 0) < 0)
	{
		mlx_terminate(app->window.mlx);
		return (1);
	}
	init_camera_variables(app);
	init_mouse_variables(app);
	init_zoom_variables(app);
	init_performance_variables(app);
	return (0);
}

void	init_camera_variables(t_app *app)
{
	app->camera.original_pos = app->scene.camera.position;
	app->camera.original_dir = app->scene.camera.direction;
	app->camera.move_speed = 0.1;
}

void	init_mouse_variables(t_app *app)
{
	app->mouse.left_dragging = false;
	app->mouse.right_dragging = false;
	app->mouse.last_x = 0;
	app->mouse.last_y = 0;
	app->mouse.left_sensitivity = 0.01;
	app->mouse.right_sensitivity = 0.002;
	app->mouse.accumulated_x = 0.0;
	app->mouse.accumulated_y = 0.0;
}

void	init_zoom_variables(t_app *app)
{
	app->zoom.factor = 1.0;
	app->zoom.speed = 0.1;
	app->zoom.min_zoom = 0.1;
	app->zoom.max_zoom = 10.0;
}

void	init_performance_variables(t_app *app)
{
	app->render.needs_rerender = true;
	app->render.frame_counter = 0;
	app->render.render_skip_frames = 2;
	app->input.interaction_mode = false;
	app->render.render_scale = 1;
	app->input.scroll_activity = false;
	app->input.ctrl_pressed = false;
}
