/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:49:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 17:33:26 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	validate_camera_fov(float fov)
{
	if (fov < 0 || fov > 180)
		return (1);
	return (0);
}

int	validate_light_brightness(float brightness)
{
	if (brightness < 0 || brightness > 1)
	{
		printf("[Light] Brightness out of range [0..1]\n");
		return (1);
	}
	return (0);
}

int	parse_error(const char *element, const char *message)
{
	printf("[%s] %s\n", element, message);
	return (1);
}

int	count_and_init_tokens(char **tokens, int *token_count, int *idx)
{
	*token_count = 0;
	while (tokens[*token_count])
		(*token_count)++;
	*idx = 1;
	return (0);
}

int	parse_ambient_ratio(char **tokens, int *idx, int token_count,
		t_float_res *fr)
{
	*fr = parse_float_tokens(tokens, idx, token_count);
	if (!(*fr).success)
		return (parse_error("Ambient", "Failed to parse ratio"));
	printf("[Ambient] Parsed ratio: %f\n", (*fr).f);
	return (0);
}
