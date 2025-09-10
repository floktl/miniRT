/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shininess.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:15:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 15:14:53 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Validates shininess value is within valid range */
static int	validate_shininess(double shininess)
{
	if (shininess < 0.0 || shininess > 1000.0)
		return (0);
	return (1);
}

/* Parses object shininess value from tokens */
int	parse_object_shininess(t_object *obj, char **tokens, int *idx,
		int token_count)
{
	t_float_res	shininess_res;

	if (*idx >= token_count)
	{
		obj->shininess = 32.0;
		return (0);
	}
	shininess_res = parse_float_tokens(tokens, idx, token_count);
	if (!shininess_res.success)
		return (1);
	if (!validate_shininess(shininess_res.f))
		return (1);
	obj->shininess = shininess_res.f;
	return (0);
}
