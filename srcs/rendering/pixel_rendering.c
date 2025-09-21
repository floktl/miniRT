/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/21 12:24:09 by fkeitel          ###   ########.fr       */
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
uint32_t	render_pixel(t_app *app, int x, int y)
{
	t_ray		ray;
	t_object	*hit_obj;
	double		intersection_dist;

	ray = get_ray(app, x, y);
	intersection_dist = find_closest_intersection(ray, &app->scene, &hit_obj);
	if (intersection_dist > 0.0 && hit_obj)
	{
		return (calculate_intersection_color(
				ray,
				intersection_dist,
				hit_obj,
				&app->scene));
	}
	else
		return (calculate_background_color(&app->scene));
}

/*
** Fill entire window with a single color
** Used for clearing buffer or filling with solid color
** @param app: Pointer to application struct
** @param color: 32-bit color value to fill with
*/
void	fill_entire_window(t_app *app, uint32_t color)
{
	int	x;
	int	y;

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

/*
** Fill entire window with calculated pixel colors using ray tracing
** Main rendering function that casts rays through each pixel
** @param app: Pointer to application struct
** @param pixel_calculator: Function pointer to calculate pixel color
*/
void	fill_window_with_raytracing(t_app *app,
		uint32_t (*pixel_calculator)(t_app*, int, int))
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
			pixel_color = pixel_calculator(app, x, y);
			mlx_put_pixel(app->img, x, y, pixel_color);
			x++;
		}
		y++;
	}
}

static void	fill_pixel_block(t_app *app, int x, int y, uint32_t pixel_color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < app->render_scale && y + dy < app->window_height)
	{
		dx = 0;
		while (dx < app->render_scale && x + dx < app->window_width)
		{
			mlx_put_pixel(app->img, x + dx, y + dy, pixel_color);
			dx++;
		}
		dy++;
	}
}

/*
** Fill entire window with calculated pixel colors using low-res ray tracing
** Renders at reduced resolution by sampling every Nth pixel and filling blocks
** @param app: Pointer to application struct
** @param pixel_calculator: Function pointer to calculate pixel color
*/
void	fill_window_with_raytracing_low_res(t_app *app,
		uint32_t (*pixel_calculator)(t_app*, int, int))
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
			pixel_color = pixel_calculator(app, x, y);
			fill_pixel_block(app, x, y, pixel_color);
			x += app->render_scale;
		}
		y += app->render_scale;
	}
}
