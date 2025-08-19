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
	double x;
	double y;
	double z;
} t_vec3;

// Struct for colors (RGB 0-255)
typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

// Struct for rays
typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 direction;
} t_ray;

// Object types
typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
} t_obj_type;

// Union for object-specific data
typedef union u_obj_data
{
	struct
	{
		t_vec3 center;
		double radius;
	} sphere;
	struct
	{
		t_vec3 point;
		t_vec3 normal;
	} plane;
	struct
	{
		t_vec3 base;
		t_vec3 axis;
		double radius;
		double height;
	} cylinder;
} t_obj_data;

// Struct for objects
typedef struct s_object
{
	t_obj_type type;
	t_obj_data data;
	t_color color;
	struct s_object *next;
} t_object;

// Struct for light
typedef struct s_light
{
	t_vec3 position;
	double brightness;
	t_color color;
	struct s_light *next;  // For multiple lights
} t_light;

// Struct for camera
typedef struct s_camera
{
	t_vec3 position;
	t_vec3 direction;
	double fov;
} t_camera;

// Struct for ambient light
typedef struct s_ambient
{
	double ratio;
	t_color color;
} t_ambient;

// Main scene struct
typedef struct s_scene
{
	t_camera camera;
	t_ambient ambient;
	t_light *lights;
	t_object *objects;
} t_scene;

// Main app struct
typedef struct s_app
{
	mlx_t *mlx;
	mlx_image_t *img;
	t_scene scene;
	int window_width;
	int window_height;
} t_app;

// Function prototypes
// init.c
int init_app(t_app *app);

// parsing/parser.c
int parse_scene(const char *filename, t_scene *scene);

// parsing/utils.c
t_color parse_color(char *str);
t_vec3 parse_vec3(char *str);
double parse_double(char *str);
int parse_int(char *str);

// rendering/render.c
void render_scene(t_app *app);

// rendering/intersections.c
double intersect_sphere(t_ray ray, t_object *sphere);
double intersect_plane(t_ray ray, t_object *plane);
double intersect_cylinder(t_ray ray, t_object *cylinder);

// rendering/lighting.c
t_color compute_lighting(t_vec3 point, t_vec3 normal, t_scene *scene, t_color obj_color);

// calculations/vectors.c
t_vec3 vec_add(t_vec3 a, t_vec3 b);
t_vec3 vec_sub(t_vec3 a, t_vec3 b);
t_vec3 vec_mul(t_vec3 a, double scalar);
double vec_dot(t_vec3 a, t_vec3 b);
t_vec3 vec_normalize(t_vec3 v);
double vec_length(t_vec3 v);
t_vec3 vec_cross(t_vec3 a, t_vec3 b);

// user_input/keys.c
void key_hook(mlx_key_data_t keydata, void *param);

// cleanup/cleanup.c
void free_scene(t_scene *scene);

#endif
