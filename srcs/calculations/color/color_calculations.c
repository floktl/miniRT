/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calculations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:15:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/21 17:56:23 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Calculate color for a pixel that intersects with an object
** @param ray: Ray that hit the object
** @param intersection_dist: Distance to intersection point
** @param hit_obj: Object that was hit
** @param scene: Scene containing lighting information
** @return: 32-bit color value for the pixel
*/
uint32_t	calculate_intersection_color(t_ray ray,
		double intersec_dist, t_object *hit_obj, t_scene *scene)
{
	t_vec3d		inter_point;
	t_vec3d		normal;
	t_color		final_color;
	uint32_t	pixel_color;

	inter_point = vec_add(ray.origin, vec_mul(ray.direction, intersec_dist));
	normal = get_normal(inter_point, hit_obj);
	final_color = compute_lighting(inter_point, normal, scene, hit_obj);
	pixel_color = (final_color.r << 24)
		| (final_color.g << 16)
		| (final_color.b << 8)
		| 0xFF;
	return (pixel_color);
}

/*
** Calculate background color for a pixel that doesn't hit any object
** @param scene: Scene containing ambient lighting information
** @return: 32-bit color value for the background pixel
*/
uint32_t	calculate_background_color(t_scene *scene)
{
	uint32_t	pixel_color;

	pixel_color = (scene->ambient.color.r << 24)
		| (scene->ambient.color.g << 16)
		| (scene->ambient.color.b << 8)
		| 0xFF;
	return (pixel_color);
}
