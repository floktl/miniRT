/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_camera_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 09:20:21 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	draw_debug_camera_sphere(t_app *app, t_vec3d world_pos)
{
	t_vec3d	screen_pos;
	int		radius;
	int		x;
	int		y;

	screen_pos = project_world_to_screen(world_pos, app);
	if (screen_pos.z <= 0)
		return ;
	radius = 6;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				draw_circle_pixel(app, screen_pos, x, y);
			x++;
		}
		y++;
	}
}

static void	draw_ray_line(t_app *app, t_ray debug_ray, double max_distance)
{
	t_vec3d	ray_point;
	t_vec3d	screen_pos;
	double	t;

	t = 0.0;
	while (t <= max_distance)
	{
		ray_point = vec_add(debug_ray.origin,
				vec_mul(debug_ray.direction, t));
		screen_pos = project_world_to_screen(ray_point, app);
		if (screen_pos.z > 0)
		{
			if ((int)screen_pos.x >= 0
				&& (int)screen_pos.x < app->window_width
				&& (int)screen_pos.y >= 0
				&& (int)screen_pos.y < app->window_height)
			{
				draw_thick_red_line(app, (int)screen_pos.x,
					(int)screen_pos.y);
			}
		}
		t += 0.1;
	}
}

static t_ray	get_debug_camera_ray(t_app *app)
{
	t_ray	ray;
	t_vec3d	right;
	t_vec3d	up;
	t_vec3d	forward;

	right = vec_cross(app->scene.debug_camera.direction,
			app->scene.debug_camera.up);
	right = vec_normalize(right);
	up = app->scene.debug_camera.up;
	up = vec_normalize(up);
	forward = app->scene.debug_camera.direction;
	ray.origin = app->scene.debug_camera.position;
	ray.direction = forward;
	ray.direction = vec_normalize(ray.direction);
	return (ray);
}

void	render_debug_camera_ray(t_app *app)
{
	t_ray		debug_ray;
	t_object	*hit_obj;
	double		intersection_dist;

	if (!app->scene.has_debug_camera)
		return ;
	draw_debug_camera_sphere(app, app->scene.debug_camera.position);
	debug_ray = get_debug_camera_ray(app);
	intersection_dist = find_closest_intersection(debug_ray, &app->scene,
			&hit_obj);
	if (intersection_dist > 0.0 && hit_obj)
		draw_ray_line(app, debug_ray, intersection_dist);
	else
	{
		render_debug_text(app, (t_vec3d){0, 0, 0});
		draw_ray_line(app, debug_ray, 10.0);
	}
}
