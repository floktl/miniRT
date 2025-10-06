/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/06 20:43:26 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Cone Intersection Helper Functions:
**
** These functions handle the mathematical calculations for cone-ray
** intersections, including side intersections, cap intersections, and
** boundary checking.
**
** Key concepts:
** - Quadratic equation: Used to find intersection points with cone sides
** - Cap intersection: Checking if ray hits the circular top face
** - Boundary checking: Ensuring intersections are within cone height
*/

double	calculate_cone_quadratic_terms(t_vec3d ray_dir, t_vec3d ov,
		t_object *obj, double cos2_theta)
{
	double	dot_dir_axis;
	double	dot_ov_axis;
	double	dot_ov_dir;
	double	params[3];

	dot_dir_axis = vec_dot(ray_dir, obj->data.s_cone.axis);
	dot_ov_axis = vec_dot(ov, obj->data.s_cone.axis);
	dot_ov_dir = vec_dot(ov, ray_dir);
	params[0] = dot_dir_axis * dot_dir_axis - cos2_theta;
	params[1] = 2 * (dot_dir_axis * dot_ov_axis - dot_ov_dir * cos2_theta);
	params[2] = dot_ov_axis * dot_ov_axis - vec_dot(ov, ov) * cos2_theta;
	return (params[1] * params[1] - 4 * params[0] * params[2]);
}

bool	is_cone_intersection_within_cone(t_ray ray, t_object *obj, double t)
{
	t_vec3d	p;
	double	m;

	p = vec_add(ray.origin, vec_mul(ray.direction, t));
	m = vec_dot(vec_sub(p, obj->data.s_cone.vertex), obj->data.s_cone.axis);
	if (m < 0 || m > obj->data.s_cone.height)
		return (false);
	return (true);
}

bool	is_point_on_cone_cap(t_vec3d p, t_object *obj)
{
	t_vec3d	cap_center;
	t_vec3d	v;
	double	dist;

	cap_center = vec_add(obj->data.s_cone.vertex, vec_mul(obj->data.s_cone.axis,
				obj->data.s_cone.height));
	v = vec_sub(p, cap_center);
	dist = vec_length(vec_sub(v, vec_mul(obj->data.s_cone.axis, vec_dot(v,
						obj->data.s_cone.axis))));
	if (dist <= obj->data.s_cone.radius)
		return (true);
	return (false);
}

double	find_cone_side_intersection(t_ray ray, t_object *obj,
		double disc, double cos2_theta)
{
	double	t[2];
	double	dot_dir_axis;
	double	dot_ov_dir;
	double	dot_ov_axis;
	double	params[2];

	dot_dir_axis = vec_dot(ray.direction, obj->data.s_cone.axis);
	dot_ov_dir = vec_dot(vec_sub(ray.origin, obj->data.s_cone.vertex),
			ray.direction);
	dot_ov_axis = vec_dot(vec_sub(ray.origin, obj->data.s_cone.vertex),
			obj->data.s_cone.axis);
	params[0] = dot_dir_axis * dot_dir_axis - cos2_theta;
	params[1] = 2 * (dot_dir_axis * dot_ov_axis - dot_ov_dir * cos2_theta);
	t[0] = (-params[1] - sqrt(disc)) / (2 * params[0]);
	t[1] = (-params[1] + sqrt(disc)) / (2 * params[0]);
	if (t[1] > 0.0 && is_cone_intersection_within_cone(ray, obj, t[1]))
		return (t[1]);
	if (t[0] > 0.0 && is_cone_intersection_within_cone(ray, obj, t[0]))
		return (t[0]);
	return (-1.0);
}

double	find_cone_cap_intersection(t_ray ray, t_object *obj)
{
	t_vec3d	cap_center;
	double	denom;
	double	t_cap;
	t_vec3d	p;

	cap_center = vec_add(obj->data.s_cone.vertex, vec_mul(obj->data.s_cone.axis,
				obj->data.s_cone.height));
	denom = vec_dot(ray.direction, obj->data.s_cone.axis);
	if (fabs(denom) < 1e-4)
		return (-1.0);
	t_cap = vec_dot(vec_sub(cap_center, ray.origin), obj->data.s_cone.axis)
		/ denom;
	if (t_cap < 0.0)
		return (-1.0);
	p = vec_add(ray.origin, vec_mul(ray.direction, t_cap));
	if (is_point_on_cone_cap(p, obj))
		return (t_cap);
	return (-1.0);
}
