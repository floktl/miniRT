/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/02 12:36:21 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	intersect_plane(t_ray ray, t_object *obj)
{
	t_vec3d oc;
	double	b;
	double	t;

	oc = vec_sub(ray.origin, obj->data.s_plane.point);
	b = vec_dot(ray.direction, obj->data.s_plane.normal);
	if (fabs(b) > 1e-6)
	{
		t = -vec_dot(oc, obj->data.s_plane.normal) / b;
		if (t >= 0.0)
			return (t);
	}
	return (-1.0);
}
