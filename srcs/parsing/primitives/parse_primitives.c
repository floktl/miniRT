/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_primitives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:07:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/06 11:42:47 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Cleans up object memory and returns error on parsing failure */
int	cleanup_object_error(t_object *obj, const char *message)
{
	printf("[Object] %s\n", message);
	if (obj)
		free(obj);
	return (1);
}

int	parse_sphere(char **tokens, t_scene *scene);
int	parse_plane(char **tokens, t_scene *scene);
int	parse_cylinder(char **tokens, t_scene *scene);
int	parse_cone(char **tokens, t_scene *scene);
