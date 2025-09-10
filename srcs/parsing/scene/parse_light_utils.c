/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:57:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/26 13:12:48 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Cleans up light memory and returns error on parsing failure */
int	cleanup_light_error(t_light *light, const char *message)
{
	printf("[Light] %s\n", message);
	free(light);
	return (1);
}

/* Parses light position from tokens */
int	parse_light_position(char **tokens, int *idx, int token_count,
		t_vec3d_res *pr)
{
	*pr = parse_vec3d_tokens(tokens, idx, token_count);
	if (!(*pr).success)
		return (1);
	return (0);
}

/* Parses light brightness from tokens */
int	parse_light_brightness(char **tokens, int *idx, int token_count,
		t_float_res *br)
{
	*br = parse_float_tokens(tokens, idx, token_count);
	if (!(*br).success)
		return (1);
	return (0);
}

/* Parses light color from tokens */
int	parse_light_color(char **tokens, int *idx, int token_count,
		t_clr_res *cr)
{
	*cr = parse_color_tokens(tokens, idx, token_count);
	if (!(*cr).success || *idx != token_count)
		return (1);
	return (0);
}
