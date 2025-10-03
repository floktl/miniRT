/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/03 14:08:54 by mezhang          ###   ########.fr       */
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

static double	find_cone_intersection(t_ray ray, t_object *obj, double disc,
		double cos2_theta)
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

double	intersect_cone(t_ray ray, t_object *obj)
{
	t_vec3d	ov;
	// double	dot_ov_dir;
	double	cos2_theta;
	double	disc;

	ov = vec_sub(ray.origin, obj->data.s_cone.vertex);
	// dot_ov_dir = vec_dot(ov, ray.direction);
	cos2_theta = (obj->data.s_cone.height * obj->data.s_cone.height)
		/ (obj->data.s_cone.radius * obj->data.s_cone.radius
			+ obj->data.s_cone.height * obj->data.s_cone.height);
	disc = calculate_quadratic_terms(ray.direction, ov, obj, cos2_theta);
	if (disc < 0.0)
		return (-1.0);
	return (find_cone_intersection(ray, obj, disc, cos2_theta));
}
