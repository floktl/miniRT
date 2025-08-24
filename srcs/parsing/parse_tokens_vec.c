/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_vec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:39:16 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 14:43:17 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <math.h>

vec3_res	parse_vec3_tokens(char **tokens, int *idx, int token_count)
{
	vec3_res		res;
	char			*str;
	int				local_idx;

	res = init_vec3_res();
	str = ft_strdup("");
	local_idx = *idx;
	if (local_idx >= token_count)
	{
		free(str);
		return (res);
	}
	res = process_single(tokens, &local_idx, &str);
	if (res.success)
	{
		*idx = local_idx;
		free(str);
		return (res);
	}
	res = handle_loop(tokens, &local_idx, token_count, &str);
	if (res.success)
		*idx = local_idx;
	free(str);
	return (res);
}
