/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/06 22:15:41 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Cylinder Intersection Helper Functions:
**
** These functions handle the mathematical calculations for cylinder-ray
** intersections, including side intersections, cap intersections, and
** boundary checking.
**
** Key concepts:
** - Quadratic equation: Used to find intersection points with cylinder sides
** - Cap intersection: Checking if ray hits the top or bottom circular faces
** - Boundary checking: Ensuring intersections are within cylinder height
*/

double	calculate_cylinder_quadratic_terms(t_vec3d ray_dir, t_vec3d oc,
		t_object *obj, double dot_dir_axis)
{
	t_vec3d	axis_perp;
	double	dot_oc_axis;
	double	dot_oc_dir;
	double	params[3];

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

bool	is_cylinder_intersection_inside(t_ray ray, t_object *obj, double t)
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

bool	is_cylinder_intersection_on_cap(t_ray ray, t_object *obj, double t,
		int cap)
{
	t_vec3d	p;
	t_vec3d	v;
	t_vec3d	cap_center;
	double	dist;

	p = vec_add(ray.origin, vec_mul(ray.direction, t));
	if (cap == 0)
		cap_center = obj->data.s_cylinder.base;
	else
		cap_center = vec_add(obj->data.s_cylinder.base,
				vec_mul(obj->data.s_cylinder.axis,
					obj->data.s_cylinder.height));
	v = vec_sub(p, cap_center);
	dist = vec_dot(v, obj->data.s_cylinder.axis);
	if (fabs(dist) > 1e-4)
		return (false);
	dist = vec_length(vec_sub(v, vec_mul(obj->data.s_cylinder.axis, dist)));
	if (dist > obj->data.s_cylinder.radius)
		return (false);
	return (true);
}

double	find_cylinder_side_intersection(t_ray ray, t_object *obj,
		double dot_dir_axis, double disc)
{
	double	t[2];
	double	dot_oc_axis;
	double	dot_oc_dir;
	double	params[2];

	dot_oc_dir = vec_dot(vec_sub(ray.origin, obj->data.s_cylinder.base),
			ray.direction);
	dot_oc_axis = vec_dot(vec_sub(ray.origin, obj->data.s_cylinder.base),
			obj->data.s_cylinder.axis);
	params[0] = 1.0 - dot_dir_axis * dot_dir_axis;
	params[1] = 2 * (dot_oc_dir - dot_oc_axis * dot_dir_axis);
	t[0] = (-params[1] - sqrt(disc)) / (2 * params[0]);
	t[1] = (-params[1] + sqrt(disc)) / (2 * params[0]);
	if (t[0] > 0 && is_cylinder_intersection_inside(ray, obj, t[0]))
		return (t[0]);
	if (t[1] > 0 && is_cylinder_intersection_inside(ray, obj, t[1]))
		return (t[1]);
	return (-1.0);
}

double	find_cylinder_cap_intersection(t_ray ray, t_object *obj,
		double dot_dir_axis)
{
	double	t1;
	double	t2;
	double	denom;
	double	res;

	denom = dot_dir_axis;
	res = -1.0;
	if (fabs(denom) > 1e-4)
	{
		t1 = (vec_dot(obj->data.s_cylinder.base, obj->data.s_cylinder.axis)
				- vec_dot(ray.origin, obj->data.s_cylinder.axis)) / denom;
		t2 = (vec_dot(vec_add(obj->data.s_cylinder.base,
						vec_mul(obj->data.s_cylinder.axis,
							obj->data.s_cylinder.height)),
					obj->data.s_cylinder.axis) - vec_dot(ray.origin,
					obj->data.s_cylinder.axis)) / denom;
		if (t1 > 0 && is_cylinder_intersection_on_cap(ray, obj, t1, 0))
			res = t1;
		if (t2 > 0 && is_cylinder_intersection_on_cap(ray, obj, t2, 1))
		{
			if (res < 0 || t2 < res)
				res = t2;
		}
	}
	return (res);
}
