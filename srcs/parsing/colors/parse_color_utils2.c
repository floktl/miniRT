/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:49:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 15:12:10 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Validates that color parts are valid integer strings */
int	validate_and_parse_parts(char **trimmed_parts, char **parts,
		char *clean_str)
{
	(void)parts;
	(void)clean_str;
	if (!is_integer_string(trimmed_parts[0])
		|| !is_integer_string(trimmed_parts[1])
		|| !is_integer_string(trimmed_parts[2]))
	{
		return (0);
	}
	return (1);
}

/* Frees all allocated memory for color parsing */
void	cleanup_memory(char **trimmed_parts, char **parts, char *clean_str)
{
	int	i;

	if (trimmed_parts)
	{
		i = 0;
		while (i < 3)
		{
			if (trimmed_parts[i])
				free(trimmed_parts[i]);
			i++;
		}
	}
	if (parts)
	{
		i = 0;
		while (parts[i])
		{
			if (parts[i])
				free(parts[i]);
			i++;
		}
		free(parts);
	}
	if (clean_str)
		free(clean_str);
}
