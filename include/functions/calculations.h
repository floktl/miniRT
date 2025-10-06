/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/06 09:15:45 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATIONS_H
# define CALCULATIONS_H

# include "../structs/app_structs.h"

// calculations/ray_generation.c
// @param app: Pointer to application struct
// @param x: X pixel coordinate
// @param y: Y pixel coordinate
// @return: Ray from camera through pixel
t_ray		get_ray(t_app *app, int x, int y);

// calculations/intersections/intersection_utils.c
// @param ray: Ray to test for intersections
// @param scene: Scene containing objects to test
// @param hit_obj: Pointer to store the hit object
// @return: Distance to closest intersection, -1 if none
double		find_closest_intersection(t_ray ray, t_scene *scene,
				t_object **hit_obj);
double		find_closest_intersection_debug(t_ray ray, t_scene *scene,
				t_object **hit_obj);

// @param point: Point on object surface
// @param obj: Object to calculate normal for
// @return: Normalized surface normal vector
t_vec3d		get_normal(t_vec3d point, t_object *obj);

// @brief Calculates the intersection distance between a ray and an object.
// @param ray: The ray to test for intersection
// @param obj: The object to test against
double		calculate_object_intersection(t_ray ray, t_object *obj);

// calculations/intersections/intersections.c
// @param ray: Ray to test for intersection
// @param s_sphere: Sphere object to test against
// @return: Distance to intersection point, -1 if no intersection
double		intersect_sphere(t_ray ray, t_object *s_sphere);
double		intersect_sphere_debug(t_ray ray, t_object *s_sphere);

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

// calculations/intersections/cylinder_helpers.c
// @param ray_dir: Ray direction vector
// @param oc: Vector from ray origin to cylinder base
// @param obj: Cylinder object
// @param dot_dir_axis: Dot product of ray direction and cylinder axis
// @return: Discriminant of quadratic equation
double		calculate_cylinder_quadratic_terms(t_vec3d ray_dir, t_vec3d oc,
				t_object *obj, double dot_dir_axis);

// @param ray: Ray to test
// @param obj: Cylinder object
// @param t: Intersection parameter
// @return: True if intersection is within cylinder bounds
bool		is_cylinder_intersection_inside(t_ray ray, t_object *obj, double t);

// @param ray: Ray to test
// @param obj: Cylinder object
// @param t: Intersection parameter
// @param cap: Cap index (0 for bottom, 1 for top)
// @return: True if intersection is on the specified cap
bool		is_cylinder_intersection_on_cap(t_ray ray, t_object *obj, double t,
				int cap);

// @param ray: Ray to test
// @param obj: Cylinder object
// @param dot_dir_axis: Dot product of ray direction and cylinder axis
// @param disc: Discriminant of quadratic equation
// @return: Distance to side intersection, -1 if none
double		find_cylinder_side_intersection(t_ray ray, t_object *obj,
				double dot_dir_axis, double disc);

// @param ray: Ray to test
// @param obj: Cylinder object
// @param dot_dir_axis: Dot product of ray direction and cylinder axis
// @return: Distance to cap intersection, -1 if none
double		find_cylinder_cap_intersection(t_ray ray, t_object *obj,
				double dot_dir_axis);

// calculations/intersections/cone_helpers.c
// @param ray_dir: Ray direction vector
// @param ov: Vector from ray origin to cone vertex
// @param obj: Cone object
// @param cos2_theta: Cosine squared of cone angle
// @return: Discriminant of quadratic equation
double		calculate_cone_quadratic_terms(t_vec3d ray_dir, t_vec3d ov,
				t_object *obj, double cos2_theta);

// @param ray: Ray to test
// @param obj: Cone object
// @param t: Intersection parameter
// @return: True if intersection is within cone bounds
bool		is_cone_intersection_within_cone(t_ray ray, t_object *obj,
				double t);

// @param p: Point to test
// @param obj: Cone object
// @return: True if point is on cone cap
bool		is_point_on_cone_cap(t_vec3d p, t_object *obj);

