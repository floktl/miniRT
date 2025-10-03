/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/01 14:24:43 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	calculate_quadratic_terms(t_vec3d u, t_vec3d oc, double r)
{
	double	b;
	double	c_term;

	b = vec_dot(u, oc);
	c_term = vec_dot(oc, oc) - r * r;
	return (b * b - c_term);
}

static double	find_sphere_intersection(double b, double disc)
{
	double	t1;
	double	t2;

	t1 = -b - sqrt(disc);
	t2 = -b + sqrt(disc);
	if (t1 > 0.0 && t2 > 0.0)
	{
		if (t1 < t2)
			return (t1);
		else
			return (t2);
	}
	if (t1 > 0.0)
		return (t1);
	if (t2 > 0.0)
		return (t2);
	return (-1.0);
}

static double	process_sphere_intersection(t_ray ray, t_object *obj)
{
	t_vec3d	oc;
	double	b;
	double	disc;
	double	result;

	oc = vec_sub(ray.origin, obj->data.s_sphere.center);
	b = vec_dot(ray.direction, oc);
	disc = calculate_quadratic_terms(ray.direction, oc,
			obj->data.s_sphere.radius);
	if (disc < 0.0)
		return (-1.0);
	result = find_sphere_intersection(b, disc);
	return (result);
}

double	intersect_sphere(t_ray ray, t_object *obj)
{
	return (process_sphere_intersection(ray, obj));
}

double	intersect_sphere_debug(t_ray ray, t_object *obj)
{
	t_vec3d	oc;
	double	b;
	double	disc;
	double	result;

	oc = vec_sub(ray.origin, obj->data.s_sphere.center);
	b = vec_dot(ray.direction, oc);
	disc = calculate_quadratic_terms(ray.direction, oc,
			obj->data.s_sphere.radius);
	printf("[DEBUG SPHERE] OC=(%.3f,%.3f,%.3f) b=%.3f disc=%.3f radius=%.3f\n",
		oc.x, oc.y, oc.z, b, disc, obj->data.s_sphere.radius);
	if (disc < 0.0)
	{
		printf("[DEBUG SPHERE] No intersection (discriminant < 0)\n");
		return (-1.0);
	}
	result = find_sphere_intersection(b, disc);
	printf("[DEBUG SPHERE] Intersection result: %.3f\n", result);
	return (result);
}
