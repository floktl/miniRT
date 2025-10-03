/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/03 12:52:09 by mezhang          ###   ########.fr       */
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

t_vec3d	get_normal(t_vec3d point, t_object *obj)
{
	t_vec3d	normal;

	if (obj->type == SPHERE)
		normal = vec_normalize(vec_sub(point, obj->data.s_sphere.center));
	else if (obj->type == PLANE)
		normal = obj->data.s_plane.normal;
	else if (obj->type == CYLINDER)
		normal = vec_normalize(vec_sub(point, obj->data.s_cylinder.base));
	else if (obj->type == CONE)
		normal = vec_normalize(vec_sub(point, obj->data.s_cone.vertex));
	else
		normal = (t_vec3d){0, 0, 1};
	return (normal);
}
