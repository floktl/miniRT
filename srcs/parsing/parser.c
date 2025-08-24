/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:24:39 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 12:35:58 by Florian Kei      ###   ########.fr       */
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

static void	trim_token(char *s)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n'
		|| s[len - 1] == '\r' || s[len - 1] == ' '))
	{
		s[len - 1] = '\0';
		len--;
	}
}

static int	dispatch_parse(char **tokens, int token_count, t_scene *scene)
{
	trim_token(tokens[0]);
	if (token_count > 1)
		trim_token(tokens[1]);
	if (token_count > 2)
		trim_token(tokens[2]);
	if (token_count > 3)
		trim_token(tokens[3]);
	if (token_count > 4)
		trim_token(tokens[4]);
	if (token_count > 5)
		trim_token(tokens[5]);

	printf("[DISPATCH] token0='%s' count=%d\n", tokens[0], token_count);

	if (ft_strncmp(tokens[0], "A", 2) == 0 && token_count >= 3)
	{
		printf("[DISPATCH] -> AMBIENT\n");
		return (parse_ambient(tokens, scene));
	}
	else if (ft_strncmp(tokens[0], "C", 2) == 0 && token_count >= 4)
	{
		printf("[DISPATCH] -> CAMERA\n");
		return (parse_camera(tokens, scene));
	}
	else if (ft_strncmp(tokens[0], "L", 2) == 0 && token_count >= 4)
	{
		printf("[DISPATCH] -> LIGHT\n");
		return (parse_light(tokens, scene));
	}
	else if (ft_strncmp(tokens[0], "sp", 3) == 0 && token_count >= 4)
	{
		printf("[DISPATCH] -> SPHERE\n");
		return (parse_sphere(tokens, scene));
	}
	else if (ft_strncmp(tokens[0], "pl", 3) == 0 && token_count >= 4)
	{
		printf("[DISPATCH] -> PLANE\n");
		return (parse_plane(tokens, scene));
	}
	else if (ft_strncmp(tokens[0], "cy", 3) == 0 && token_count >= 6)
	{
		printf("[DISPATCH] -> CYLINDER\n");
		return (parse_cylinder(tokens, scene));
	}
	printf("[DISPATCH][ERROR] Unknown/invalid line start '%s' or wrong arg count (%d)\n",
		tokens[0], token_count);
	return (1);
}


int	parse_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		token_count;
	int		status;

	status = 0;
	printf("Parsing line: %s\n", line);

	int i = 0;
	while (line[i]) {
		if (line[i] == '\t') {
			line[i] = ' ';
		}
		i++;
	}

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
	{
		write(2, "Error: Could not open file\n", 27);
		return (1);
	}
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
