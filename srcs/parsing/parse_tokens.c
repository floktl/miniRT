/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:39:28 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 16:42:46 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <math.h>

static color_res	handle_single_token_res(char **tokens, int *idx,
		char *str)
{
	t_color		c;
	color_res	res;

	handle_single_token(tokens, idx, &str);
	c = parse_color(str);
	if (check_color_validity(c, str))
	{
		res.c = c;
		res.success = 1;
		// Free the allocated memory before returning
		if (str)
			free(str);
		return (res);
	}
	// Free the allocated memory if validation fails
	if (str)
		free(str);
	return ((color_res){{0, 0, 0}, 0});
}

static color_res	handle_loop_res(char **tokens, int *idx,
		int token_count, char *str)
{
	color_res	res;

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
	return ((color_res){{0, 0, 0}, 0});
}

color_res	parse_color_tokens(char **tokens, int *idx, int token_count)
{
	color_res	res;
	char		*str;

	res = init_color_res();
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
