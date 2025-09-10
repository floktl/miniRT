/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:44:28 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 15:12:10 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	counter;

	counter = 0;
	while (s[counter])
		counter++;
	while (counter >= 0)
	{
		if (s[counter] == (char)c)
			return ((char *)s + counter);
		counter--;
	}
	return (NULL);
}

/* int	main(void) {
	const char str[] = "bonjour";
	const char ch = 'b';
	char *ret;

	ret = ft_strrchr(str, ch);
	printf("String after %c is - %s\n", ch, ret);
	return 0;
}*/
