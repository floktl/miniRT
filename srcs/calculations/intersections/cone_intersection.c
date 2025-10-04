/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/04 11:58:46 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
intersection formula:
((OC + t*D) . A)^2 = |OC + t*D|^2 * cos^2(theta)
cos^2(theta) = h^2 / (r^2 + h^2) = 1 / (1 + (r/h)^2)
*/

#include "miniRT.h"

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
	disc = calculate_cone_quadratic_terms(ray.direction, ov, obj, cos2_theta);
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
