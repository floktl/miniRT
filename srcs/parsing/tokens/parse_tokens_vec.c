/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_vec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:39:16 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/26 13:12:48 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3d_res	parse_vec3d_tokens(char **tokens, int *idx, int token_count)
{
	t_vec3d_res		res;
	char			*str;
	int				local_idx;

	res = init_vec3d_res();
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
