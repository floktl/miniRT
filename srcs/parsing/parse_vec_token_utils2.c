/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec_token_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:49:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 15:15:04 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

vec3_res	process_single(char **tokens, int *local_idx, char **str)
{
	t_vec3	v;

	handle_single_vec_token(tokens, local_idx, str);
	v = parse_vec3(*str);
	if (check_vec_validity(v, *str))
		return (set_vec3_res(v, *local_idx, local_idx));
	return ((vec3_res){{0.0f, 0.0f, 0.0f}, 0});
}

vec3_res	handle_loop(char **tokens, int *local_idx,
		int token_count, char **str)
{
	if (process_vec_tokens_loop(tokens, local_idx, token_count, str))
		return (set_vec3_res(parse_vec3(*str), *local_idx, local_idx));
	return ((vec3_res){{0.0f, 0.0f, 0.0f}, 0});
}
