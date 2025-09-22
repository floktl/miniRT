/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_calculations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 10:22:42 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	calculate_diffuse_factor(t_vec3d normal, t_vec3d light_dir)
{
	double	dot_product;

	dot_product = vec_dot(normal, light_dir);
	return (fmax(0.0, dot_product));
}

double	calculate_specular_factor(t_vec3d view_dir, t_vec3d light_dir,
		t_vec3d normal, double shininess)
{
	t_vec3d	reflect_dir;
	double	dot_product;

	reflect_dir = vec_reflect(vec_mul(light_dir, -1.0), normal);
	dot_product = vec_dot(view_dir, reflect_dir);
	return (pow(fmax(0.0, dot_product), shininess));
}

t_color	apply_light_color(t_color texture_color, t_light *light,
		double light_intensity)
{
	t_color	result;

	result.r = (int)(texture_color.r * light->color.r * light_intensity / 255);
	result.g = (int)(texture_color.g * light->color.g * light_intensity / 255);
	result.b = (int)(texture_color.b * light->color.b * light_intensity / 255);
	result.r = fmin(255, fmax(0, result.r));
	result.g = fmin(255, fmax(0, result.g));
	result.b = fmin(255, fmax(0, result.b));
	return (result);
}
