/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:28:46 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint32_t	calculate_intersection_color(t_ray ray,
		double intersection_dist, t_object *hit_obj, t_scene *scene)
{
	t_vec3d		intersection_point;
	t_vec3d		normal;
	t_color		final_color;
	uint32_t	pixel_color;

	intersection_point = vec_add(ray.origin,
			vec_mul(ray.direction, intersection_dist));
	normal = get_normal(intersection_point, hit_obj);
	final_color = compute_lighting(intersection_point, normal, scene, hit_obj);
	pixel_color = (final_color.r << 16) | (final_color.g << 8) | final_color.b;
	return (pixel_color);
}

static uint32_t	calculate_background_color(t_scene *scene)
{
	uint32_t	pixel_color;

	pixel_color = (scene->ambient.color.r << 16)
		| (scene->ambient.color.g << 8) | scene->ambient.color.b;
	return (pixel_color);
}

uint32_t	render_pixel(t_app *app, int x, int y)
{
	t_ray		ray;
	t_object	*hit_obj;
	double		intersection_dist;

	ray = get_ray(app, x, y);
	intersection_dist = find_closest_intersection(ray, &app->scene, &hit_obj);
	if (intersection_dist > 0.0 && hit_obj)
		return (calculate_intersection_color(ray, intersection_dist,
				hit_obj, &app->scene));
	else
		return (calculate_background_color(&app->scene));
}
