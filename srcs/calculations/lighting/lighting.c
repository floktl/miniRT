/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:17:48 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:18:29 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * PHONG LIGHTING MODEL CALCULATIONS
 *
 * The Phong reflection model simulates realistic surface lighting:
 * - Ambient lighting provides constant background illumination
 * - Diffuse lighting follows Lambert's cosine law for matte surfaces
 * - Specular lighting creates shiny highlights using reflection angles
 * - Multiple light sources are combined for final illumination
 *
 * Lighting components:
 * - Ambient: Constant light simulating indirect illumination
 * - Diffuse: Light scattered equally in all directions (Lambert's law)
 * - Specular: Light reflected in mirror-like direction (Phong model)
 * - Final color combines all components from all light sources
 */

static t_color	process_light_contribution(t_light *light,
		t_light_params *params, t_color texture_color)
{
	t_vec3d	light_dir;
	double	diffuse_factor;
	double	specular_factor;
	double	light_intensity;

	light_dir = vec_sub(light->position, params->point);
	light_dir = vec_normalize(light_dir);
	diffuse_factor = calculate_diffuse_factor(params->normal, light_dir);
	specular_factor = calculate_specular_factor(params->view_dir, light_dir,
			params->normal, params->shininess);
	light_intensity = light->brightness * (diffuse_factor + specular_factor);
	return (apply_light_color(texture_color, light, light_intensity));
}

static t_color	process_all_lights(t_light_params *params, t_light *lights,
		t_color obj_color)
{
	t_color	final_color;
	t_light	*current_light;
	t_color	light_contribution;

	final_color.r = 0;
	final_color.g = 0;
	final_color.b = 0;
	current_light = lights;
	while (current_light)
	{
		light_contribution = process_light_contribution(current_light, params,
				obj_color);
		add_light_contribution(&final_color, light_contribution);
		current_light = current_light->next;
	}
	return (final_color);
}

t_color	compute_lighting(t_vec3d point, t_vec3d normal,
		t_scene *scene, t_object *obj)
{
	t_light_params	params;
	t_color			ambient_color;
	t_color			light_color;

	params.point = point;
	params.normal = normal;
	params.view_dir = vec_normalize(vec_sub(scene->camera.position, point));
	params.shininess = obj->shininess;
	ambient_color = calculate_ambient_color(obj, scene);
	light_color = process_all_lights(&params, scene->lights, obj->color);
	ambient_color.r = fmin(255, ambient_color.r + light_color.r);
	ambient_color.g = fmin(255, ambient_color.g + light_color.g);
	ambient_color.b = fmin(255, ambient_color.b + light_color.b);
	return (ambient_color);
}
