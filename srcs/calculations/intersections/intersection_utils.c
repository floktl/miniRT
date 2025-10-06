/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/06 11:10:56 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Ray-Object Intersection System:
**
** This system determines which objects a ray intersects and finds closest one.
**
** Key concepts:
** - Ray: A line starting from a point (origin) extending in a direction
** - Intersection: The point where a ray hits an object's surface
** - Distance: How far along the ray the intersection occurs
**
	- Closest intersection: The nearest object hit by ray (used for rendering)
**
** Process:
** 1. For each object, calculate if the ray intersects it
** 2. If intersection exists, record the distance
** 3. Keep track of the closest valid intersection
** 4. Return the closest object and its distance
*/

static double	calculate_object_intersection_debug(t_ray ray, t_object *obj)
{
	if (obj->type == SPHERE || obj->type == LIGHT)
		return (intersect_sphere_debug(ray, obj));
	else if (obj->type == PLANE)
		return (intersect_plane(ray, obj));
	else if (obj->type == CYLINDER)
		return (intersect_cylinder(ray, obj));
	else if (obj->type == CONE)
		return (intersect_cone(ray, obj));
	return (-1.0);
}

double	find_closest_intersection(t_ray ray, t_scene *scene, t_object **hit_obj)
{
	t_object	*current;
	double		closest_dist;
	double		current_dist;

	*hit_obj = NULL;
	closest_dist = -1.0;
	current = scene->objects;
	while (current)
	{
		current_dist = calculate_object_intersection(ray, current);
		if (current_dist > 0.0 && (closest_dist < 0.0
				|| current_dist < closest_dist))
		{
			closest_dist = current_dist;
			*hit_obj = current;
		}
		current = current->next;
	}
	return (closest_dist);
}

double	find_closest_intersection_debug(t_ray ray, t_scene *scene,
		t_object **hit_obj)
{
	t_object	*current;
	double		closest_dist;
	double		current_dist;

	*hit_obj = NULL;
	closest_dist = -1.0;
	current = scene->objects;
	while (current)
	{
		current_dist = calculate_object_intersection_debug(ray, current);
		if (current_dist > 0.0 && (closest_dist < 0.0
				|| current_dist < closest_dist))
		{
			closest_dist = current_dist;
			*hit_obj = current;
		}
		current = current->next;
	}
	return (closest_dist);
}

double	calculate_object_intersection(t_ray ray, t_object *obj)
{
	if (obj->type == SPHERE || obj->type == LIGHT)
		return (intersect_sphere(ray, obj));
	else if (obj->type == PLANE)
		return (intersect_plane(ray, obj));
	else if (obj->type == CYLINDER)
		return (intersect_cylinder(ray, obj));
	else if (obj->type == CONE)
		return (intersect_cone(ray, obj));
	return (-1.0);
}
