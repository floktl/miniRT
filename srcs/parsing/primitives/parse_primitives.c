/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_primitives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:07:30 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 19:06:22 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	cleanup_object_error(t_object *obj, const char *message)
{
	printf("[Object] %s\n", message);
	free(obj);
	return (1);
}

int	parse_sphere(char **tokens, t_scene *scene);
int	parse_plane(char **tokens, t_scene *scene);
int	parse_cylinder(char **tokens, t_scene *scene);
int	parse_cone(char **tokens, t_scene *scene);
