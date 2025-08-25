/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:21:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 17:32:30 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_scene(t_scene *scene)
{
	t_object	*obj;
	t_object	*obj_next;
	t_light		*light;
	t_light		*light_next;

	if (!scene)
		return ;
	obj = scene->objects;
	while (obj)
	{
		obj_next = obj->next;
		free(obj);
		obj = obj_next;
	}
	scene->objects = NULL;
	light = scene->lights;
	while (light)
	{
		light_next = light->next;
		free(light);
		light = light_next;
	}
	scene->lights = NULL;
}

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
