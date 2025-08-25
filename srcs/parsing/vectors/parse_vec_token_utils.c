/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec_token_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 17:58:59 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_vec_validity(t_vec3 v, char *str)
{
	if (!is_vec_zero(v) || ft_strncmp(str, "0,0,0", 5) == 0)
		return (1);
	return (0);
}

int	process_vec_tokens_loop(char **tokens, int *local_idx,
		int token_count, char **str)
{
	char	*tmp;
	t_vec3	v;

	while (*local_idx < token_count)
	{
		tmp = ft_strjoin(*str, tokens[*local_idx]);
		free(*str);
		*str = tmp;
		(*local_idx)++;
		v = parse_vec3(*str);
		if (check_vec_validity(v, *str))
			return (1);
	}
	return (0);
}

t_vec3_res	init_vec3_res(void)
{
	t_vec3_res	res;

	res = (t_vec3_res){{0.0f, 0.0f, 0.0f}, 0};
	return (res);
}

int	handle_single_vec_token(char **tokens, int *local_idx, char **str)
{
	char	*tmp;

	tmp = ft_strjoin(*str, tokens[*local_idx]);
	free(*str);
	*str = tmp;
	(*local_idx)++;
	return (1);
}

t_vec3_res	set_vec3_res(t_vec3 v, int local_idx, int *idx)
{
	t_vec3_res	res;

	res.v = v;
	res.success = 1;
	*idx = local_idx;
	return (res);
}
