/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two_dimensional_array.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:57:41 by flo               #+#    #+#             */
/*   Updated: 2025/08/25 15:12:10 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	function to free an two dimensional array of chars
void	free_two_dimensional_array(char **param)
{
	int	count;

	count = 0;
	if (!param)
		return ;
	while (param[count])
	{
		free(param[count]);
		param[count] = NULL;
		count++;
	}
	free(param);
	param = NULL;
}
