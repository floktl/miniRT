/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 00:00:00 by yourname         #+#    #+#             */
/*   Updated: 2024/10/10 00:00:00 by yourname        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

// Default window settings
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

// Struct for 3D vectors
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

// Struct for colors (RGB 0-255)
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

// Struct for rays
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

// Object types
typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

// Union for object-specific data
typedef union u_obj_data
{
	struct
	{
		t_vec3	center;
		double	radius;
	}	s_sphere;
	struct
	{
		t_vec3	point;
		t_vec3	normal;
	}	s_plane;
	struct
	{
		t_vec3	base;
		t_vec3	axis;
		double	radius;
		double	height;
	}	s_cylinder;
}	t_obj_data;

// Struct for objects
typedef struct s_object
{
	t_obj_type		type;
	t_obj_data		data;
	t_color			color;
	struct s_object	*next;
}	t_object;

// Struct for light
typedef struct s_light
{
	t_vec3			position;
	double			brightness;
	t_color			color;
	struct s_light	*next;
}	t_light;

// Struct for camera
typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	double	fov;
}	t_camera;

// Struct for ambient light
typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

// Main scene struct
typedef struct s_scene
{
	t_camera	camera;
	t_ambient	ambient;
	t_light		*lights;
	t_object	*objects;
}	t_scene;

// Main app struct
typedef struct s_app
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
	int			window_width;
	int			window_height;
}	t_app;

// Additional parsing utils
typedef struct {
	t_color c;
	int success;
} color_res;

typedef struct {
	t_vec3 v;
	int success;
} vec3_res;

typedef struct {
	float f;
	int success;
} float_res;

// Function prototypt_scenees
// init.c
int		init_app(t_app *app);

// parsing/parser.c
int		parse_scene(const char *filename, t_scene *scene);
int		parse_line(char *line, t_scene *scene);

// parsing/parser_utils.c
int		count_tokens(char **tokens);
void	trim_token(char *token);
void	trim_all_tokens(char **tokens, int token_count);
void	replace_tabs_with_spaces(char *line);

// parsing/parser_utils2.c
int		dispatch_and_return(t_scene *scene, char **tokens, const char *type, int (*parse_func)(char **, t_scene *));

// parsing/parse_scene_elements.c
int		parse_ambient(char **tokens, t_scene *scene);
int		parse_camera(char **tokens, t_scene *scene);
int		parse_light(char **tokens, t_scene *scene);

// parsing/parse_scene_utils.c
int		check_ambient_duplicate(t_scene *scene);
int		check_camera_duplicate(t_scene *scene);
int		validate_ambient_ratio(float ratio);
int		validate_camera_fov(float fov);
int		validate_light_brightness(float brightness);

// parsing/parse_scene_utils2.c
int		parse_error(const char *element, const char *message);
int		count_and_init_tokens(char **tokens, int *token_count, int *idx);
int		parse_ambient_ratio(char **tokens, int *idx, int token_count, float_res *fr);
int		set_ambient_data(t_scene *scene, float_res fr, t_color col);
int		set_camera_data(t_scene *scene, vec3_res pr, vec3_res dr, float_res fr);

// parsing/parse_scene_utils3.c
int		parse_ambient_color(char **tokens, int *idx, int token_count, color_res *cr);
int		parse_camera_position(char **tokens, int *idx, int token_count, vec3_res *pr);
int		parse_camera_direction(char **tokens, int *idx, int token_count, vec3_res *dr);
int		parse_camera_fov(char **tokens, int *idx, int token_count, float_res *fr);

// parsing/parse_light_utils.c
int		cleanup_light_error(t_light *light, const char *message);
int		parse_light_position(char **tokens, int *idx, int token_count, vec3_res *pr);
int		parse_light_brightness(char **tokens, int *idx, int token_count, float_res *br);
int		parse_light_color(char **tokens, int *idx, int token_count, color_res *cr);

// parsing/parse_light_utils2.c
int		setup_light(t_light *light, t_scene *scene);
int		parse_light_internal(char **tokens, t_scene *scene);

// parsing/parse_sphere.c
int		validate_sphere_diameter(float diameter);
int		parse_sphere_center(t_object *obj, char **tokens, int *idx, int token_count);
int		parse_sphere_diameter(t_object *obj, char **tokens, int *idx, int token_count);
int		parse_sphere_color(t_object *obj, char **tokens, int *idx, int token_count);
int		validate_sphere_data(t_object *obj, float_res dr);

// parsing/parse_primitive_utils.c
int		validate_plane_normal(t_vec3 normal);
int		validate_cylinder_dimensions(float diameter, float height);
int		init_object_and_count(t_object **obj, char **tokens, int *token_count, int *idx);

// parsing/parse_primitive_utils2.c
int		parse_plane_point(t_object *obj, char **tokens, int *idx, int token_count);
int		parse_plane_normal(t_object *obj, char **tokens, int *idx, int token_count);
int		parse_plane_color(t_object *obj, char **tokens, int *idx, int token_count);
int		parse_cylinder_base(t_object *obj, char **tokens, int *idx, int token_count);
int		parse_cylinder_axis(t_object *obj, char **tokens, int *idx, int token_count);

// parsing/parse_primitive_utils3.c
int		parse_cylinder_dimensions(t_object *obj, char **tokens, int *idx, int token_count);
int		parse_cylinder_color(t_object *obj, char **tokens, int *idx, int token_count);
int		validate_cylinder_data(t_object *obj, float_res dr, float_res hr);

// parsing/parse_primitives.c
int		parse_sphere(char **tokens, t_scene *scene);
int		parse_plane(char **tokens, t_scene *scene);
int		parse_cylinder(char **tokens, t_scene *scene);
int		cleanup_object_error(t_object *obj, const char *message);

// parsing/parse_color.c
t_color	parse_color(char *str);
int		is_color_zero(t_color c);

// parsing/parse_color_utils.c
t_color	validate_color(t_color color, char **parts);
int		validate_color_values(t_color color);
int		clean_newlines(char *str);
int		trim_part(char *part, char **trimmed);
int		process_parts(char **parts, char **trimmed_parts);

// parsing/parse_color_utils2.c
int		validate_and_parse_parts(char **trimmed_parts, char **parts, char *clean_str);
void	cleanup_memory(char **trimmed_parts, char **parts, char *clean_str);

// parsing/parse_vector.c
t_vec3	parse_vec3(char *str);
int		is_vec_zero(t_vec3 v);
int		is_vec_normalized(t_vec3 v);

// parsing/parse_validation.c
int		is_integer_string(const char *str);

// parsing/parse_tokens.c
color_res parse_color_tokens(char **tokens, int *idx, int token_count);

// parsing/parse_token_utils.c
int		handle_single_token(char **tokens, int *idx, char **str);
int		check_color_validity(t_color c, char *str);
int		process_color_tokens_loop(char **tokens, int *idx, int token_count, char **str);
color_res init_color_res(void);

// parsing/parse_tokens_vec.c
vec3_res parse_vec3_tokens(char **tokens, int *idx, int token_count);

// parsing/parse_vec_token_utils.c
vec3_res	init_vec3_res(void);
vec3_res	process_single(char **tokens, int *local_idx, char **str);
vec3_res	handle_loop(char **tokens, int *local_idx, int token_count, char **str);

// parsing/parse_vec_token_utils2.c
int		handle_single_vec_token(char **tokens, int *local_idx, char **str);
int		check_vec_validity(t_vec3 v, char *str);
vec3_res	set_vec3_res(t_vec3 v, int local_idx, int *idx);
int		process_vec_tokens_loop(char **tokens, int *local_idx, int token_count, char **str);

// parsing/parse_tokens_float.c
float_res parse_float_tokens(char **tokens, int *idx, int token_count);

// rendering/render.c
void	render_scene(t_app *app);

// rendering/intersections.c
double	intersect_sphere(t_ray ray, t_object *s_sphere);
double	intersect_plane(t_ray ray, t_object *s_plane);
double	intersect_cylinder(t_ray ray, t_object *s_cylinder);

// rendering/lighting.c
t_color	compute_lighting(t_vec3 point, t_vec3 normal,
			t_scene *scene, t_color obj_color);

// calculations/vec_ops.c
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_sub(t_vec3 a, t_vec3 b);
t_vec3	vec_mul(t_vec3 a, double scalar);
double	vec_dot(t_vec3 a, t_vec3 b);
double	vec_length(t_vec3 v);

// calculations/vec_utils.c
t_vec3	vec_normalize(t_vec3 v);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);

// user_input/keys.c
void	key_hook(mlx_key_data_t keydata, void *param);

// cleanup/cleanup.c
void	free_scene(t_scene *scene);
void	free_tokens(char **tokens);

// debugging/print_scene.c
void	print_scene(const t_scene *scene);

#endif
