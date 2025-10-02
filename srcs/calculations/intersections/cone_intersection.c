/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/02 16:27:27 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double calculate_quadratic_terms(t_vec3d ray_dir, t_vec3d oc, t_object *obj, double cos2_theta)
{
	double	dot_dir_axis;
	double	dot_oc_axis;
	double  dot_oc_dir;
	double  params[3]; // a, b, c

	dot_dir_axis = vec_dot(ray_dir, obj->data.s_cone.axis);
	dot_oc_axis = vec_dot(oc, obj->data.s_cone.axis);
	dot_oc_dir = vec_dot(oc, ray_dir);
	params[0] = dot_dir_axis * dot_dir_axis - cos2_theta;
	params[1] = 2 * (dot_dir_axis * dot_oc_axis - dot_oc_dir * cos2_theta);
	params[2] = dot_oc_axis * dot_oc_axis - vec_dot(oc, oc) * cos2_theta;
	return (params[1] * params[1] - 4 * params[0] * params[2]);
}

static bool is_intersection_within_cone(t_ray ray, t_object *obj, double t)
{
	t_vec3d	p;
	t_vec3d	v;
	t_vec3d	apex_to_p;

	p = vec_add(ray.origin, vec_scale(ray.direction, t));
	v = vec_sub(p, obj->data.s_cone.vertex);
	apex_to_p = vec_dot(v, obj->data.s_cone.axis);
	if (apex_to_p < 0 || apex_to_p > obj->data.s_cone.height)
		return (false);
	return (true);
}

static double find_cone_intersection(t_ray ray, t_object *obj, double b, double disc)
{
	double t1;
	double t2;

	t1 = (-b - sqrt(disc)) / (2 * a);
	t2 = (-b + sqrt(disc)) / (2 * a);
	if (t1 > 0.0 && is_intersection_within_cone(ray, obj, t1))
		return (t1);
	if (t2 > 0.0 && is_intersection_within_cone(ray, obj, t2))
		return (t2);
	return (-1.0);
}

static double	intersect_cone(t_ray ray, t_object *obj)
{
	t_vec3d	oc;
	double	b;
	double	cos2_theta;
	double	disc;

	oc = vec_sub(ray.origin, obj->data.s_cone.vertex);
	b = vec_dot(oc, ray.direction); // get normalized axis
	cos2_theta = (obj->data.s_cone.height * obj->data.s_cone.height)
		/ (obj->data.s_cone.radius * obj->data.s_cone.radius
			+ obj->data.s_cone.height * obj->data.s_cone.height);
	disc = calculate_quadratic_terms(ray.direction, oc, obj, cos2_theta);
	if (disc < 0.0)
		return (-1.0);
	return (find_cone_intersection(ray, obj, b, disc));
}
