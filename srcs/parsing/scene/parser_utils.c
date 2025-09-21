/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 15:45:06 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Counts the number of tokens in a token array */
int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

/* Removes trailing whitespace and newline characters from a token */
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

/* Trims all tokens in array to remove whitespace and newlines */
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

/* Replaces all tab characters with spaces in a line */
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

/* Checks if color is invalid (zero but not explicitly 0,0,0) */
int	color_invalid(t_color c, const char *raw)
{
	if (c.r == 0 && c.g == 0 && c.b == 0 && ft_strncmp(raw, "0,0,0", 5) != 0)
		return (1);
	return (0);
}
