/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:40:29 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 11:07:06 by Florian Kei      ###   ########.fr       */
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

static int	is_invalid_value(const char *str)
{
	// Check for INF, NaN, or other invalid values
	if (ft_strncmp(str, "INF", 3) == 0 || ft_strncmp(str, "inf", 3) == 0)
		return (1);
	if (ft_strncmp(str, "NAN", 3) == 0 || ft_strncmp(str, "nan", 3) == 0)
		return (1);
	return (0);
}

double	ft_atof(const char *str)
{
	int		i;
	double	sign;
	double	result;

	if (!str || is_invalid_value(str))
		return (0.0);

	i = 0;
	result = 0.0;
	skip_ws_and_sign(str, &i, &sign);
	result = parse_integer_part(str, &i);
	parse_fraction_part(str, &i, &result);
	result = result * sign;

	// Apply scientific notation if present
	if (str[i] == 'e' || str[i] == 'E')
	{
		double	exponent;
		double	exp_sign;

		i++; // Skip 'e' or 'E'

		// Parse exponent sign
		exp_sign = 1.0;
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				exp_sign = -1.0;
			i++;
		}

		// Parse exponent value
		exponent = 0.0;
		while (ft_isdigit(str[i]))
			exponent = exponent * 10.0 + (str[i++] - '0');

		// Apply the exponent
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
	}

	return (result);
}
