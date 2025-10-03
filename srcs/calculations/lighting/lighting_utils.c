/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/03 20:17:53 by mezhang          ###   ########.fr       */
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

bool in_shadow(t_light_params *params, t_vec3d light_dir, double dist_to_light)
{
	t_ray shadow_ray;
	t_object *current_obj;
	double intersection_dist;
	
	shadow_ray.origin = vec_add(params->point, vec_mul(params->normal, 1e-4));
	shadow_ray.direction = light_dir;
	current_obj = params->scene->objects;
	while (current_obj)
	{
		intersection_dist = calculate_object_intersection(shadow_ray, current_obj);
		if (intersection_dist > 1e-4 && intersection_dist < dist_to_light)
			return (true);
		current_obj = current_obj->next;
	}
	return (false);
}
	