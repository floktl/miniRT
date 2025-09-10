/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:17:50 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/26 13:12:48 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3d	vec_add(t_vec3d a, t_vec3d b)
{
	return ((t_vec3d){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3d	vec_sub(t_vec3d a, t_vec3d b)
{
	return ((t_vec3d){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3d	vec_mul(t_vec3d a, double scalar)
{
	return ((t_vec3d){a.x * scalar, a.y * scalar, a.z * scalar});
}

double	vec_dot(t_vec3d a, t_vec3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	vec_length(t_vec3d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
