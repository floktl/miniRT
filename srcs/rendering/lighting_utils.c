/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:17:48 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 18:54:17 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_color	scale_color(t_color color, double factor)
{
	return (color);
}

t_color	add_colors(t_color a, t_color b)
{
	return (a);
}

double	compute_diffuse(t_vec3 light_dir, t_vec3 normal)
{
	return (0);
}

double	compute_specular(t_vec3 light_dir, t_vec3 normal,
		t_vec3 view_dir, double shininess)
{
	return (0);
}
