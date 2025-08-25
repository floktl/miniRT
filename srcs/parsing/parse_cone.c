/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:45:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 09:32:15 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_cone(char **tokens, t_scene *scene)
{
	t_object		*obj;
	int				token_count;
	int				idx;

	if (init_object_and_count(&obj, tokens, &token_count, &idx))
		return (1);
	obj->type = CONE;
	if (parse_cone_center(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cone] Failed to parse center"));
	if (parse_cone_axis(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cone] Failed to parse axis"));
	if (parse_cone_dimensions(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cone] Failed to parse dimensions"));
	if (parse_cone_color(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cone] Failed to parse color"));
	if (parse_object_shininess(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cone] Failed to parse shininess"));
	if (parse_texture_type(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cone] Failed parse texture type"));
	if (parse_texture_scale(obj, tokens, &idx, token_count))
		return (cleanup_object_error(obj, "[Cone] Failed parse texture scale"));
	if (validate_cone_data(obj))
		return (cleanup_object_error(obj, "[Cone] Validation failed"));
	obj->next = scene->objects;
	return (scene->objects = obj, 0);
}
