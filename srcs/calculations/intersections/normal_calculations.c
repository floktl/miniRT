/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/04 11:59:19 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Normal Vector Calculation System:
**
** This system calculates surface normals for different geometric objects.
** Normal vectors are perpendicular to the surface at a given point and
** are essential for lighting calculations and shading.
**
** Key concepts:
** - Normal: A vector perpendicular to a surface at a specific point
** - Surface normal: Used to determine how light reflects off surfaces
** - Unit normal: Normalized vector (length = 1) for consistent calculations
**
** Process:
** 1. Determine object type (sphere, plane, cylinder, cone)
** 2. Calculate the appropriate normal based on geometry
** 3. Normalize the result for consistent lighting calculations
*/

static t_vec3d	get_cylinder_normal(t_object *obj, t_vec3d point)
{
	t_vec3d	v;
	t_vec3d	perp;
	double	m;

	v = vec_sub(point, obj->data.s_cylinder.base);
	m = vec_dot(v, obj->data.s_cylinder.axis);
	perp = vec_sub(v, vec_mul(obj->data.s_cylinder.axis, m));
	return (vec_normalize(perp));
}

static t_vec3d	get_cone_normal(t_object *obj, t_vec3d point)
{
	t_vec3d	v;
	t_vec3d	scaled_axis;
	double	m;
	double	k;

	v = vec_sub(point, obj->data.s_cone.vertex);
	m = vec_dot(v, obj->data.s_cone.axis);
	k = obj->data.s_cone.radius / obj->data.s_cone.height;
	scaled_axis = vec_mul(obj->data.s_cone.axis, m * (1 + k * k));
	return (vec_normalize(vec_sub(v, scaled_axis)));
}

t_vec3d	get_normal(t_vec3d point, t_object *obj)
{
	t_vec3d	normal;

	if (obj->type == SPHERE || obj->type == LIGHT)
	{
		normal = vec_sub(point, obj->data.s_sphere.center);
		normal = vec_normalize(normal);
	}
	else if (obj->type == PLANE)
		normal = obj->data.s_plane.normal;
	else if (obj->type == CYLINDER)
		normal = get_cylinder_normal(obj, point);
	else if (obj->type == CONE)
		normal = get_cone_normal(obj, point);
	else
		normal = (t_vec3d){0, 0, 1};
	return (normal);
}
