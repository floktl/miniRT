/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_primitives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:07:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 12:54:31 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_sphere(char **tokens, t_scene *scene)
{
	t_object	*obj;

	int token_count = 0;
	while (tokens[token_count]) token_count++;
	int idx = 1;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (1);
	obj->type = SPHERE;

	vec3_result cr = parse_vec3_tokens(tokens, &idx, token_count);
	if (!cr.success) {
		printf("[Sphere] Failed to parse center\n");
		free(obj);
		return (1);
	}
	obj->data.s_sphere.center = cr.v;

	float_result dr = parse_float_tokens(tokens, &idx, token_count);
	if (!dr.success) {
		printf("[Sphere] Failed to parse diameter\n");
		free(obj);
		return (1);
	}
	obj->data.s_sphere.radius = dr.f / 2.0;

	color_result colr = parse_color_tokens(tokens, &idx, token_count);
	if (!colr.success || idx != token_count) {
		printf("[Sphere] Failed to parse color or extra tokens\n");
		free(obj);
		return (1);
	}
	obj->color = colr.c;

	// Check for negative or zero diameter BEFORE adding to scene
	if (dr.f <= 0) {
		printf("[Sphere] Diameter must be positive\n");
		free(obj);
		return (1);
	}
	if (obj->data.s_sphere.radius <= 0) {
		free(obj);
		return (1);
	}

	// Only add to scene after all validation passes
	obj->next = scene->objects;
	scene->objects = obj;
	return (0);
}

int	parse_plane(char **tokens, t_scene *scene)
{
	t_object	*obj;

	int token_count = 0;
	while (tokens[token_count]) token_count++;
	int idx = 1;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (1);
	obj->type = PLANE;

	vec3_result pr = parse_vec3_tokens(tokens, &idx, token_count);
	if (!pr.success) {
		printf("[Plane] Failed to parse point\n");
		free(obj);
		return (1);
	}
	obj->data.s_plane.point = pr.v;

	vec3_result nr = parse_vec3_tokens(tokens, &idx, token_count);
	if (!nr.success) {
		printf("[Plane] Failed to parse normal\n");
		free(obj);
		return (1);
	}
	// Check for zero-length normal vector
	if (is_vec_zero(nr.v)) {
		printf("[Plane] Normal vector cannot be zero-length\n");
		free(obj);
		return (1);
	}
	// Check if normal is normalized
	if (!is_vec_normalized(nr.v)) {
		printf("[Plane] Normal vector must be normalized\n");
		free(obj);
		return (1);
	}
	obj->data.s_plane.normal = vec_normalize(nr.v);

	color_result colr = parse_color_tokens(tokens, &idx, token_count);
	if (!colr.success || idx != token_count) {
		printf("[Plane] Failed to parse color or extra tokens\n");
		free(obj);
		return (1);
	}
	obj->color = colr.c;

	obj->next = scene->objects;
	scene->objects = obj;
	return (0);
}

int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_object	*obj;

	int token_count = 0;
	while (tokens[token_count]) token_count++;
	int idx = 1;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (1);
	obj->type = CYLINDER;

	vec3_result br = parse_vec3_tokens(tokens, &idx, token_count);
	if (!br.success) {
		printf("[Cylinder] Failed to parse base\n");
		free(obj);
		return (1);
	}
	obj->data.s_cylinder.base = br.v;

	vec3_result ar = parse_vec3_tokens(tokens, &idx, token_count);
	if (!ar.success) {
		printf("[Cylinder] Failed to parse axis\n");
		free(obj);
		return (1);
	}
	// Check for zero-length axis vector
	if (is_vec_zero(ar.v)) {
		printf("[Cylinder] Axis vector cannot be zero-length\n");
		free(obj);
		return (1);
	}
	obj->data.s_cylinder.axis = vec_normalize(ar.v);

	float_result dr = parse_float_tokens(tokens, &idx, token_count);
	if (!dr.success) {
		printf("[Cylinder] Failed to parse diameter\n");
		free(obj);
		return (1);
	}
	obj->data.s_cylinder.radius = dr.f / 2.0;

	float_result hr = parse_float_tokens(tokens, &idx, token_count);
	if (!hr.success) {
		printf("[Cylinder] Failed to parse height\n");
		free(obj);
		return (1);
	}
	obj->data.s_cylinder.height = hr.f;

	color_result colr = parse_color_tokens(tokens, &idx, token_count);
	if (!colr.success || idx != token_count) {
		printf("[Cylinder] Failed to parse color or extra tokens\n");
		free(obj);
		return (1);
	}
	obj->color = colr.c;

	// Check for negative or zero dimensions BEFORE adding to scene
	if (dr.f <= 0) {
		printf("[Cylinder] Diameter must be positive\n");
		free(obj);
		return (1);
	}
	if (hr.f <= 0) {
		printf("[Cylinder] Height must be positive\n");
		free(obj);
		return (1);
	}
	if (obj->data.s_cylinder.radius <= 0 || obj->data.s_cylinder.height <= 0) {
		free(obj);
		return (1);
	}

	// Only add to scene after all validation passes
	obj->next = scene->objects;
	scene->objects = obj;
	return (0);
}
