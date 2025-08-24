/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:07:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 12:54:31 by Florian Kei      ###   ########.fr       */
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
	int		token_count;
	int		idx;
	t_color col;

	// Check if ambient already exists
	if (scene->ambient.ratio != 0.0) {
		printf("[Ambient] Duplicate ambient element not allowed\n");
		return (1);
	}

	token_count = 0;
	while (tokens[token_count]) token_count++;
	idx = 1;

	float_result fr = parse_float_tokens(tokens, &idx, token_count);
	if (!fr.success) {
		printf("[Ambient] Failed to parse ratio\n");
		return (1);
	}
	printf("[Ambient] Parsed ratio: %f\n", fr.f);

	color_result cr = parse_color_tokens(tokens, &idx, token_count);
	if (!cr.success || idx != token_count) {
		printf("[Ambient] Failed to parse color or extra tokens\n");
		return (1);
	}
	col = cr.c;
	printf("[Ambient] Parsed color: r=%d g=%d b=%d\n", col.r, col.g, col.b);

	if (fr.f < 0 || fr.f > 1) {
		printf("[Ambient][ERROR] Ratio out of range [0..1]\n");
		return (1);
	}

	scene->ambient.ratio = fr.f;
	scene->ambient.color = col;
	printf("[Ambient] OK (ratio=%f, color=%d,%d,%d)\n", fr.f, col.r, col.g, col.b);
	return (0);
}


int	parse_camera(char **tokens, t_scene *scene)
{
	int		token_count;
	int		idx;

	// Check if camera already exists
	if (scene->camera.fov != 0.0) {
		printf("[Camera] Duplicate camera element not allowed\n");
		return (1);
	}

	token_count = 0;
	while (tokens[token_count]) token_count++;
	idx = 1;

	vec3_result pr = parse_vec3_tokens(tokens, &idx, token_count);
	if (!pr.success) {
		printf("[Camera] Failed to parse position\n");
		return (1);
	}
	scene->camera.position = pr.v;

	vec3_result dr = parse_vec3_tokens(tokens, &idx, token_count);
	if (!dr.success) {
		printf("[Camera] Failed to parse direction\n");
		return (1);
	}
	// Check for zero-length direction vector
	if (is_vec_zero(dr.v)) {
		printf("[Camera] Direction vector cannot be zero-length\n");
		return (1);
	}
	scene->camera.direction = vec_normalize(dr.v);

	float_result fr = parse_float_tokens(tokens, &idx, token_count);
	if (!fr.success || idx != token_count) {
		printf("[Camera] Failed to parse FOV or extra tokens\n");
		return (1);
	}
	scene->camera.fov = fr.f;

	if (scene->camera.fov < 0 || scene->camera.fov > 180) {
		return (1);
	}
	return (0);
}

int	parse_light(char **tokens, t_scene *scene)
{
	t_light	*light;

	int token_count = 0;
	while (tokens[token_count]) token_count++;
	int idx = 1;

	light = malloc(sizeof(t_light));
	if (!light)
		return (1);

	vec3_result pr = parse_vec3_tokens(tokens, &idx, token_count);
	if (!pr.success) {
		printf("[Light] Failed to parse position\n");
		free(light);
		return (1);
	}
	light->position = pr.v;

	float_result br = parse_float_tokens(tokens, &idx, token_count);
	if (!br.success) {
		printf("[Light] Failed to parse brightness\n");
		free(light);
		return (1);
	}
	light->brightness = br.f;

	color_result cr = parse_color_tokens(tokens, &idx, token_count);
	if (!cr.success || idx != token_count) {
		printf("[Light] Failed to parse color or extra tokens\n");
		free(light);
		return (1);
	}
	light->color = cr.c;

	// Check brightness BEFORE adding to scene
	if (light->brightness < 0 || light->brightness > 1) {
		printf("[Light] Brightness out of range [0..1]\n");
		free(light);
		return (1);
	}

	// Only add to scene after all validation passes
	light->next = scene->lights;
	scene->lights = light;
	return (0);
}
