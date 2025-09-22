/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_res_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 08:45:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 08:53:00 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Fill pixel block with a single color for low-resolution rendering
** Used to fill multiple pixels with the same color for performance
** @param app: Pointer to application struct
** @param x: Base x coordinate
** @param y: Base y coordinate
** @param pixel_color: Color to fill the block with
*/
static void	fill_pixel_block(t_app *app, int x, int y, uint32_t pixel_color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < app->render_scale && y + dy < app->window_height)
	{
		dx = 0;
		while (dx < app->render_scale && x + dx < app->window_width)
		{
			mlx_put_pixel(app->img, x + dx, y + dy, pixel_color);
			dx++;
		}
		dy++;
	}
}

/*
** Fill entire window with calculated pixel colors using low-res ray tracing
** Renders at reduced resolution by sampling every Nth pixel and filling blocks
** @param app: Pointer to application struct
** @param pixel_calculator: Function pointer to calculate pixel color
*/
void	fill_window_with_raytracing_low_res(t_app *app,
		uint32_t (*pixel_calculator)(t_app*, int, int))
{
	int			x;
	int			y;
	uint32_t	pixel_color;

	y = 0;
	while (y < app->window_height)
	{
		x = 0;
		while (x < app->window_width)
		{
			pixel_color = pixel_calculator(app, x, y);
			fill_pixel_block(app, x, y, pixel_color);
			x += app->render_scale;
		}
		y += app->render_scale;
	}
}
