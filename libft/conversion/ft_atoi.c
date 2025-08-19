/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:00:23 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/19 15:46:20 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	size_t	i;

	result = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit((unsigned char)str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}


/*int main() {
    char str[] = "12345"; // Replace this with the string you want to convert
    int number = ft_atoi(str);

    printf("String: %s\n", str);
    printf("Converted to Integer: %d\n", number);

    return 0;
}*/
