/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_primitives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:45:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 18:58:48 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// ANSI escape codes
#define C_RESET   "\033[0m"
#define C_YELLOW  "\033[33m"

static void	print_vec3(const char *label, t_vec3 v)
{
	printf(C_YELLOW "%s" C_RESET "(%.6f, %.6f, %.6f)\n",
		label, v.x, v.y, v.z);
}

void	print_sphere_data(const t_object *obj)
{
	printf("SPHERE" C_RESET "\n");
	print_vec3("  center=", obj->data.s_sphere.center);
	printf("  radius=%.6f\n", obj->data.s_sphere.radius);
}

void	print_plane_data(const t_object *obj)
{
	printf("PLANE" C_RESET "\n");
	print_vec3("  point =", obj->data.s_plane.point);
	print_vec3("  normal=", obj->data.s_plane.normal);
}

void	print_cylinder_data(const t_object *obj)
{
	printf("CYLINDER" C_RESET "\n");
	print_vec3("  base  =", obj->data.s_cylinder.base);
	print_vec3("  axis  =", obj->data.s_cylinder.axis);
	printf("  radius=%.6f\n", obj->data.s_cylinder.radius);
	printf("  height=%.6f\n", obj->data.s_cylinder.height);
}

void	print_cone_data(const t_object *obj)
{
	printf("CONE" C_RESET "\n");
	print_vec3("  center=", obj->data.s_cone.center);
	print_vec3("  axis  =", obj->data.s_cone.axis);
	printf("  radius=%.6f\n", obj->data.s_cone.radius);
	printf("  height=%.6f\n", obj->data.s_cone.height);
}
