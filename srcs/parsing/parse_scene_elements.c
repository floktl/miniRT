/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:07:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/19 14:34:48 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_ambient(char **tokens, t_scene *scene)
{
	scene->ambient.ratio = ft_atof(tokens[1]);
	scene->ambient.color = parse_color(tokens[2]);
	if (scene->ambient.ratio < 0 || scene->ambient.ratio > 1)
		return (1);
	return (0);
}

int	parse_camera(char **tokens, t_scene *scene)
{
	scene->camera.position = parse_vec3(tokens[1]);
	scene->camera.direction = vec_normalize(parse_vec3(tokens[2]));
	scene->camera.fov = ft_atof(tokens[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (1);
	return (0);
}

int	parse_light(char **tokens, t_scene *scene)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (1);
	light->position = parse_vec3(tokens[1]);
	light->brightness = ft_atof(tokens[2]);
	light->color = parse_color(tokens[3]);
	light->next = scene->lights;
	scene->lights = light;
	if (light->brightness < 0 || light->brightness > 1)
	{
		free(light);
		return (1);
	}
	return (0);
}
