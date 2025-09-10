/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:17:50 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/26 13:12:48 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3d	vec_normalize(t_vec3d v)
{
	double	length;

	length = vec_length(v);
	if (length == 0.0)
	{
		return ((t_vec3d){0, 0, 0});
	}
	return ((t_vec3d){v.x / length, v.y / length, v.z / length});
}

t_vec3d	vec_cross(t_vec3d a, t_vec3d b)
{
	return ((t_vec3d){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}

t_vec3d	vec_reflect(t_vec3d incident, t_vec3d normal)
{
	double	dot_product;

	dot_product = vec_dot(incident, normal);
	return (vec_sub(incident, vec_mul(normal, 2.0 * dot_product)));
}
