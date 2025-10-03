/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/03 20:42:37 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
intersection formula:
((OC + t*D) . A)^2 = |OC + t*D|^2 * cos^2(theta)
cos^2(theta) = h^2 / (r^2 + h^2) = 1 / (1 + (r/h)^2)
*/

#include "miniRT.h"


static double	calculate_quadratic_terms(t_vec3d ray_dir, t_vec3d ov,
		t_object *obj, double cos2_theta)
{
	double	dot_dir_axis;
	double	dot_ov_axis;
	double	dot_ov_dir;

	double params[3]; // a, b, c
	dot_dir_axis = vec_dot(ray_dir, obj->data.s_cone.axis);
	dot_ov_axis = vec_dot(ov, obj->data.s_cone.axis);
	dot_ov_dir = vec_dot(ov, ray_dir);
	params[0] = dot_dir_axis * dot_dir_axis - cos2_theta;
	params[1] = 2 * (dot_dir_axis * dot_ov_axis - dot_ov_dir * cos2_theta);
	params[2] = dot_ov_axis * dot_ov_axis - vec_dot(ov, ov) * cos2_theta;
	return (params[1] * params[1] - 4 * params[0] * params[2]); // b^2 - 4ac
}

static bool	is_intersection_within_cone(t_ray ray, t_object *obj, double t)
{
	t_vec3d	p;
	double	m;

	p = vec_add(ray.origin, vec_mul(ray.direction, t));
	m = vec_dot(vec_sub(p, obj->data.s_cone.vertex), obj->data.s_cone.axis);
	if (m < 0 || m > obj->data.s_cone.height)
		return (false);
	return (true);
}

static bool	is_point_on_cone_cap(t_vec3d p, t_object *obj)
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

static double	find_cone_side_intersection(t_ray ray, t_object *obj,
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
	if (t[1] > 0.0 && is_intersection_within_cone(ray, obj, t[1]))
		return (t[1]);
	if (t[0] > 0.0 && is_intersection_within_cone(ray, obj, t[0]))
		return (t[0]);
	return (-1.0);
}

static double	find_cone_cap_intersection(t_ray ray, t_object *obj)
{
	t_vec3d	cap_center;
	double	denom;
	double	t_cap;
	t_vec3d	p;

	cap_center = vec_add(obj->data.s_cone.vertex, vec_mul(obj->data.s_cone.axis,
				obj->data.s_cone.height));
	denom = vec_dot(ray.direction, obj->data.s_cone.axis);
	if (fabs(denom) < 1e-6)
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

double	intersect_cone(t_ray ray, t_object *obj)
{
	t_vec3d	ov;
	double	cos2_theta;
	double	disc;
	double	t_side;
	double	t_cap;

	ov = vec_sub(ray.origin, obj->data.s_cone.vertex);
	cos2_theta = (obj->data.s_cone.height * obj->data.s_cone.height)
		/ (obj->data.s_cone.radius * obj->data.s_cone.radius
			+ obj->data.s_cone.height * obj->data.s_cone.height);
	disc = calculate_quadratic_terms(ray.direction, ov, obj, cos2_theta);
	if (disc < 0.0)
		t_side = -1.0;
	else
		t_side = find_cone_side_intersection(ray, obj, disc, cos2_theta);
	t_cap = find_cone_cap_intersection(ray, obj);
	if (t_side > 0.0 && (t_cap < 0.0 || t_side < t_cap))
		return (t_side);
	if (t_cap > 0.0)
		return (t_cap);
	return (-1.0);
}
