/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_buttons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:13:13 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Handles left mouse button press */
void	handle_left_mouse_press(t_app *app)
{
	app->left_mouse_dragging = true;
	if (!app->interaction_mode)
	{
		app->interaction_mode = true;
		mark_scene_dirty(app);
	}
	mlx_get_mouse_pos(app->mlx, &app->last_mouse_x, &app->last_mouse_y);
}

/* Handles left mouse button release */
void	handle_left_mouse_release(t_app *app)
{
	app->left_mouse_dragging = false;
	if (!app->right_mouse_dragging && app->interaction_mode)
	{
		app->interaction_mode = false;
		mark_scene_dirty(app);
	}
}

/* Handles right mouse button press */
void	handle_right_mouse_press(t_app *app)
{
	app->right_mouse_dragging = true;
	if (!app->interaction_mode)
	{
		app->interaction_mode = true;
		mark_scene_dirty(app);
	}
	mlx_get_mouse_pos(app->mlx, &app->last_mouse_x, &app->last_mouse_y);
}

/* Handles right mouse button release */
void	handle_right_mouse_release(t_app *app)
{
	app->right_mouse_dragging = false;
	if (!app->left_mouse_dragging && app->interaction_mode)
	{
		app->interaction_mode = false;
		mark_scene_dirty(app);
	}
}

/* Handles mouse button events */
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_app	*app;

	app = (t_app *)param;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (action == MLX_PRESS)
			handle_left_mouse_press(app);
		else if (action == MLX_RELEASE)
			handle_left_mouse_release(app);
	}
	else if (button == MLX_MOUSE_BUTTON_RIGHT)
	{
		if (action == MLX_PRESS)
			handle_right_mouse_press(app);
		else if (action == MLX_RELEASE)
			handle_right_mouse_release(app);
	}
}
