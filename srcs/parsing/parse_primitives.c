/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_primitives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:07:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/19 14:44:34 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	parse_sphere(char **tokens, t_scene *scene)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (1);
	obj->type = SPHERE;
	obj->data.s_sphere.center = parse_vec3(tokens[1]);
	obj->data.s_sphere.radius = ft_atof(tokens[2]) / 2.0;
	obj->color = parse_color(tokens[3]);
	obj->next = scene->objects;
	scene->objects = obj;
	if (obj->data.s_sphere.radius <= 0)
	{
		free(obj);
		return (1);
	}
	return (0);
}

int	parse_plane(char **tokens, t_scene *scene)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (1);
	obj->type = PLANE;
	obj->data.s_plane.point = parse_vec3(tokens[1]);
	obj->data.s_plane.normal = vec_normalize(parse_vec3(tokens[2]));
	obj->color = parse_color(tokens[3]);
	obj->next = scene->objects;
	scene->objects = obj;
	return (0);
}

int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (1);
	obj->type = CYLINDER;
	obj->data.s_cylinder.base = parse_vec3(tokens[1]);
	obj->data.s_cylinder.axis = vec_normalize(parse_vec3(tokens[2]));
	obj->data.s_cylinder.radius = ft_atof(tokens[3]) / 2.0;
	obj->data.s_cylinder.height = ft_atof(tokens[4]);
	obj->color = parse_color(tokens[5]);
	obj->next = scene->objects;
	scene->objects = obj;
	if (obj->data.s_cylinder.radius <= 0 || obj->data.s_cylinder.height <= 0)
	{
		free(obj);
		return (1);
	}
	return (0);
}
