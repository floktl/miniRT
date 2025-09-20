/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:32:32 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:28:46 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "parsing.h"
# include "structs.h"

// Default window settings
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

// Function prototypes with parameter explanations

// init.c
// @param app: Pointer to application struct to initialize
int			init_app(t_app *app);

// @param app: Pointer to application struct
void		init_camera_variables(t_app *app);

// @param app: Pointer to application struct
void		init_mouse_variables(t_app *app);

// @param app: Pointer to application struct
void		init_zoom_variables(t_app *app);

// @param app: Pointer to application struct
void		init_performance_variables(t_app *app);

// rendering/render.c
// @param app: Pointer to application struct containing scene and mlx data
void		render_scene(t_app *app);

// @param app: Pointer to application struct
// @param x: X pixel coordinate
// @param y: Y pixel coordinate
// @return: Ray from camera through pixel
t_ray		get_ray(t_app *app, int x, int y);

// rendering/optimized_render.c
// @param app: Pointer to application struct
void		optimized_re_render_scene(t_app *app);

// @param app: Pointer to application struct
void		mark_scene_dirty(t_app *app);

// @param app: Pointer to application struct
void		force_re_render_scene(t_app *app);

// rendering/progressive_render.c
// @param app: Pointer to application struct
void		progressive_re_render_scene(t_app *app);

// @param app: Pointer to application struct
// @param active: True to enable interaction mode, false to disable

// calculations/intersections/intersections.c
// @param ray: Ray to test for intersection
// @param s_sphere: Sphere object to test against
// @return: Distance to intersection point, -1 if no intersection
double		intersect_sphere(t_ray ray, t_object *s_sphere);

// @param ray: Ray to test for intersection
// @param s_plane: Plane object to test against
// @return: Distance to intersection point, -1 if no intersection
double		intersect_plane(t_ray ray, t_object *s_plane);

// @param ray: Ray to test for intersection
// @param s_cylinder: Cylinder object to test against
// @return: Distance to intersection point, -1 if no intersection
double		intersect_cylinder(t_ray ray, t_object *s_cylinder);

// @param ray: Ray to test for intersection
// @param s_cone: Cone object to test against
// @return: Distance to intersection point, -1 if no intersection
double		intersect_cone(t_ray ray, t_object *s_cone);

// rendering/intersection_utils.c
// @param ray: Ray to test for intersection
// @param scene: Scene containing all objects
// @param hit_obj: Pointer to store the hit object
// @return: Distance to closest intersection, -1 if no intersection
double		find_closest_intersection(t_ray ray, t_scene *scene, t_object **hit_obj);

// @param point: Point on object surface
// @param obj: Object to calculate normal for
// @return: Surface normal vector at the point
t_vec3d		get_normal(t_vec3d point, t_object *obj);

// rendering/ray_generation.c
// @param app: Application struct containing camera and window data
// @param x: X coordinate of pixel
// @param y: Y coordinate of pixel
// @return: Ray from camera through pixel
t_ray		get_ray(t_app *app, int x, int y);

// rendering/pixel_rendering.c
// @param app: Application struct
// @param x: X coordinate of pixel
// @param y: Y coordinate of pixel
// @return: Final pixel color as 32-bit integer
uint32_t	render_pixel(t_app *app, int x, int y);

// calculations/lighting/lighting.c
// @param point: Point on surface to calculate lighting for
// @param normal: Surface normal at the point
// @param scene: Scene containing lights and ambient lighting
// @param obj: Object being lit (for material properties)
// @return: Final color with lighting applied
t_color		compute_lighting(t_vec3d point, t_vec3d normal,
				t_scene *scene, t_object *obj);

// calculations/lighting/lighting_calculations.c
// @param normal: Surface normal vector
// @param light_dir: Direction vector from point to light source
// @return: Diffuse lighting factor (0.0 to 1.0)
double		calculate_diffuse_factor(t_vec3d normal, t_vec3d light_dir);

// @param view_dir: Direction vector from point to camera
// @param light_dir: Direction vector from point to light source
// @param normal: Surface normal vector
// @param shininess: Material shininess factor
// @return: Specular lighting factor (0.0 to 1.0)
double		calculate_specular_factor(t_vec3d view_dir, t_vec3d light_dir,
				t_vec3d normal, double shininess);

// @param texture_color: Base color of the surface
// @param light: Light source
// @param light_intensity: Calculated light intensity
// @return: Color with light applied
t_color		apply_light_color(t_color texture_color, t_light *light,
				double light_intensity);

// calculations/lighting/lighting_utils.c
// @param obj: Object to calculate ambient color for
// @param scene: Scene containing ambient lighting
// @return: Ambient color contribution
t_color		calculate_ambient_color(t_object *obj, t_scene *scene);

// @param final_color: Color to add contribution to
// @param contribution: Light contribution to add
void		add_light_contribution(t_color *final_color, t_color contribution);

