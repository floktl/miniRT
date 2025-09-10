/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec_token_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:49:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/26 13:12:48 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3d_res	process_single(char **tokens, int *local_idx, char **str)
{
	t_vec3d	v;

	handle_single_vec_token(tokens, local_idx, str);
	v = parse_vec3d(*str);
	if (check_vec_validity(v, *str))
		return (set_vec3d_res(v, *local_idx, local_idx));
	return ((t_vec3d_res){{0.0f, 0.0f, 0.0f}, 0});
}

t_vec3d_res	handle_loop(char **tokens, int *local_idx,
		int token_count, char **str)
{
	if (process_vec_tokens_loop(tokens, local_idx, token_count, str))
		return (set_vec3d_res(parse_vec3d(*str), *local_idx, local_idx));
	return ((t_vec3d_res){{0.0f, 0.0f, 0.0f}, 0});
}
