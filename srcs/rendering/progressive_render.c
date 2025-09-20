/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progressive_render.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 10:16:45 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Fills pixel block with color during low resolution rendering */
static void	fill_pixel_block(t_app *app, int x, int y, uint32_t color)
{
	int	dx;
	int	dy;
	int	step;

	step = app->render_scale;
	dy = 0;
	while (dy < step && y + dy < app->window_height)
	{
		dx = 0;
		while (dx < step && x + dx < app->window_width)
		{
			mlx_put_pixel(app->img, x + dx, y + dy, color);
			dx++;
		}
		dy++;
	}
}

/* Calculates pixel color for low resolution rendering */
static uint32_t	calculate_pixel_color(t_app *app, t_ray ray)
{
	t_object	*hit_obj;
	double		intersection_dist;
	t_vec3d		intersection_point;
	t_vec3d		normal;
	t_color		final_color;

	intersection_dist = find_closest_intersection(ray, &app->scene, &hit_obj);
	if (intersection_dist > 0.0 && hit_obj)
	{
		intersection_point = vec_add(ray.origin,
				vec_mul(ray.direction, intersection_dist));
		normal = get_normal(intersection_point, hit_obj);
		final_color = compute_lighting(intersection_point, normal,
				&app->scene, hit_obj);
		return ((final_color.r << 16) | (final_color.g << 8) | final_color.b);
	}
	return ((app->scene.ambient.color.r << 16)
		| (app->scene.ambient.color.g << 8)
		| app->scene.ambient.color.b);
}

/* Renders scene at reduced resolution for better performance */
static void	render_scene_low_res(t_app *app)
{
	int			x;
	int			y;
	t_ray		ray;
	uint32_t	pixel_color;

	y = 0;
	while (y < app->window_height)
	{
		x = 0;
		while (x < app->window_width)
		{
			ray = get_ray(app, x, y);
			pixel_color = calculate_pixel_color(app, ray);
			fill_pixel_block(app, x, y, pixel_color);
			x += app->render_scale;
		}
		y += app->render_scale;
	}
}

/* Clears image buffer for progressive rendering */
static void	clear_buffer(t_app *app)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->window_height)
	{
		x = 0;
		while (x < app->window_width)
		{
			mlx_put_pixel(app->img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

/* Progressive render that switches between full & low resolution */
void	progressive_re_render_scene(t_app *app)
{
	if (!app->scene_dirty)
		return ;
	if (app->interaction_mode
		&& (app->frame_counter % app->render_skip_frames != 0))
	{
		app->frame_counter++;
		return ;
	}
	clear_buffer(app);
	if (app->interaction_mode)
	{
		app->render_scale = 2;
		render_scene_low_res(app);
	}
	else
	{
		app->render_scale = 1;
		render_scene(app);
	}
	app->scene_dirty = false;
	app->frame_counter++;
}
