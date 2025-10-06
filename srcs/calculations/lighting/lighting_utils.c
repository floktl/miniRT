/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/06 11:10:25 by fkeitel          ###   ########.fr       */
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

bool	in_shadow(t_light_params *params, t_vec3d light_dir,
			double dist_to_light)
{
	t_ray		shadow_ray;
	t_object	*cur_obj;
	double		intersection_dist;

	shadow_ray.origin = vec_add(params->point, vec_mul(params->normal, 1e-4));
	shadow_ray.direction = light_dir;
	cur_obj = params->scene->objects;
	while (cur_obj)
	{
		if (!cur_obj->is_light_sphere)
		{
			intersection_dist = calculate_object_intersection(shadow_ray,
					cur_obj);
			if (intersection_dist > 1e-4 && intersection_dist < dist_to_light)
				return (true);
		}
		cur_obj = cur_obj->next;
	}
	return (false);
}
