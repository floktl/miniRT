/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:17:31 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/19 14:17:32 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static t_ray	get_ray(t_app *app, int x, int y)
{
	return ((t_ray){(t_vec3){0, 0, 0}, (t_vec3){0, 0, 1}});
}

static double	find_closest_intersection(t_ray ray,
		t_scene *scene, t_object **hit_obj)
{
	*hit_obj = NULL;
	return (-1.0);
}

static t_vec3	get_normal(t_vec3 point, t_object *obj)
{
	return ((t_vec3){0, 0, 1});
}

void	render_scene(t_app *app)
{
	int			x;
	int			y;
	uint32_t	color;

	color = 0x0000FFFF;
	y = 0;
	while (y < app->window_height)
	{
		x = 0;
		while (x < app->window_width)
		{
			mlx_put_pixel(app->img, x, y, color);
			x++;
		}
		y++;
	}
}
