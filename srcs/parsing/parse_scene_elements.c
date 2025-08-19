/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:07:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/19 15:11:02 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static int	color_invalid(t_color c, const char *raw)
{
	if (c.r == 0 && c.g == 0 && c.b == 0 && ft_strncmp(raw, "0,0,0", 5) != 0)
		return (1);
	return (0);
}

int	parse_ambient(char **tokens, t_scene *scene)
{
	t_color	col;

	if (!tokens || !tokens[1] || !tokens[2])
	{
		printf("[Ambient] Missing tokens (expected ratio,color)\n");
		return (1);
	}
	printf("[Ambient] Raw ratio token: '%s'\n", tokens[1]);
	printf("[Ambient] Raw color token: '%s'\n", tokens[2]);

	scene->ambient.ratio = ft_atof(tokens[1]);
	printf("[Ambient] Parsed ratio: %f\n", scene->ambient.ratio);

	col = parse_color(tokens[2]);
	if (color_invalid(col, tokens[2]))
	{
		printf("[Ambient][ERROR] Invalid color parsed -> %d,%d,%d\n",
			col.r, col.g, col.b);
		return (1);
	}
	printf("[Ambient] Parsed color: r=%d g=%d b=%d\n", col.r, col.g, col.b);

	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
	{
		printf("[Ambient][ERROR] Ratio out of range [0..1]\n");
		return (1);
	}
	if ((col.r | col.g | col.b) == 0 && ft_strncmp(tokens[2], "0,0,0", 5) != 0)
	{
		printf("[Ambient][WARN] Color parsed as 0,0,0 — input may be invalid\n");
		/* keep going; parse_color already validated ranges */
	}
	scene->ambient.color = col;
	printf("[Ambient] OK (ratio=%f, color=%d,%d,%d)\n",
		scene->ambient.ratio, scene->ambient.color.r,
		scene->ambient.color.g, scene->ambient.color.b);
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
