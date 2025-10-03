/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/01 14:22:22 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Handles forward/backward movement keys */
void	handle_forward_back_keys(t_app *app, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W)
	{
		move_camera_forward(app);
	}
	else if (keydata.key == MLX_KEY_S)
	{
		move_camera_backward(app);
	}
}

/* Handles left/right movement keys */
void	handle_left_right_keys(t_app *app, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_A)
	{
		move_camera_left(app);
	}
	else if (keydata.key == MLX_KEY_D)
	{
		move_camera_right(app);
	}
}

/* Handles up/down movement keys */
void	handle_up_down_keys(t_app *app, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_Q)
	{
		move_camera_up(app);
	}
	else if (keydata.key == MLX_KEY_E)
	{
		move_camera_down(app);
	}
}

/* Handles debug camera rotation keys (I/J/K/L/N/M) */
void	handle_debug_camera_rotation_keys(t_app *app, mlx_key_data_t keydata)
{
	double	rotation_angle;

	rotation_angle = 0.05;
	if (keydata.key == MLX_KEY_I)
	{
		rotate_debug_camera_vertical(app, rotation_angle);
	}
	else if (keydata.key == MLX_KEY_J)
	{
		rotate_debug_camera_roll(app, -rotation_angle);
	}
	else if (keydata.key == MLX_KEY_K)
	{
		rotate_debug_camera_horizontal(app, rotation_angle);
	}
	else if (keydata.key == MLX_KEY_L)
	{
		rotate_debug_camera_horizontal(app, -rotation_angle);
	}
	else if (keydata.key == MLX_KEY_N)
	{
		rotate_debug_camera_vertical(app, -rotation_angle);
	}
	else if (keydata.key == MLX_KEY_M)
		rotate_debug_camera_roll(app, rotation_angle);
}

/* Handles WASD movement keys */
void	handle_movement_keys(t_app *app, mlx_key_data_t keydata)
{
	handle_forward_back_keys(app, keydata);
	handle_left_right_keys(app, keydata);
	handle_up_down_keys(app, keydata);
	handle_debug_camera_rotation_keys(app, keydata);
}
