/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_camera_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/03 09:50:23 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Debug-specific world to screen projection
 * Projects 3D world points to 2D screen coordinates using main camera
 * @param world_point: 3D point in world coordinates
 * @param app: Application struct with camera data
 * @return: Screen coordinates with depth information
 */
static t_vec3d	project_debug_world_to_screen(t_vec3d world_point, t_app *app)
{
	t_vec2d	normalized;
	t_vec3d	screen_pos;

	// Use the same projection logic as the main rendering system
	normalized = calculate_normalized_coords(world_point, app);
	screen_pos = normalized_to_screen_pixels(normalized, world_point, app);
	return (screen_pos);
}

/*
 * Calculate color based on 3D position in space
 * Uses position coordinates to create a colorful gradient
 * @param position: 3D world position
 * @return: 32-bit color value (RGBA)
 */
static uint32_t	get_position_color(t_vec3d position)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (int)(fabs(position.x) * 50) % 256;
	green = (int)(fabs(position.y) * 50) % 256;
	blue = (int)(fabs(position.z) * 50) % 256;
	alpha = 255;
	if (red < 50)
		red = 50;
	if (green < 50)
		green = 50;
	if (blue < 50)
		blue = 50;
	return ((uint32_t)((red << 24) | (green << 16) | (blue << 8) | alpha));
}

/*
 * Draw a pixel with specified color
 * @param app: Pointer to application struct
 * @param x: X coordinate
 * @param y: Y coordinate
 * @param color: 32-bit color value
 */
static void	draw_colored_pixel(t_app *app, int x, int y, uint32_t color)
{
	if (x >= 0 && x < app->window.width
		&& y >= 0 && y < app->window.height)
	{
		mlx_put_pixel(app->window.img, x, y, color);
	}
}

/*
 * Draw a thick line with specified color
 * @param app: Pointer to application struct
 * @param x: X coordinate
 * @param y: Y coordinate
 * @param color: 32-bit color value
 */
static void	draw_thick_colored_line(t_app *app, int x, int y, uint32_t color)
{
	draw_colored_pixel(app, x, y, color);
	draw_colored_pixel(app, x + 1, y, color);
	draw_colored_pixel(app, x - 1, y, color);
	draw_colored_pixel(app, x, y + 1, color);
	draw_colored_pixel(app, x, y - 1, color);
	draw_colored_pixel(app, x + 2, y, color);
	draw_colored_pixel(app, x - 2, y, color);
	draw_colored_pixel(app, x, y + 2, color);
	draw_colored_pixel(app, x, y - 2, color);
	draw_colored_pixel(app, x + 1, y + 1, color);
	draw_colored_pixel(app, x - 1, y - 1, color);
	draw_colored_pixel(app, x + 1, y - 1, color);
	draw_colored_pixel(app, x - 1, y + 1, color);
}

static void	draw_debug_camera_sphere(t_app *app, t_vec3d world_pos, int base_radius)
{
	t_vec3d	screen_pos;
	t_vec3d	relative;
	double	distance;
	int		radius;
	int		x;
	int		y;

	screen_pos = project_debug_world_to_screen(world_pos, app);
	if (screen_pos.z <= 0)
		return ;
	relative = vec_sub(world_pos, app->scene.camera.position);
	distance = sqrt(vec_dot(relative, relative));
	radius = (int)(base_radius * 10.0 / distance);
	if (radius < 1)
		radius = 1;
	if (radius > 20)
		radius = 20;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				draw_circle_pixel(app, screen_pos, x, y);
			x++;
		}
		y++;
	}
}

