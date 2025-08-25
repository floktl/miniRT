/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 10:38:30 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	apply_exponent(double result, double exponent, double exp_sign)
{
	if (exp_sign > 0)
	{
		while (exponent > 0)
		{
			result *= 10.0;
			exponent--;
		}
	}
	else
	{
		while (exponent > 0)
		{
			result /= 10.0;
			exponent--;
		}
	}
	return (result);
}

double	parse_exponent(const char *str, int *i, double result)
{
	double	exponent;
	double	exp_sign;

	(*i)++;
	exp_sign = 1.0;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			exp_sign = -1.0;
		(*i)++;
	}
	exponent = 0.0;
	while (ft_isdigit(str[*i]))
		exponent = exponent * 10.0 + (str[(*i)++] - '0');
	return (apply_exponent(result, exponent, exp_sign));
}
