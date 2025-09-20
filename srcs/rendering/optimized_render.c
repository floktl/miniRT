/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:47:57 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Optimized re-render, only renders when scene dirty & frame counter allows */
void	optimized_re_render_scene(t_app *app)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	if (!app->needs_rerender)
		return ;
	if (app->interaction_mode
		&& (app->frame_counter % app->render_skip_frames != 0))
	{
		app->frame_counter++;
		return ;
	}
	while (y < app->window_height)
	{
		while (x < app->window_width)
		{
			mlx_put_pixel(app->img, x++, y, 0x00000000);
		}
		y++;
	}
	render_scene(app);
	app->needs_rerender = false;
	app->frame_counter++;
}

/* Marks the scene as needing a re-render */
void	mark_needs_rerender(t_app *app)
{
	app->needs_rerender = true;
}

/* Forces an immediate re-render regardless of frame rate */
void	force_re_render_scene(t_app *app)
{
	int			y;
	int			x;

	y = 0;
	x = 0;
	while (y < app->window_height)
	{
		while (x < app->window_width)
		{
			mlx_put_pixel(app->img, x++, y, 0x00000000);
		}
		y++;
	}
	render_scene(app);
	app->needs_rerender = false;
	app->frame_counter++;
}