static void	draw_ray_line(t_app *app, t_ray debug_ray, double max_distance)
{
	t_vec3d		ray_point;
	t_vec3d		screen_pos;
	//t_vec3d		relative_to_cam;
	uint32_t	position_color;
	double		t;

	t = 0.0;
	printf("[RAY DEBUG] Drawing ray from (%.3f,%.3f,%.3f) dir (%.3f,%.3f,%.3f) max_dist=%.3f\n",
		debug_ray.origin.x, debug_ray.origin.y, debug_ray.origin.z,
		debug_ray.direction.x, debug_ray.direction.y, debug_ray.direction.z, max_distance);

	while (t <= max_distance)
	{
		ray_point = vec_add(debug_ray.origin,
				vec_mul(debug_ray.direction, -t));
		screen_pos = project_debug_world_to_screen(ray_point, app);

		// Print key points for debugging
		printf("[RAY DEBUG] t=%.2f world=(%.3f,%.3f,%.3f) screen=(%.1f,%.1f) depth=%.3f\n",
			t, ray_point.x, ray_point.y, ray_point.z,
			screen_pos.x, screen_pos.y, screen_pos.z);

		if (screen_pos.z > 0)
		{
			if ((int)screen_pos.x >= 0
				&& (int)screen_pos.x < app->window.width
				&& (int)screen_pos.y >= 0
				&& (int)screen_pos.y < app->window.height)
			{
				position_color = get_position_color(ray_point);
				draw_thick_colored_line(app, (int)screen_pos.x,
					(int)screen_pos.y, position_color);
			}
			else
				printf("[RAY DEBUG] Point off-screen: screen=(%.1f,%.1f) depth=%.3f\n",
					screen_pos.x, screen_pos.y, screen_pos.z);
		}
		t += 0.1;
	}
}

static t_ray	get_debug_camera_ray(t_app *app)
{
	t_ray	ray;
	t_vec3d	right;
	t_vec3d	up;
	t_vec3d	forward;

	forward = app->scene.debug_camera.direction;
	up = app->scene.debug_camera.up;
	right = vec_cross(forward, up);
	right = vec_normalize(right);
	up = vec_normalize(up);
	ray.origin = app->scene.debug_camera.position;
	ray.direction = vec_normalize(forward);
	printf("Generated ray - Origin: (%.6f, %.6f, %.6f) Direction: (%.6f, %.6f, %.6f)\n",
		ray.origin.x, ray.origin.y, ray.origin.z,
		ray.direction.x, ray.direction.y, ray.direction.z);
	return (ray);
}

void	render_debug_camera_ray(t_app *app)
{
	t_ray		debug_ray;
	t_object	*hit_obj;
	double		intersection_dist;

	if (!app->scene.has_debug_camera)
		return ;
	debug_ray = get_debug_camera_ray(app);
	printf("Generated ray - Origin: (%.6f, %.6f, %.6f) Direction: (%.6f, %.6f, %.6f)\n",
		debug_ray.origin.x, debug_ray.origin.y, debug_ray.origin.z,
		debug_ray.direction.x, debug_ray.direction.y, debug_ray.direction.z);
	printf("Main Camera - Pos: (%.6f, %.6f, %.6f) Dir: (%.6f, %.6f, %.6f)\n",
		app->scene.camera.position.x, app->scene.camera.position.y, app->scene.camera.position.z,
		app->scene.camera.direction.x, app->scene.camera.direction.y, app->scene.camera.direction.z);
	printf("=== DEBUG CAMERA SHOULD BE INDEPENDENT ===\n");
		intersection_dist = find_closest_intersection_debug(debug_ray, &app->scene,
			&hit_obj);
			if (intersection_dist > 0.0 && hit_obj)
			draw_ray_line(app, debug_ray, intersection_dist);
			else
			draw_ray_line(app, debug_ray, 10.0);
		draw_debug_camera_sphere(app, app->scene.debug_camera.position, 6);
	printf("Debug Camera - Pos: (%.6f, %.6f, %.6f) Dir: (%.6f, %.6f, %.6f) Up: (%.6f, %.6f, %.6f)\n",
		app->scene.debug_camera.position.x,
		app->scene.debug_camera.position.y,
		app->scene.debug_camera.position.z,
		app->scene.debug_camera.direction.x,
		app->scene.debug_camera.direction.y,
		app->scene.debug_camera.direction.z,
		app->scene.debug_camera.up.x,
		app->scene.debug_camera.up.y,
		app->scene.debug_camera.up.z);
	printf("=== DEBUG CAMERA DIRECTION SHOULD BE (0,0,1) ===\n");
}
