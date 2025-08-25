/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:17:48 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 18:53:03 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	process_light_contribution(t_light *light,
		t_light_params *params, t_color texture_color)
{
	return (texture_color);
}

t_color	compute_lighting(t_vec3 point, t_vec3 normal,
		t_scene *scene, t_object *obj)
{
	return (obj->color);
}
