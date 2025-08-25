/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:57:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/25 09:43:58 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	cleanup_light_error(t_light *light, const char *message)
{
	printf("[Light] %s\n", message);
	free(light);
	return (1);
}

int	parse_light_position(char **tokens, int *idx, int token_count,
		t_vec3_res *pr)
{
	*pr = parse_vec3_tokens(tokens, idx, token_count);
	if (!(*pr).success)
		return (1);
	return (0);
}

int	parse_light_brightness(char **tokens, int *idx, int token_count,
		t_float_res *br)
{
	*br = parse_float_tokens(tokens, idx, token_count);
	if (!(*br).success)
		return (1);
	return (0);
}

int	parse_light_color(char **tokens, int *idx, int token_count,
		t_clr_res *cr)
{
	*cr = parse_color_tokens(tokens, idx, token_count);
	if (!(*cr).success || *idx != token_count)
		return (1);
	return (0);
}
