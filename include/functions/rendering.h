/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/04 11:45:33 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "../structs/app_structs.h"

/* render loop that switches between full & low resolution */
void		render_loop(void *param);

// rendering/core/projection_calculations.c
// @param world_point: 3D point in world coordinates
// @param app: Pointer to application struct
// @return: Normalized screen coordinates [-1,1]
t_vec2d		calculate_normalized_coords(t_vec3d world_point, t_app *app);

// @param normalized: Normalized coordinates [-1,1]
// @param world_point: 3D point in world coordinates
// @param app: Pointer to application struct
// @return: Screen pixel coordinates with depth
t_vec3d		normalized_to_screen_pixels(t_vec2d normalized,
				t_vec3d world_point, t_app *app);

// @param world_point: 3D point in world coordinates
// @param app: Pointer to application struct
// @return: Screen pixel coordinates with depth
t_vec3d		project_world_to_screen(t_vec3d world_point, t_app *app);

// @param screen_x: X pixel coordinate
// @param screen_y: Y pixel coordinate
// @param depth: Distance from camera along view direction
// @param app: Application struct with camera data
// @return: 3D world point
t_vec3d		screen_to_world_point(int screen_x, int screen_y, double depth,
				t_app *app);

// @param app: Pointer to application struct
// @param color: 32-bit color value to fill with
void		fill_entire_window(t_app *app, uint32_t color);

// @param app: Pointer to application struct
// @param pixel_calculator: Function pointer to calculate pixel color
void		fill_window_with_raytracing(t_app *app,
				uint32_t (*pixel_calculator)(t_app*, int, int));

// @param app: Pointer to application struct
// @param pixel_calculator: Function pointer to calculate pixel color
void		fill_window_with_raytracing_low_res(t_app *app,
				uint32_t (*pixel_calculator)(t_app*, int, int));

// rendering/pixel_rendering.c
// @param app: Pointer to application struct
// @param x: X pixel coordinate
// @param y: Y pixel coordinate
// @return: 32-bit color value for the pixel
uint32_t	render_pixel(t_app *app, int x, int y);

// rendering/modes/progressive_render.c
// @param app: Pointer to application struct
void		progressive_re_render_scene(t_app *app);

// rendering/debug/debug_camera_ray.c
// @param app: Pointer to application struct
void		render_debug_camera_ray(t_app *app);

// rendering/debug/debug_drawing.c
// @param app: Pointer to application struct
// @param x: X coordinate
// @param y: Y coordinate
void		draw_red_pixel(t_app *app, int x, int y);
void		draw_thick_red_line(t_app *app, int x, int y);
void		render_light_spheres(t_app *app);

// rendering/debug/debug_utils.c
void		format_vector_string(char *buffer, const char *label, t_vec3d vec);
void		render_debug_text(t_app *app, t_vec3d hit_point);
void		draw_circle_pixel(t_app *app, t_vec3d screen_pos, int x, int y);

#endif
