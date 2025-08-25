/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:50:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 14:31:54 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

/*
 * TEXTURE MAPPING AND BUMP MAPPING CALCULATIONS
 *
 * Texture mapping applies surface patterns and detail to objects:
 * - Checkerboard textures create alternating color patterns
 * - Texture coordinates map 3D surface points to 2D texture space
 * - Surface derivatives determine texture sampling locations
 * - Bump mapping perturbs surface normals for detail without geometry
 *
 * Mathematical concepts:
 * - UV coordinates: 2D texture space mapping from 3D surfaces
 * - Surface derivatives: How texture coordinates change across surface
 * - Normal perturbation: Modifying surface normals for lighting detail
 * - Texture sampling: Extracting color values from texture patterns
 */

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
