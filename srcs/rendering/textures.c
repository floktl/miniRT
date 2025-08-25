/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:50:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 18:52:33 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

static t_color	checkerboard_texture(t_object *obj, t_vec3 point)
{
	return (obj->color);
}

t_color	apply_texture(t_object *obj, t_vec3 point)
{
	if (obj->texture_type == TEXTURE_CHECKERBOARD)
		return (checkerboard_texture(obj, point));
	return (obj->color);
}

static t_vec3	bump_map_normal(t_object *obj, t_vec3 point, t_vec3 normal)
{
	return (normal);
}

t_vec3	apply_bump_mapping(t_object *obj, t_vec3 point, t_vec3 normal)
{
	if (obj->texture_type == TEXTURE_BUMP_MAP)
		return (bump_map_normal(obj, point, normal));
	return (normal);
}
