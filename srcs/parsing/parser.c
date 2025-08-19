/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:24:39 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/19 14:12:39 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <fcntl.h>
#include <unistd.h> // for write
#include <stdio.h>	// Add this for printf

static int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

static int	dispatch_parse(char **tokens, int token_count, t_scene *scene)
{
	if (ft_strncmp(tokens[0], "A", 2) == 0 && token_count == 3)
		return (parse_ambient(tokens, scene));
	else if (ft_strncmp(tokens[0], "C", 2) == 0 && token_count == 4)
		return (parse_camera(tokens, scene));
	else if (ft_strncmp(tokens[0], "L", 2) == 0 && token_count == 4)
		return (parse_light(tokens, scene));
	else if (ft_strncmp(tokens[0], "sp", 3) == 0 && token_count == 4)
		return (parse_sphere(tokens, scene));
	else if (ft_strncmp(tokens[0], "pl", 3) == 0 && token_count == 4)
		return (parse_plane(tokens, scene));
	else if (ft_strncmp(tokens[0], "cy", 3) == 0 && token_count == 6)
		return (parse_cylinder(tokens, scene));
	else
		return (1);
}

int	parse_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		token_count;
	int		status;

	status = 0;
	printf("Parsing line: %s\n", line);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		free_tokens(tokens);
		return (status);
	}
	token_count = count_tokens(tokens);
	printf("Token count: %d, First token: %s\n", token_count, tokens[0]);
	status = dispatch_parse(tokens, token_count, scene);
	free_tokens(tokens);
	return (status);
}

static int	validate_scene(t_scene *scene)
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

int	parse_scene(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error: Could not open file\n", 27));
	line = get_next_line(fd);
	while (line)
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
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_scene(scene));
}
