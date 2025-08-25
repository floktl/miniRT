/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 13:52:39 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

void	trim_token(char *s)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n'
			|| s[len - 1] == '\r' || s[len - 1] == ' '))
	{
		s[len - 1] = '\0';
		len--;
	}
}

void	trim_all_tokens(char **tokens, int token_count)
{
	int	i;

	i = 0;
	while (i < token_count && i < 6)
	{
		trim_token(tokens[i]);
		i++;
	}
}

void	replace_tabs_with_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
}