// rendering/lighting_utils.c
// @param color: Color to scale
// @param factor: Scaling factor (0.0 to 1.0)
// @return: Scaled color
t_color		scale_color(t_color color, double factor);

// @param a: First color to add
// @param b: Second color to add
// @return: Sum of the two colors (clamped to 255)
t_color		add_colors(t_color a, t_color b);

// @param light_dir: Direction vector from point to light source
// @param normal: Surface normal vector
// @return: Diffuse lighting factor (0.0 to 1.0)
double		compute_diffuse(t_vec3d light_dir, t_vec3d normal);

// @param light_dir: Direction vector from point to light source
// @param normal: Surface normal vector
// @param view_dir: Direction vector from point to camera
// @param shininess: Material shininess factor
// @return: Specular lighting factor (0.0 to 1.0)
double		compute_specular(t_vec3d light_dir, t_vec3d normal,
				t_vec3d view_dir, double shininess);

// rendering/textures.c
// @param obj: Object to apply texture to
// @param point: Point on object surface
// @return: Texture color at the given point
t_color		apply_texture(t_object *obj, t_vec3d point);

// @param obj: Object to apply bump mapping to
// @param point: Point on object surface
// @param normal: Original surface normal
// @return: Modified normal vector with bump mapping applied
t_vec3d		apply_bump_mapping(t_object *obj, t_vec3d point, t_vec3d normal);


t_vec3d		vec_add(t_vec3d a, t_vec3d b);


t_vec3d		vec_sub(t_vec3d a, t_vec3d b);


t_vec3d		vec_mul(t_vec3d a, double scalar);


double		vec_dot(t_vec3d a, t_vec3d b);


double		vec_length(t_vec3d v);


t_vec3d		vec_normalize(t_vec3d v);


t_vec3d		vec_cross(t_vec3d a, t_vec3d b);


t_vec3d		vec_reflect(t_vec3d incident, t_vec3d normal);

// user_input/key_movement.c
// @param app: Pointer to application struct
// @param keydata: Key event data from MLX42
void		handle_forward_back_keys(t_app *app, mlx_key_data_t keydata);
void		handle_left_right_keys(t_app *app, mlx_key_data_t keydata);
void		handle_up_down_keys(t_app *app, mlx_key_data_t keydata);
void		handle_movement_keys(t_app *app, mlx_key_data_t keydata);

// user_input/keys.c
// @param keydata: Key event data from MLX42
// @param param: User parameter (typically app pointer)
void		key_hook(mlx_key_data_t keydata, void *param);

// calculations/camera_movement/camera_forward_back.c
// @param app: Pointer to application struct
void		move_camera_forward(t_app *app);
void		move_camera_backward(t_app *app);

// calculations/camera_movement/camera_left_right.c
// @param app: Pointer to application struct
void		move_camera_left(t_app *app);
void		move_camera_right(t_app *app);

// calculations/camera_movement/camera_up_down.c
// @param app: Pointer to application struct
void		move_camera_up(t_app *app);
void		move_camera_down(t_app *app);

// calculations/camera_movement/camera_pan.c
// @param app: Pointer to application struct
// @param x_offset: X-axis movement offset
// @param y_offset: Y-axis movement offset
void		move_camera_pan(t_app *app, double x_offset, double y_offset);
void		re_render_scene(t_app *app);

// calculations/camera_movement/camera_rotation.c
// @param app: Pointer to application struct
// @param angle: Rotation angle in radians
void		rotate_camera_horizontal(t_app *app, double angle);
void		rotate_camera_vertical(t_app *app, double angle);
void		rotate_camera_roll(t_app *app, double angle);

// user_input/mouse_buttons.c
// @param app: Pointer to application struct
void		handle_left_mouse_press(t_app *app);
void		handle_left_mouse_release(t_app *app);
void		handle_right_mouse_press(t_app *app);
void		handle_right_mouse_release(t_app *app);

// @param button: Mouse button that was pressed/released
// @param action: Action (press/release)
// @param mods: Modifier keys
// @param param: User parameter (typically app pointer)
void		mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param);

// user_input/mouse_movement.c
// @param app: Pointer to application struct
// @param yaw_angle: Horizontal rotation angle
// @param pitch_angle: Vertical rotation angle
void		process_mouse_movement(t_app *app, double yaw_angle, double pitch_angle);

// @param xpos: X position of mouse cursor
// @param ypos: Y position of mouse cursor
// @param param: User parameter (typically app pointer)
void		cursor_hook(double xpos, double ypos, void *param);

// @param xdelta: Horizontal scroll delta
// @param ydelta: Vertical scroll delta
// @param param: User parameter (typically app pointer)
void		scroll_hook(double xdelta, double ydelta, void *param);

// cleanup/cleanup.c
// @param scene: Scene struct to free all allocated memory from
void		free_scene(t_scene *scene);

// @param tokens: Array of strings to free
void		free_tokens(char **tokens);

// debugging/print_scene.c
// @param scene: Scene struct to print debug information for
void		print_scene(const t_scene *scene);


#endif
