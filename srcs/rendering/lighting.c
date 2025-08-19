/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:17:48 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/19 14:19:20 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static t_color	lamp_color(t_color c)
{
	return (c);
}

t_color	compute_lighting(t_vec3 point, t_vec3 normal,
		t_scene *scene, t_color obj_color)
{
	return ((t_color){0, 0, 0});
}
