/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:19:58 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/19 12:42:58 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
* GEOMETRIC PRIMITIVE INTERSECTION CALCULATIONS
*
* Intersection testing determines where rays hit geometric objects:
* - Ray-sphere intersection uses quadratic equation solving
* - Ray-plane intersection uses dot product calculations
* - Ray-cylinder intersection combines quadratic solving with height bounds
* - Ray-cone intersection uses quadratic equations with conical constraints
*
* Mathematical concepts:
* - Quadratic equations: ax² + bx + c = 0 for curved surfaces
* - Dot products: For plane intersections and distance calculations
* - Parametric equations: Ray = origin + t*direction
* - Distance bounds: Checking if intersection is within object limits
*/

// t = - (u \cdot (o-c)) \pm \sqrt{(u \cdot (o-c))^2 - (\|o-c\|^2 - r^2)}
//  Equation for a line starting at o
// x = o + d * u
// x : points on the line
// o : origin of the line
// d : distance from the origin of the line
// u : direction of line (a non-zero vector)
double	intersect_sphere(t_ray ray, t_object *obj)
{
	t_vec3d o = ray.origin;					// ray origin
	t_vec3d u = ray.direction;				// ray direction
	t_vec3d c = obj->data.s_sphere.center;	// sphere center
	double  r = obj->data.s_sphere.radius;	// sphere radius

	// Vector from sphere center to ray origin
	t_vec3d oc = vec_sub(o, c);

	// Compute terms of quadratic
	double b = vec_dot(u, oc);				// u · (o - c)
	double c_term = vec_dot(oc, oc) - r * r;

	// Discriminant
	double disc = b * b - c_term;

	if (disc < 0.0)
		return (-1.0);  // no intersection

	// Two possible solutions
	double t1 = -b - sqrt(disc);
	double t2 = -b + sqrt(disc);

	// Pick the smallest positive t
	if (t1 > 0.0)
		return (t1);
	if (t2 > 0.0)
		return (t2);

	return (-1.0); // both are behind ray origin
}

double	intersect_plane(t_ray ray, t_object *obj)
{
	return (-1.0);
}

double	intersect_cylinder(t_ray ray, t_object *obj)
{
	return (-1.0);
}

double	intersect_cone(t_ray ray, t_object *obj)
{
	return (-1.0);
}
