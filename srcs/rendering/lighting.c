/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:17:48 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/12 14:03:33 by fkeitel          ###   ########.fr       */
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

/* Processes contribution from a single light source */
static t_color	process_light_contribution(t_light *light,
		t_light_params *params, t_color texture_color)
{
	t_color	result;
	double	diffuse_factor;
	double	specular_factor;
	t_vec3d	light_dir;
	t_vec3d	reflect_dir;
	double	dot_product;

	// Calculate light direction
	light_dir = vec_sub(light->position, params->point);
	light_dir = vec_normalize(light_dir);

	// Calculate diffuse lighting (Lambert's cosine law)
	dot_product = vec_dot(params->normal, light_dir);
	diffuse_factor = fmax(0.0, dot_product);

	// Calculate specular lighting (Phong reflection model)
	reflect_dir = vec_reflect(vec_mul(light_dir, -1.0), params->normal);
	dot_product = vec_dot(params->view_dir, reflect_dir);
	specular_factor = pow(fmax(0.0, dot_product), params->shininess);

	// Combine lighting components
	result.r = (int)(texture_color.r * (0.1 + 0.7 * diffuse_factor + 0.2 * specular_factor));
	result.g = (int)(texture_color.g * (0.1 + 0.7 * diffuse_factor + 0.2 * specular_factor));
	result.b = (int)(texture_color.b * (0.1 + 0.7 * diffuse_factor + 0.2 * specular_factor));

	// Clamp values to valid range
	result.r = fmin(255, fmax(0, result.r));
	result.g = fmin(255, fmax(0, result.g));
	result.b = fmin(255, fmax(0, result.b));

	return (result);
}

/* Computes final lighting for a surface point */
t_color	compute_lighting(t_vec3d point, t_vec3d normal,
		t_scene *scene, t_object *obj)
{
	t_color			final_color;
	t_light_params	params;
	t_light			*current_light;
	t_color			ambient_color;

	// Initialize lighting parameters
	params.point = point;
	params.normal = normal;
	params.view_dir = vec_normalize(vec_sub(scene->camera.position, point));
	params.shininess = obj->shininess;

	// Start with ambient lighting
	ambient_color.r = (int)(obj->color.r * scene->ambient.ratio);
	ambient_color.g = (int)(obj->color.g * scene->ambient.ratio);
	ambient_color.b = (int)(obj->color.b * scene->ambient.ratio);

	final_color = ambient_color;

	// Add contributions from all light sources
	current_light = scene->lights;
	while (current_light)
	{
		final_color = process_light_contribution(current_light, &params, obj->color);
		current_light = current_light->next;
	}

	return (final_color);
}
