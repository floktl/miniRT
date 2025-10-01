/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:14:48 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/01 10:58:02 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Handles keyboard input for camera movement and application control */
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(app->window.mlx);
	if (keydata.key == MLX_KEY_LEFT_CONTROL
		|| keydata.key == MLX_KEY_RIGHT_CONTROL)
	{
		if (keydata.action == MLX_PRESS)
			app->input.shift_pressed = true;
		else if (keydata.action == MLX_RELEASE)
			app->input.shift_pressed = false;
	}
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		handle_movement_keys(app, keydata);
}
