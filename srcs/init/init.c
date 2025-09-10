/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:23:20 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/10 14:57:32 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	init_app(t_app *app)
{
	app->window_width = WINDOW_WIDTH;
	app->window_height = WINDOW_HEIGHT;
	app->mlx = mlx_init(app->window_width, app->window_height, "miniRT", false);
	if (!app->mlx)
		return (1);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img || mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
	{
		mlx_terminate(app->mlx);
		return (1);
	}
	return (0);
}
