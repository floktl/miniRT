/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:03:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/26 13:12:48 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Sets up light in scene after validation and adds to light list */
int	setup_light(t_light *light, t_scene *scene)
{
	if (validate_light_brightness(light->brightness))
		return (cleanup_light_error(light, "Brightness validation failed"));
	light->next = scene->lights;
	scene->lights = light;
	return (0);
}

/* Parses light position, brightness and color from tokens */
static int	parse_light_data(t_light *light, char **tokens, int *idx,
		int token_count)
{
	t_vec3d_res		pr;
	t_float_res		br;
	t_clr_res		cr;

	if (parse_light_position(tokens, idx, token_count, &pr))
		return (cleanup_light_error(light, "Failed to parse position"));
	light->position = pr.v;
	if (parse_light_brightness(tokens, idx, token_count, &br))
		return (cleanup_light_error(light, "Failed to parse brightness"));
	light->brightness = br.f;
	if (parse_light_color(tokens, idx, token_count, &cr))
		return (cleanup_light_error(light, "Failed to parse color"));
	light->color = cr.c;
	return (0);
}

/* Internal function to parse light object from tokens */
int	parse_light_internal(char **tokens, t_scene *scene)
{
	t_light	*light;
	int		token_count;
	int		idx;

	count_and_init_tokens(tokens, &token_count, &idx);
	light = malloc(sizeof(t_light));
	if (!light)
		return (1);
	if (parse_light_data(light, tokens, &idx, token_count))
		return (1);
	return (setup_light(light, scene));
}
