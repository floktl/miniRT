/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/21 17:56:23 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	draw_red_pixel(t_app *app, int x, int y)
{
	uint32_t	red_color;

	if (x >= 0 && x < app->window_width
		&& y >= 0 && y < app->window_height)
	{
		red_color = 0xFF0000FF;
		mlx_put_pixel(app->img, x, y, red_color);
	}
}

void	draw_thick_red_line(t_app *app, int x, int y)
{
	draw_red_pixel(app, x, y);
	draw_red_pixel(app, x + 1, y);
	draw_red_pixel(app, x - 1, y);
	draw_red_pixel(app, x, y + 1);
	draw_red_pixel(app, x, y - 1);
	draw_red_pixel(app, x + 2, y);
	draw_red_pixel(app, x - 2, y);
	draw_red_pixel(app, x, y + 2);
	draw_red_pixel(app, x, y - 2);
	draw_red_pixel(app, x + 1, y + 1);
	draw_red_pixel(app, x - 1, y - 1);
	draw_red_pixel(app, x + 1, y - 1);
	draw_red_pixel(app, x - 1, y + 1);
}

static void	draw_sphere_pixel(t_app *app, t_vec3d screen_pos, int x, int y)
{
	int	screen_x;
	int	screen_y;

	screen_x = (int)screen_pos.x + x;
	screen_y = (int)screen_pos.y + y;
	if (screen_x >= 0 && screen_x < app->window_width
		&& screen_y >= 0 && screen_y < app->window_height)
	{
		mlx_put_pixel(app->img, screen_x, screen_y, app->sphere_color);
	}
}

static void	draw_colored_sphere(t_app *app, t_vec3d world_pos, t_color color,
			int radius)
{
	t_vec3d	screen_pos;
	int		x;
	int		y;

	screen_pos = project_world_to_screen(world_pos, app);
	if (screen_pos.z <= 0)
		return ;
	app->sphere_color = (color.r << 16) | (color.g << 8) | color.b;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				draw_sphere_pixel(app, screen_pos, x, y);
			x++;
		}
		y++;
	}
}

void	render_light_spheres(t_app *app)
{
	t_light	*current_light;

	current_light = app->scene.lights;
	while (current_light)
	{
		draw_colored_sphere(app, current_light->position,
			current_light->color, 4);
		current_light = current_light->next;
	}
}
