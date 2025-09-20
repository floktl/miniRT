/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:17:31 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:28:46 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * RAY TRACING RENDERING ENGINE
 *
 * Ray tracing is a rendering technique that simulates light transport:
 * - Rays are cast from the camera through each pixel into the scene
 * - Intersection testing determines which objects are hit by each ray
 * - Surface normals are calculated at intersection points
 * - Lighting models compute the final color at each point
 *
 * The ray tracing algorithm simulates how light travels:
 * 1. Cast rays from camera through image plane pixels
 * 2. Find closest object intersections along ray paths
 * 3. Calculate surface properties and lighting at hit points
 * 4. Apply material properties and texture mapping
 * 5. Determine final pixel color from lighting calculations
 */

void	render_scene(t_app *app)
{
	int			x;
	int			y;
	uint32_t	pixel_color;

	y = 0;
	while (y < app->window_height)
	{
		x = 0;
		while (x < app->window_width)
		{
			pixel_color = render_pixel(app, x, y);
			mlx_put_pixel(app->img, x, y, pixel_color);
			x++;
		}
		y++;
	}
}
