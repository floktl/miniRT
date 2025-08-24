/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:00:00 by yourname         #+#    #+#             */
/*   Updated: 2024/10/10 00:00:00 by yourname        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static int	is_not_rt(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 3)
		return (1);
	return (ft_strncmp(file + len - 3, ".rt", 3));
}

int	main(int argc, char **argv)
{
	t_app	app ;
	char	*path;

	path = NULL;
	app = (t_app){0};

	if (argc != 2)
		return (printf("Error\nUsage: ./miniRT <scene.rt>\n"), 1);
	if (is_not_rt(argv[1]))
		return (printf("Error\nFile must have .rt extension\n"), 1);

	path = ft_strdup(argv[1]);
	if (parse_scene(path, &app.scene) != 0)
	{
		free(path);
		free_scene(&app.scene);
		return (printf("Error\nFailed to parse scene file\n"), 1);
	}

	print_scene(&app.scene);
	free(path);
	//if (init_app(&app) != 0)
	//	return (printf("Error\nFailed to initialize application\n"), 1);
	//render_scene(&app);
	//mlx_key_hook(app.mlx, key_hook, &app);
	//mlx_loop(app.mlx);
	//mlx_terminate(app.mlx);
	free_scene(&app.scene);
	return (0);
}
