/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:03:31 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 18:59:00 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// ANSI escape codes
#define C_RESET   "\033[0m"
#define C_CYAN    "\033[36m"
#define C_YELLOW  "\033[33m"
#define C_RED     "\033[31m"

static void	print_vec3(const char *label, t_vec3 v)
{
	printf(C_YELLOW "%s" C_RESET "(%.6f, %.6f, %.6f)\n",
		label, v.x, v.y, v.z);
}

static void	print_color(const char *label, t_color c)
{
	printf(C_YELLOW "%s" C_RESET "(%d, %d, %d)\n",
		label, c.r, c.g, c.b);
}

void	print_objects(const t_object *obj, int *index);

static void	print_lights(const t_light *light)
{
	int	index;

	index = 0;
	while (light)
	{
		printf(C_CYAN "Light[%d]:" C_RESET "\n", index);
		print_vec3("  position=", light->position);
		printf("  brightness=%.6f\n", light->brightness);
		print_color("  color   =", light->color);
		light = light->next;
		index++;
	}
	if (index == 0)
		printf(C_RED "(no lights)\n" C_RESET);
}

void	print_scene(const t_scene *scene)
{
	int	index;

	index = 0;
	if (!scene)
	{
		printf(C_RED "Scene: (null)\n" C_RESET);
		return ;
	}
	printf(C_CYAN "\n=== SCENE ===\n\n" C_RESET);
	printf(C_CYAN "Ambient:\n" C_RESET);
	printf("  ratio=%.6f\n", scene->ambient.ratio);
	print_color("  color=", scene->ambient.color);
	printf(C_CYAN "Camera:\n" C_RESET);
	print_vec3("  position=", scene->camera.position);
	print_vec3("  direction=", scene->camera.direction);
	printf("  fov=%.6f\n", scene->camera.fov);
	printf(C_CYAN "Lights:\n" C_RESET);
	print_lights(scene->lights);
	printf(C_CYAN "Objects:\n" C_RESET);
	print_objects(scene->objects, &index);
	if (index == 0)
		printf(C_RED "(no objects)\n" C_RESET);
	printf(C_CYAN "\n=============\n\n" C_RESET);
}
