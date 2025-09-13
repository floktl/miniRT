/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:17:31 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/12 14:06:45 by fkeitel          ###   ########.fr       */
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

/* Generates ray from camera through pixel coordinates */
static t_ray	get_ray(t_app *app, int x, int y)
{
	t_ray		ray;
	t_vec3d		pixel_world;	// 3D world coordinates for pixel
	double		aspect_ratio;	// Screen width/height ratio
	double		fov_scale;

	// Calculate aspect ratio and field of view scaling
	aspect_ratio = (double)app->window_width / (double)app->window_height;
	fov_scale = tan(app->scene.camera.fov * M_PI / 360.0);

	// Convert pixel coordinates to normalized device coordinates (-1 to 1)
	pixel_world.x = (2.0 * (x + 0.5) / app->window_width - 1.0) * aspect_ratio * fov_scale;
	pixel_world.y = (1.0 - 2.0 * (y + 0.5) / app->window_height) * fov_scale;
	pixel_world.z = 1.0;

	// Set ray origin to camera position
	ray.origin = app->scene.camera.position;

	// Calculate ray direction (camera direction + pixel offset)
	ray.direction = vec_add(app->scene.camera.direction, pixel_world);
	ray.direction = vec_normalize(ray.direction);

	return (ray);
}

/* Finds closest object intersection along ray path */
static double	find_closest_intersection(t_ray ray,
		t_scene *scene, t_object **hit_obj)
{
	t_object	*current;
	double		closest_dist;
	double		current_dist;

	*hit_obj = NULL;
	closest_dist = -1.0;
	current = scene->objects;

	// Test intersection with all objects in scene
	while (current)
	{
		current_dist = -1.0;

		// Call appropriate intersection function based on object type
		if (current->type == SPHERE)
			current_dist = intersect_sphere(ray, current);
		else if (current->type == PLANE)
			current_dist = intersect_plane(ray, current);
		else if (current->type == CYLINDER)
			current_dist = intersect_cylinder(ray, current);
		else if (current->type == CONE)
			current_dist = intersect_cone(ray, current);

		// Update closest intersection if this one is closer
		if (current_dist > 0.0 && (closest_dist < 0.0 || current_dist < closest_dist))
		{
			closest_dist = current_dist;
			*hit_obj = current;
		}

		current = current->next;
	}

	return (closest_dist);
}

/* Calculates surface normal at intersection point */
static t_vec3d	get_normal(t_vec3d point, t_object *obj)
{
	t_vec3d	normal;

	// Calculate normal based on object type
	if (obj->type == SPHERE)
	{
		// For sphere: normal points from center to intersection point
		normal = vec_sub(point, obj->data.s_sphere.center);
		normal = vec_normalize(normal);
	}
	else if (obj->type == PLANE)
	{
		// For plane: normal is constant (stored in object data)
		normal = obj->data.s_plane.normal;
	}
	else if (obj->type == CYLINDER)
	{
		// For cylinder: calculate normal based on position relative to axis
		t_vec3d	to_point;
		t_vec3d	projection;
		double	projection_length;

		to_point = vec_sub(point, obj->data.s_cylinder.base);
		projection_length = vec_dot(to_point, obj->data.s_cylinder.axis);
		projection = vec_mul(obj->data.s_cylinder.axis, projection_length);
		normal = vec_sub(to_point, projection);
		normal = vec_normalize(normal);
	}
	else if (obj->type == CONE)
	{
		// For cone: calculate normal based on cone geometry
		t_vec3d	to_point;
		t_vec3d	projection;
		double	projection_length;

		to_point = vec_sub(point, obj->data.s_cone.center);
		projection_length = vec_dot(to_point, obj->data.s_cone.axis);
		projection = vec_mul(obj->data.s_cone.axis, projection_length);
		normal = vec_sub(to_point, projection);
		normal = vec_normalize(normal);
	}
	else
	{
		// Default fallback
		normal = (t_vec3d){0, 0, 1};
	}

	return (normal);
}

/* Main ray tracing rendering function */
void	render_scene(t_app *app)
{
	int			x;
	int			y;
	t_ray		ray;
	t_object	*hit_obj;
	double		intersection_dist;
	t_vec3d		intersection_point;
	t_vec3d		normal;
	t_color		final_color;
	uint32_t	pixel_color;

	y = 0;
	while (y < app->window_height)
	{
		x = 0;
		while (x < app->window_width)
		{
			// Step 1: Generate ray from camera through pixel
			ray = get_ray(app, x, y);

			// Step 2: Find closest intersection
			intersection_dist = find_closest_intersection(ray, &app->scene, &hit_obj);

			if (intersection_dist > 0.0 && hit_obj)
			{
				// Step 3: Calculate intersection point
				intersection_point = vec_add(ray.origin,
					vec_mul(ray.direction, intersection_dist));

				// Step 4: Calculate surface normal
				normal = get_normal(intersection_point, hit_obj);

				// Step 5: Calculate lighting and final color
				final_color = compute_lighting(intersection_point, normal,
					&app->scene, hit_obj);

				// Convert color to pixel format
				pixel_color = (final_color.r << 16) | (final_color.g << 8) | final_color.b;
			}
			else
			{
				// No intersection - use background color (ambient)
				pixel_color = (app->scene.ambient.color.r << 16)
					| (app->scene.ambient.color.g << 8)
					| app->scene.ambient.color.b;
			}

			// Draw pixel
			mlx_put_pixel(app->img, x, y, pixel_color);
			x++;
		}
		y++;
	}
}
