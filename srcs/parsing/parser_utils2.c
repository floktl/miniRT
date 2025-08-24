/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:49:30 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/24 13:56:56 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	validate_scene(t_scene *scene)
{
	if (scene->camera.fov == 0 || scene->ambient.ratio == 0)
	{
		printf("Validation failed: FOV=%f, Ambient ratio=%f\n",
			scene->camera.fov, scene->ambient.ratio);
		write(2, "Error: Missing required elements\n", 33);
		return (1);
	}
	return (0);
}

int	process_line(char *line, t_scene *scene, int fd)
{
	printf("Read line: %s\n", line);
	if (line[0] != '#' && line[0] != '\n'
		&& line[0] != 0 && parse_line(line, scene) != 0)
	{
		free(line);
		close(fd);
		return (1);
	}
	free(line);
	return (0);
}

int	dispatch_and_return(t_scene *scene, char **tokens, const char *type,
		int (*parse_func)(char **, t_scene *))
{
	printf("[DISPATCH] -> %s\n", type);
	return (parse_func(tokens, scene));
}
