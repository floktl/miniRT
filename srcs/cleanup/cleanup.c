/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:21:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/19 13:22:48 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_scene(t_scene *scene)
{
	t_object	*obj;
	t_object	*tmp;
	t_light		*light;
	t_light		*tmp;

	if (!scene)
		return ;
	obj = scene->objects;
	while (obj)
	{
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
	scene->objects = NULL;
	light = scene->lights;
	while (light)
	{
		tmp = light;
		light = light->next;
		free(tmp);
	}
	scene->lights = NULL;
}
