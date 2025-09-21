/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/21 11:42:44 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Handles forward/backward movement keys */
void	handle_forward_back_keys(t_app *app, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W)
	{
		move_camera_forward(app);
		app->needs_rerender = true;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		move_camera_backward(app);
		app->needs_rerender = true;
	}
}

/* Handles left/right movement keys */
void	handle_left_right_keys(t_app *app, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_A)
	{
		move_camera_left(app);
		app->needs_rerender = true;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		move_camera_right(app);
		app->needs_rerender = true;
	}
}

/* Handles up/down movement keys */
void	handle_up_down_keys(t_app *app, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_Q)
	{
		move_camera_up(app);
		app->needs_rerender = true;
	}
	else if (keydata.key == MLX_KEY_E)
	{
		move_camera_down(app);
		app->needs_rerender = true;
	}
}

/* Handles WASD movement keys */
void	handle_movement_keys(t_app *app, mlx_key_data_t keydata)
{
	handle_forward_back_keys(app, keydata);
	handle_left_right_keys(app, keydata);
	handle_up_down_keys(app, keydata);
}
