/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:23:20 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 09:42:51 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	init_app(t_app *app)
{
	app->window_width = WINDOW_WIDTH;
	app->window_height = WINDOW_HEIGHT;
	app->mlx = mlx_init(app->window_width, app->window_height, "miniRT", true);
	if (!app->mlx)
		return (1);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img || mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
	{
		mlx_terminate(app->mlx);
		return (1);
	}

	// Initialize camera movement variables
	app->camera_original_pos = app->scene.camera.position;
	app->camera_original_dir = app->scene.camera.direction;
	app->move_speed = 0.1; // Movement speed in world units

	// Initialize mouse movement variables
	app->mouse_dragging = false;
	app->right_mouse_dragging = false;
	app->last_mouse_x = 0;
	app->last_mouse_y = 0;
	app->mouse_sensitivity = 0.002; // Mouse sensitivity for rotation
	app->accumulated_mouse_x = 0.0;
	app->accumulated_mouse_y = 0.0;

	// Initialize zoom variables
	app->zoom_factor = 1.0; // Start with no zoom
	app->zoom_speed = 0.1; // Zoom speed multiplier
	app->min_zoom = 0.1; // Minimum zoom (very zoomed out)
	app->max_zoom = 10.0; // Maximum zoom (very zoomed in)

	// Initialize performance optimization variables
	app->scene_dirty = true; // Scene needs initial render
	app->frame_counter = 0; // Start frame counter at 0
	app->render_skip_frames = 2; // Skip every 2nd frame during interaction for performance
	app->interaction_mode = false; // Start in normal mode
	app->render_scale = 1; // Start with full resolution

	return (0);
}
