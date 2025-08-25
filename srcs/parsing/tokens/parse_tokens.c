/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:39:28 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/25 09:43:58 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

static t_clr_res	handle_single_token_res(char **tokens, int *idx,
		char *str)
{
	t_color		c;
	t_clr_res	res;

	handle_single_token(tokens, idx, &str);
	c = parse_color(str);
	if (check_color_validity(c, str))
	{
		res.c = c;
		res.success = 1;
		if (str)
			free(str);
		return (res);
	}
	if (str)
		free(str);
	return ((t_clr_res){{0, 0, 0}, 0});
}

static t_clr_res	handle_loop_res(char **tokens, int *idx,
		int token_count, char *str)
{
	t_clr_res	res;

	if (str == NULL)
		str = ft_strdup("");
	if (process_color_tokens_loop(tokens, idx, token_count, &str))
	{
		res.c = parse_color(str);
		res.success = 1;
		return (res);
	}
	if (str)
		free(str);
	return ((t_clr_res){{0, 0, 0}, 0});
}

t_clr_res	parse_color_tokens(char **tokens, int *idx, int token_count)
{
	t_clr_res	res;
	char		*str;

	res = init_clr_res();
	str = ft_strdup("");
	if (*idx >= token_count)
	{
		free(str);
		return (res);
	}
	res = handle_single_token_res(tokens, idx, str);
	if (res.success)
		return (res);
	res = handle_loop_res(tokens, idx, token_count, NULL);
	if (res.success)
		return (res);
	if (str)
		free(str);
	return (res);
}
