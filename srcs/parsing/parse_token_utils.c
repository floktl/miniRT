/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/25 09:43:58 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	check_color_validity(t_color c, char *str)
{
	if (!is_color_zero(c) || (ft_strncmp(str, "0,0,0", 5) == 0
			&& ft_strlen(str) == 5))
		return (1);
	return (0);
}

static int	cleanup_and_return(char **str, int status)
{
	free(*str);
	*str = NULL;
	return (status);
}

int	process_color_tokens_loop(char **tokens, int *local_idx,
		int token_count, char **str)
{
	char	*tmp;
	t_color	c;

	while (*local_idx < token_count)
	{
		if (ft_strlen(*str) > 0 && (*str)[ft_strlen(*str) - 1] != ',')
		{
			tmp = ft_strjoin(*str, " ");
			if (!tmp)
				return (cleanup_and_return(str, 1));
			free(*str);
			*str = tmp;
		}
		tmp = ft_strjoin(*str, tokens[*local_idx]);
		if (!tmp)
			return (cleanup_and_return(str, 1));
		free(*str);
		*str = tmp;
		(*local_idx)++;
		c = parse_color(*str);
		if (check_color_validity(c, *str))
			return (1);
	}
	return (cleanup_and_return(str, 0));
}

t_clr_res	init_clr_res(void)
{
	t_clr_res	res;

	res = (t_clr_res){{0, 0, 0}, 0};
	return (res);
}

int	handle_single_token(char **tokens, int *local_idx, char **str)
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
