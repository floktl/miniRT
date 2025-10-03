/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_primitives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:45:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/28 16:58:34 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// ANSI escape codes
#define C_RESET   "\033[0m"
#define C_YELLOW  "\033[33m"

static void	print_vec3d(const char *label, t_vec3d v)
{
	printf(C_YELLOW "%s" C_RESET "(%.6f, %.6f, %.6f)\n",
		label, v.x, v.y, v.z);
}

void	print_sphere_data(const t_object *obj)
{
	if (obj->type == LIGHT)
		printf("LIGHT" C_RESET "\n");
	else
		printf("SPHERE" C_RESET "\n");
	print_vec3d("  center=", obj->data.s_sphere.center);
	printf("  radius=%.6f\n", obj->data.s_sphere.radius);
}

void	print_plane_data(const t_object *obj)
{
	printf("PLANE" C_RESET "\n");
	print_vec3d("  point =", obj->data.s_plane.point);
	print_vec3d("  normal=", obj->data.s_plane.normal);
}

void	print_cylinder_data(const t_object *obj)
{
	printf("CYLINDER" C_RESET "\n");
	print_vec3d("  base  =", obj->data.s_cylinder.base);
	print_vec3d("  axis  =", obj->data.s_cylinder.axis);
	printf("  radius=%.6f\n", obj->data.s_cylinder.radius);
	printf("  height=%.6f\n", obj->data.s_cylinder.height);
}

void	print_cone_data(const t_object *obj)
{
	printf("CONE" C_RESET "\n");
	print_vec3d("  center=", obj->data.s_cone.center);
	print_vec3d("  axis  =", obj->data.s_cone.axis);
	printf("  radius=%.6f\n", obj->data.s_cone.radius);
	printf("  height=%.6f\n", obj->data.s_cone.height);
}
