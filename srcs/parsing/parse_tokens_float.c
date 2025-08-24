/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_float.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:37:48 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 15:14:51 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <math.h>

static float_res	init_float_res(void)
{
	float_res	res;

	res = (float_res){0.0f, 0};
	return (res);
}

static int	check_float_validity(float f)
{
	if (isnan(f) || isinf(f))
		return (0);
	return (1);
}

static int	process_float_token(char **tokens, int *local_idx, char **str)
{
	char	*tmp;

	tmp = ft_strdup(tokens[*local_idx]);
	free(*str);
	*str = tmp;
	(*local_idx)++;
	return (1);
}

static float_res	set_float_res(float f, int local_idx, int *idx)
{
	float_res	res;

	res.f = f;
	res.success = 1;
	*idx = local_idx;
	return (res);
}

float_res	parse_float_tokens(char **tokens, int *idx, int token_count)
{
	float_res	res;
	char		*str;
	int			local_idx;
	float		f;

	res = init_float_res();
	str = ft_strdup("");
	local_idx = *idx;
	if (local_idx >= token_count)
	{
		free(str);
		return (res);
	}
	process_float_token(tokens, &local_idx, &str);
	f = ft_atof(str);
	if (!check_float_validity(f))
	{
		free(str);
		return (res);
	}
	res = set_float_res(f, local_idx, idx);
	free(str);
	return (res);
}
