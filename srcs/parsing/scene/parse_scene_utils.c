/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:43:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/21 12:24:09 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Checks if ambient element already exists in scene */
int	check_ambient_duplicate(t_scene *scene)
{
	if (scene->ambient.ratio != 0.0)
	{
		printf("[Ambient] Duplicate ambient element not allowed\n");
		return (1);
	}
	return (0);
}

/* Validates ambient ratio is within valid range */
int	validate_ambient_ratio(float ratio)
{
	if (ratio < 0 || ratio > 1)
	{
		printf("[Ambient][ERROR] Ratio out of range [0..1]\n");
		return (1);
	}
	return (0);
}
