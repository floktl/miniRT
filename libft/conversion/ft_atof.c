/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:40:29 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/19 12:50:24 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	skip_ws_and_sign(const char *s, int *i, double *sign)
{
	*sign = 1.0;
	while (s[*i] == ' ' || (s[*i] >= '\t' && s[*i] <= '\r'))
		(*i)++;
	if (s[*i] == '-' || s[*i] == '+')
	{
		if (s[*i] == '-')
			*sign = -1.0;
		(*i)++;
	}
}

static double	parse_integer_part(const char *s, int *i)
{
	double	result;

	result = 0.0;
	while (ft_isdigit(s[*i]))
		result = result * 10.0 + (s[(*i)++] - '0');
	return (result);
}

static void	parse_fraction_part(const char *s, int *i, double *result)
{
	double	fraction;

	if (s[*i] != '.')
		return ;
	(*i)++;
	fraction = 0.1;
	while (ft_isdigit(s[*i]))
	{
		*result += (s[(*i)++] - '0') * fraction;
		fraction *= 0.1;
	}
}

double	ft_atof(const char *str)
{
	int		i;
	double	sign;
	double	result;

	i = 0;
	result = 0.0;
	skip_ws_and_sign(str, &i, &sign);
	result = parse_integer_part(str, &i);
	parse_fraction_part(str, &i, &result);
	return (result * sign);
}
