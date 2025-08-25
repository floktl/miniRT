/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 18:40:48 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_texture_type(t_object *obj, char **tokens, int *idx, int token_count)
{
	if (*idx >= token_count)
		return (0);
	if (ft_strncmp(tokens[*idx], "checkerboard", 13) == 0)
	{
		obj->texture_type = TEXTURE_CHECKERBOARD;
		(*idx)++;
		return (0);
	}
	else if (ft_strncmp(tokens[*idx], "bump", 5) == 0)
	{
		obj->texture_type = TEXTURE_BUMP_MAP;
		(*idx)++;
		return (0);
	}
	return (0);
}

int	parse_texture_scale(t_object *obj, char **tokens, int *idx, int token_count)
{
	t_float_res	scale_res;

	if (*idx >= token_count)
		return (0);
	scale_res = parse_float_tokens(tokens, idx, token_count);
	if (!scale_res.success)
		return (1);
	if (scale_res.f <= 0.0)
		return (1);
	obj->texture_scale = scale_res.f;
	return (0);
}
