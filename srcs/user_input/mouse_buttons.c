/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_buttons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 09:46:29 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Handles left mouse button press */
void	handle_left_mouse_press(t_app *app)
{
	app->mouse.left_dragging = true;
	if (!app->input.interaction_mode)
	{
		app->input.interaction_mode = true;
		app->render.needs_rerender = true;
	}
	mlx_get_mouse_pos(app->window.mlx, &app->mouse.last_x, &app->mouse.last_y);
}

/* Handles left mouse button release */
void	handle_left_mouse_release(t_app *app)
{
	app->mouse.left_dragging = false;
	if (!app->mouse.right_dragging && app->input.interaction_mode)
	{
		app->input.interaction_mode = false;
		app->render.needs_rerender = true;
	}
}

/* Handles right mouse button press */
void	handle_right_mouse_press(t_app *app)
{
	app->mouse.right_dragging = true;
	if (!app->input.interaction_mode)
	{
		app->input.interaction_mode = true;
		app->render.needs_rerender = true;
	}
	mlx_get_mouse_pos(app->window.mlx, &app->mouse.last_x, &app->mouse.last_y);
}

/* Handles right mouse button release */
void	handle_right_mouse_release(t_app *app)
{
	app->mouse.right_dragging = false;
	if (!app->mouse.left_dragging && app->input.interaction_mode)
	{
		app->input.interaction_mode = false;
		app->render.needs_rerender = true;
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
