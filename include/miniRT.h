/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:32:32 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/25 10:12:22 by Florian Kei      ###   ########.fr       */
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
# include "parsing.h"

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
	CYLINDER,
	CONE
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
	struct
	{
		t_vec3	center;
		t_vec3	axis;
		double	radius;
		double	height;
	}	s_cone;
}	t_obj_data;

// Struct for lighting parameters
typedef struct s_light_params
{
	t_vec3	point;
	t_vec3	normal;
	t_vec3	view_dir;
	double	shininess;
}	t_light_params;

// Texture types
typedef enum e_texture_type
{
	TEXTURE_NONE,
	TEXTURE_CHECKERBOARD,
	TEXTURE_BUMP_MAP
}	t_texture_type;

// Struct for objects
typedef struct s_object
{
	t_obj_type		type;
	t_obj_data		data;
	t_color			color;
	double			shininess;
	t_texture_type	texture_type;
	double			texture_scale;
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
typedef struct s_color_res
{
	t_color	c;
	int		success;
}	t_clr_res;

typedef struct s_vec3_res
{
	t_vec3	v;
	int		success;
}	t_vec3_res;

typedef struct s_float_res
{
	float	f;
	int		success;
}	t_float_res;

// Function prototypt_scenees
// init.c
int			init_app(t_app *app);

// rendering/render.c
void		render_scene(t_app *app);

// rendering/intersections.c
double		intersect_sphere(t_ray ray, t_object *s_sphere);
double		intersect_plane(t_ray ray, t_object *s_plane);
double		intersect_cylinder(t_ray ray, t_object *s_cylinder);
double		intersect_cone(t_ray ray, t_object *s_cone);

// rendering/lighting.c
t_color		compute_lighting(t_vec3 point, t_vec3 normal,
				t_scene *scene, t_object *obj);

// rendering/lighting_utils.c
t_color		scale_color(t_color color, double factor);
t_color		add_colors(t_color a, t_color b);
double		compute_diffuse(t_vec3 light_dir, t_vec3 normal);
double		compute_specular(t_vec3 light_dir, t_vec3 normal,
				t_vec3 view_dir, double shininess);

// rendering/textures.c
t_color		apply_texture(t_object *obj, t_vec3 point);
t_vec3		apply_bump_mapping(t_object *obj, t_vec3 point, t_vec3 normal);

// calculations/vec_ops.c
t_vec3		vec_add(t_vec3 a, t_vec3 b);
t_vec3		vec_sub(t_vec3 a, t_vec3 b);
t_vec3		vec_mul(t_vec3 a, double scalar);
double		vec_dot(t_vec3 a, t_vec3 b);
double		vec_length(t_vec3 v);

// calculations/vec_utils.c
t_vec3		vec_normalize(t_vec3 v);
t_vec3		vec_cross(t_vec3 a, t_vec3 b);
t_vec3		vec_reflect(t_vec3 incident, t_vec3 normal);

// user_input/keys.c
void		key_hook(mlx_key_data_t keydata, void *param);

// cleanup/cleanup.c
void		free_scene(t_scene *scene);
void		free_tokens(char **tokens);

// debugging/print_scene.c
void		print_scene(const t_scene *scene);

#endif
