/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:40:29 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 15:12:10 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	if (ft_strncmp(str, "INF", 3) == 0 || ft_strncmp(str, "inf", 3) == 0)
		return (1);
	if (ft_strncmp(str, "NAN", 3) == 0 || ft_strncmp(str, "nan", 3) == 0)
		return (1);
	return (0);
}

double	parse_exponent(const char *str, int *i, double result);

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
	if (str[i] == 'e' || str[i] == 'E')
		result = parse_exponent(str, &i, result);
	return (result);
}
