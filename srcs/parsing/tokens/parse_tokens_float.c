/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_float.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:37:48 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/01 15:21:35 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_float_res	init_float_res(void)
{
	t_float_res	res;

	res = (t_float_res){0.0f, 0};
	return (res);
}

/* Checks if float value is valid (not NaN or infinity) */
static int	check_float_validity(float f)
{
	if (isnan(f) || isinf(f))
		return (0);
	return (1);
}

/* Processes a single float token by copying it to string */
static int	process_float_token(char **tokens, int *local_idx, char **str)
{
	char	*tmp;

	tmp = ft_strdup(tokens[*local_idx]);
	if (!tmp)
		return (0);
	free(*str);
	*str = tmp;
	(*local_idx)++;
	return (1);
}

static t_float_res	set_float_res(float f, int local_idx, int *idx)
{
	t_float_res	res;

	res.f = f;
	res.success = 1;
	*idx = local_idx;
	return (res);
}

/* Parses float tokens and returns float result with success status */
t_float_res	parse_float_tokens(char **tokens, int *idx, int token_count)
{
	t_float_res	res;
	char		*str;
	int			local_idx;
	float		f;

	res = init_float_res();
	str = ft_strdup("");
	local_idx = *idx;
	if (local_idx >= token_count)
		return (free(str), res);
	process_float_token(tokens, &local_idx, &str);
	f = ft_atof(str);
	if (!check_float_validity(f))
		return (free(str), res);
	res = set_float_res(f, local_idx, idx);
	return (free(str), res);
}
