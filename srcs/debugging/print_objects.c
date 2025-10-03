/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:40:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/28 16:58:34 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// ANSI escape codes
#define C_RESET   "\033[0m"
#define C_CYAN    "\033[36m"
#define C_YELLOW  "\033[33m"
#define C_RED     "\033[31m"

static void	print_color(const char *label, t_color c)
{
	printf(C_YELLOW "%s" C_RESET "(%d, %d, %d)\n",
		label, c.r, c.g, c.b);
}

static const char	*get_texture_type_name(t_texture_type type)
{
	if (type == TEXTURE_NONE)
		return ("NONE");
	else if (type == TEXTURE_CHECKERBOARD)
		return ("CHECKERBOARD");
	else if (type == TEXTURE_BUMP_MAP)
		return ("BUMP_MAP");
	else
		return ("UNKNOWN");
}

void	print_sphere_data(const t_object *obj);
void	print_plane_data(const t_object *obj);
void	print_cylinder_data(const t_object *obj);
void	print_cone_data(const t_object *obj);

static void	print_object_common(const t_object *obj)
{
	print_color("  color =", obj->color);
	printf("  shininess=%.6f\n", obj->shininess);
	printf("  texture_type=%s\n", get_texture_type_name(obj->texture_type));
	printf("  texture_scale=%.6f\n", obj->texture_scale);
}

void	print_objects(const t_object *obj)
{
	int	index;

	index = 0;
	while (obj)
	{
		printf(C_CYAN "Object[%d]: type=", index++);
		if (obj->type == SPHERE)
			print_sphere_data(obj);
		else if (obj->type == LIGHT)
			print_sphere_data(obj);
		else if (obj->type == PLANE)
			print_plane_data(obj);
		else if (obj->type == CYLINDER)
			print_cylinder_data(obj);
		else if (obj->type == CONE)
			print_cone_data(obj);
		print_object_common(obj);
		obj = obj->next;
	}
	if (index == 0)
		printf(C_RED "(no objects)\n" C_RESET);
}
