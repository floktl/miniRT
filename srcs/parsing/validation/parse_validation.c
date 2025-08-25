/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:38:22 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 13:40:24 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

int	is_integer_string(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	if (!*str || !(*str >= '0' && *str <= '9'))
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
