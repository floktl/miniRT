/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 19:06:24 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_plane(char **tokens, t_scene *scene)
{
	t_object	*obj;
	int			token_count;
	int			idx;

	if (init_object_and_count(&obj, tokens, &token_count, &idx))
		return (1);
	obj->type = PLANE;
	if (parse_plane_point(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Plane] Failed to parse point"));
	if (parse_plane_normal(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Plane] Failed to parse normal"));
	if (parse_plane_color(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Plane] Failed to parse color"));
	if (parse_object_shininess(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Plane] Failed parse shininess"));
	if (parse_texture_type(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Plane] Failed parse txt type"));
	if (parse_texture_scale(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Plane] Failed parse txt scale"));
	obj->next = scene->objects;
	scene->objects = obj;
	return (0);
}