// @param ray: Ray to test
// @param obj: Cone object
// @param disc: Discriminant of quadratic equation
// @param cos2_theta: Cosine squared of cone angle
// @return: Distance to side intersection, -1 if none
double		find_cone_side_intersection(t_ray ray, t_object *obj,
				double disc, double cos2_theta);

// @param ray: Ray to test
// @param obj: Cone object
// @return: Distance to cap intersection, -1 if none
double		find_cone_cap_intersection(t_ray ray, t_object *obj);

// calculations/color/color_calculations.c
// @param ray: Ray that hit the object
// @param intersection_dist: Distance to intersection point
// @param hit_obj: Object that was hit
// @param scene: Scene containing lighting information
// @return: 32-bit color value for the pixel
uint32_t	calculate_intersection_color(t_ray ray, double intersection_dist,
				t_object *hit_obj, t_scene *scene);

// @param scene: Scene containing ambient lighting information
// @return: 32-bit color value for the background pixel
uint32_t	calculate_background_color(t_scene *scene);

// calculations/color/color_sampling.c
// @param c1: First color
// @param c2: Second color
// @param c3: Third color
// @param c4: Fourth color
// @return: Averaged color value
uint32_t	calculate_average_color(uint32_t c1, uint32_t c2, uint32_t c3,
				uint32_t c4);

// @param app: Pointer to application struct
// @param pixel_calculator: Function pointer to calculate pixel color
// @param x: Base x coordinate
// @param y: Base y coordinate
// @return: Averaged color value from 4 sub-pixel samples
uint32_t	get_supersampled_color(t_app *app,
				uint32_t (*pixel_calculator)(t_app *, int, int), int x, int y);

// calculations/lighting/lighting.c
// @param point: Point on surface to calculate lighting for
// @param normal: Surface normal at the point
// @param scene: Scene containing lights and ambient lighting
// @param obj: Object being lit (for material properties)
// @return: Final color with lighting applied
t_color		compute_lighting(t_vec3d point, t_vec3d normal, t_scene *scene,
				t_object *obj);

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

// @param params: Lighting parameters at the point
// @param light_dir: Direction vector from point to light source
bool		in_shadow(t_light_params *params, t_vec3d light_dir,
				double dist_to_light);

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

// calculations/textures/textures.c
// @param obj: Object to apply texture to
// @param point: Point on object surface
// @return: Texture color at the given point
t_color		apply_texture(t_object *obj, t_vec3d point);

// @param obj: Object to apply bump mapping to
// @param point: Point on object surface
// @param normal: Original surface normal
// @return: Modified normal vector with bump mapping applied
t_vec3d		apply_bump_mapping(t_object *obj, t_vec3d point, t_vec3d normal);

// calculations/vectors/vect_ops.c
t_vec3d		vec_add(t_vec3d a, t_vec3d b);
t_vec3d		vec_sub(t_vec3d a, t_vec3d b);
t_vec3d		vec_mul(t_vec3d a, double scalar);
double		vec_dot(t_vec3d a, t_vec3d b);
double		vec_length(t_vec3d v);
t_vec3d		vec_normalize(t_vec3d v);
t_vec3d		vec_cross(t_vec3d a, t_vec3d b);
t_vec3d		vec_reflect(t_vec3d incident, t_vec3d normal);

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

// calculations/camera_movement/camera_rotation.c
// @param app: Pointer to application struct
// @param angle: Rotation angle in radians
void		rotate_camera_horizontal(t_app *app, double angle);
void		rotate_camera_vertical(t_app *app, double angle);
void		rotate_camera_roll(t_app *app, double angle);

// calculations/camera_movement/camera_zoom.c
// @param app: Pointer to application struct
// @param zoom_amount: Amount to zoom (pos = zoom in, neg = zoom out)
void		zoom_camera_towards_mouse(t_app *app, double zoom_amount);

#endif
