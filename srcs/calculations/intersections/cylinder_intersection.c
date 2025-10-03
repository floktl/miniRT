/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/03 14:09:08 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
|(P - C) - (P - C) . A|^2 = r ^2
|OC + t*D - (OC + t*D) . A|^2 = r ^2
P = O + tD
 */

#include "miniRT.h"

static double	calculate_quadratic_terms(t_vec3d ray_dir, t_vec3d oc,
		t_object *obj, double dot_dir_axis)
{
	t_vec3d	axis_perp;
	double	dot_oc_axis;
	double	dot_oc_dir;
	double params[3]; // a, b, c

	axis_perp = vec_sub(ray_dir, vec_mul(obj->data.s_cylinder.axis,
				dot_dir_axis));
	dot_oc_axis = vec_dot(oc, obj->data.s_cylinder.axis);
	dot_oc_dir = vec_dot(oc, ray_dir);
	params[0] = vec_dot(axis_perp, axis_perp);
	params[1] = 2 * (dot_oc_dir - dot_oc_axis * dot_dir_axis);
	params[2] = vec_dot(oc, oc) - dot_oc_axis * dot_oc_axis
		- obj->data.s_cylinder.radius * obj->data.s_cylinder.radius;
	return (params[1] * params[1] - 4 * params[0] * params[2]);
}

static bool	is_intersection_within_cylinder(t_ray ray, t_object *obj, double t,
		double dot_dir_axis)
{
	t_vec3d	p;
	double	m;

	p = vec_add(ray.origin, vec_mul(ray.direction, t));
	m = vec_dot(vec_sub(p, obj->data.s_cylinder.base),
			obj->data.s_cylinder.axis);
	if (m < 0 || m > obj->data.s_cylinder.height)
		return (false);
	return (true);
}

static double	find_cylinder_intersection(t_ray ray, t_object *obj,
		double dot_dir_axis, double disc)
{
	double	t[2];
	double	dot_oc_axis;
	double	dot_oc_dir;
	double params[2]; // a, b, c

	dot_oc_dir = vec_dot(vec_sub(ray.origin, obj->data.s_cylinder.base),
			ray.direction);
	dot_oc_axis = vec_dot(vec_sub(ray.origin, obj->data.s_cylinder.base),
			obj->data.s_cylinder.axis);
	params[0] = 1.0 - dot_dir_axis * dot_dir_axis;
	params[1] = 2 * (dot_oc_dir - dot_oc_axis * dot_dir_axis);
	t[0] = (-params[1] - sqrt(disc)) / (2 * params[0]);
	t[1] = (-params[1] + sqrt(disc)) / (2 * params[0]);
	if (t[0] > 0 && is_intersection_within_cylinder(ray, obj, t[0], dot_dir_axis))
		return (t[0]);
	if (t[1] > 0 && is_intersection_within_cylinder(ray, obj, t[1], dot_dir_axis))
		return (t[1]);
	return (-1.0);
}

static double	calculate_cap_intersection(t_ray ray, t_object *obj,
		double dot_dir_axis)
{
	double	t1;
	double	t2;
	double	denom;

	denom = dot_dir_axis;
	if (fabs(denom) > 1e-6)
	{
		t1 = (vec_dot(obj->data.s_cylinder.base, obj->data.s_cylinder.axis)
				- vec_dot(ray.origin, obj->data.s_cylinder.axis)) / denom;
		t2 = (vec_dot(vec_add(obj->data.s_cylinder.base,
						vec_mul(obj->data.s_cylinder.axis,
							obj->data.s_cylinder.height)),
					obj->data.s_cylinder.axis)
				- vec_dot(ray.origin, obj->data.s_cylinder.axis)) / denom;
		if (!is_intersection_within_cylinder(ray, obj, t1, dot_dir_axis) || 
			!is_intersection_within_cylinder(ray, obj, t2, dot_dir_axis))
			return (-1.0);
		if (t1 > 0.0 && t2 > 0.0)
			return (fmin(t1, t2));
	}
	return (-1.0);
}

double	intersect_cylinder(t_ray ray, t_object *obj)
{
	t_vec3d	oc;
	double	dot_dir_axis;
	double	disc;
	double	t;

	oc = vec_sub(ray.origin, obj->data.s_cylinder.base);
	dot_dir_axis = vec_dot(ray.direction, obj->data.s_cylinder.axis);
	t = calculate_cap_intersection(ray, obj, dot_dir_axis);
	if (t > 0.0)
		return (t);
	disc = calculate_quadratic_terms(ray.direction, oc, obj, dot_dir_axis);
	if (disc < 0)
		return (-1.0);
	return (find_cylinder_intersection(ray, obj, dot_dir_axis, disc));
}
