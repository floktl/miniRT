/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:24:39 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 15:44:59 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Routes tokens to appropriate parser based on identifier */
static int	dispatch_parse(char **tokens, int token_count, t_scene *scene)
{
	trim_all_tokens(tokens, token_count);
	printf("[DISPATCH] token0='%s' count=%d\n", tokens[0], token_count);
	if (ft_strncmp(tokens[0], "A", 2) == 0 && token_count >= 3)
		return (dispatch_and_return(scene, tokens, "AMBIENT", parse_ambient));
	else if (ft_strncmp(tokens[0], "C", 2) == 0 && token_count >= 4)
		return (dispatch_and_return(scene, tokens, "CAMERA", parse_camera));
	else if (ft_strncmp(tokens[0], "DC", 3) == 0 && token_count >= 4)
		return (dispatch_and_return(scene, tokens, "DEBUG_CAMERA",
				parse_debug_camera));
	else if (ft_strncmp(tokens[0], "L", 2) == 0 && token_count >= 4)
		return (dispatch_and_return(scene, tokens, "LIGHT", parse_light));
	else if (ft_strncmp(tokens[0], "sp", 3) == 0 && token_count >= 4)
		return (dispatch_and_return(scene, tokens, "SPHERE", parse_sphere));
	else if (ft_strncmp(tokens[0], "pl", 3) == 0 && token_count >= 4)
		return (dispatch_and_return(scene, tokens, "PLANE", parse_plane));
	else if (ft_strncmp(tokens[0], "cy", 3) == 0 && token_count >= 6)
		return (dispatch_and_return(scene, tokens, "CYLINDER", parse_cylinder));
	else if (ft_strncmp(tokens[0], "co", 3) == 0 && token_count >= 6)
		return (dispatch_and_return(scene, tokens, "CONE", parse_cone));
	printf("[DISPATCH][ERROR] invalid line '%s' or wrong count (%d)\n",
		tokens[0], token_count);
	return (1);
}

/* Parses a single line from scene file into scene data */
int	parse_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		token_count;
	int		status;

	status = 0;
	replace_tabs_with_spaces(line);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		free_tokens(tokens);
		return (status);
	}
	token_count = count_tokens(tokens);
	status = dispatch_parse(tokens, token_count, scene);
	free_tokens(tokens);
	return (status);
}

/* Validates that scene has required camera and ambient elements */
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

/* Processes a single line from file, handles comments and empty lines */
static int	process_line(char **line, t_scene *scene, int fd)
{
	printf("Read line: %s\n", *line);
	if ((*line)[0] != '#' && (*line)[0] != '\n' && (*line)[0] != 0)
	{
		if (parse_line(*line, scene) != 0)
		{
			free(*line);
			*line = NULL;
			close(fd);
			return (1);
		}
	}
	free(*line);
	*line = NULL;
	return (0);
}

/* Main function to parse entire scene file and populate scene struct */
int	parse_scene(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: Could not open file\n", 27);
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (process_line(&line, scene, fd))
			return (1);
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_scene(scene));
}
