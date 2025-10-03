/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 21:10:26 by mezhang           #+#    #+#             */
/*   Updated: 2025/10/03 21:37:16 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// v[0]: assuming point is on top cap
// v[1]: assuming point is on bottom cap

static t_vec3d	get_cylinder_normal(t_object *obj, t_vec3d point)
{
	t_vec3d	v_top;
	t_vec3d	v_other;
	t_vec3d	perp;
	double	m;
    double dist;

    v_top = vec_sub(point, vec_add(obj->data.s_cylinder.base, vec_mul(obj->data.s_cylinder.axis, obj->data.s_cylinder.height)));
    m = vec_dot(v_top, obj->data.s_cylinder.axis);
    dist = vec_length(vec_sub(v_top, vec_mul(obj->data.s_cylinder.axis, m)));
    if (fabs(m) < 1e-6 && dist <= obj->data.s_cylinder.radius)
    {
        return (obj->data.s_cylinder.axis);
    }
	v_other = vec_sub(point, obj->data.s_cylinder.base);
	m = vec_dot(v_other, obj->data.s_cylinder.axis);
    dist = vec_length(vec_sub(v_other, vec_mul(obj->data.s_cylinder.axis, m)));
    if (fabs(m) < 1e-6 && dist <= obj->data.s_cylinder.radius)
    {
        return (vec_mul(obj->data.s_cylinder.axis, -1));
    }
    perp = vec_sub(v_other, vec_mul(obj->data.s_cylinder.axis, m));
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