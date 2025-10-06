/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/06 09:20:33 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
|(P - C) - (P - C) . A|^2 = r ^2
|OC + t*D - (OC + t*D) . A|^2 = r ^2
P = O + tD
 */

#include "miniRT.h"


double	intersect_cylinder(t_ray ray, t_object *obj)
{
	t_vec3d	oc;
	double	dot_dir_axis;
	double	disc;
	double	t_side;
	double	t_cap;

	oc = vec_sub(ray.origin, obj->data.s_cylinder.base);
	dot_dir_axis = vec_dot(ray.direction, obj->data.s_cylinder.axis);
	disc = calculate_cylinder_quadratic_terms(ray.direction, oc, obj,
			dot_dir_axis);
	if (disc < 0)
		t_side = -1.0;
	else
		t_side = find_cylinder_side_intersection(ray, obj, dot_dir_axis, disc);
	t_cap = find_cylinder_cap_intersection(ray, obj, dot_dir_axis);
	if (t_side > 0.0 && (t_cap < 0.0 || t_side < t_cap))
		return (t_side);
	if (t_cap > 0.0)
		return (t_cap);
	return (-1.0);
}
