/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:13:13 by fkeitel          ###   ########.fr       */
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

	oc = vec_sub(ray.origin, obj->data.s_sphere.center);
	b = vec_dot(ray.direction, oc);
	disc = calculate_quadratic_terms(ray.direction, oc,
			obj->data.s_sphere.radius);
	if (disc < 0.0)
		return (-1.0);
	return (find_sphere_intersection(b, disc));
}

double	intersect_sphere(t_ray ray, t_object *obj)
{
	return (process_sphere_intersection(ray, obj));
}
