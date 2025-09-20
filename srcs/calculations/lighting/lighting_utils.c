/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:18:31 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	calculate_ambient_color(t_object *obj, t_scene *scene)
{
	t_color	ambient_color;

	ambient_color.r = (int)(obj->color.r * scene->ambient.ratio);
	ambient_color.g = (int)(obj->color.g * scene->ambient.ratio);
	ambient_color.b = (int)(obj->color.b * scene->ambient.ratio);
	return (ambient_color);
}

void	add_light_contribution(t_color *final_color, t_color contribution)
{
	final_color->r = fmin(255, final_color->r + contribution.r);
	final_color->g = fmin(255, final_color->g + contribution.g);
	final_color->b = fmin(255, final_color->b + contribution.b);
}
