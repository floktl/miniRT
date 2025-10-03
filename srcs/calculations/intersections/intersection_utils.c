/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/03 17:49:24 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	calculate_object_intersection(t_ray ray, t_object *obj)
{
	if (obj->type == SPHERE)
		return (intersect_sphere(ray, obj));
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

t_vec3d	get_normal(t_vec3d point, t_object *obj)
{
	t_vec3d	normal;

	if (obj->type == SPHERE)
		normal = vec_normalize(vec_sub(point, obj->data.s_sphere.center));
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
