/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/03 20:36:42 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Ray-Object Intersection System:
**
** This system determines which objects a ray intersects and finds the closest one.
**
** Key concepts:
** - Ray: A line starting from a point (origin) extending in a direction
** - Intersection: The point where a ray hits an object's surface
** - Distance: How far along the ray the intersection occurs
** - Closest intersection: The nearest object hit by the ray (used for rendering)
**
** Process:
** 1. For each object, calculate if the ray intersects it
** 2. If intersection exists, record the distance
** 3. Keep track of the closest valid intersection
** 4. Return the closest object and its distance
*/

static double	calculate_object_intersection(t_ray ray, t_object *obj)
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

static t_vec3d	get_cylinder_normal(t_object *obj, t_vec3d point)
{
	t_vec3d	v;
	t_vec3d	perp;
	double	m;

	v = vec_sub(point, obj->data.s_cylinder.base);
	m = vec_dot(v, obj->data.s_cylinder.axis);
	perp = vec_sub(v, vec_mul(obj->data.s_cylinder.axis, m));
	return (vec_normalize(perp));
}

static t_vec3d	get_cone_normal(t_object *obj, t_vec3d point)
{
	t_vec3d	v;
	t_vec3d	scaled_axis;
	double	m;
	double	k;

	v = vec_sub(point, obj->data.s_cone.vertex);
	m = vec_dot(v, obj->data.s_cone.axis);
	k = obj->data.s_cone.radius / obj->data.s_cone.height;
	scaled_axis = vec_mul(obj->data.s_cone.axis, m * (1 + k * k));
	return (vec_normalize(vec_sub(v, scaled_axis)));
}

double	find_closest_intersection_debug(t_ray ray, t_scene *scene, t_object **hit_obj)
{
	t_object	*current;
	double		closest_dist;
	double		current_dist;

	printf("[DEBUG INTERSECTION] find_closest_intersection: ray origin=(%.3f,%.3f,%.3f) dir=(%.3f,%.3f,%.3f)\n",
		ray.origin.x, ray.origin.y, ray.origin.z,
		ray.direction.x, ray.direction.y, ray.direction.z);
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
	printf("[DEBUG INTERSECTION] Final result: distance=%.3f, hit_obj=%p\n", closest_dist, *hit_obj);
	return (closest_dist);
}

t_vec3d	get_normal(t_vec3d point, t_object *obj)
{
	t_vec3d	normal;

	if (obj->type == SPHERE || obj->type == LIGHT)
	{
		normal = vec_sub(point, obj->data.s_sphere.center);
		normal = vec_normalize(normal);
	}
	else if (obj->type == PLANE)
		normal = obj->data.s_plane.normal;
	else if (obj->type == CYLINDER)
		normal = get_cylinder_normal(obj, point);
	else if (obj->type == CONE)
		normal = get_cone_normal(obj, point);
	else
		normal = (t_vec3d){0, 0, 1};
	return (normal);
}
