/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:32:32 by Florian Kei       #+#    #+#             */
/*   Updated: 2025/08/25 14:31:54 by Florian Kei      ###   ########.fr       */
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

// Default window settings
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

// Struct for 3D vectors
// @param x: X-coordinate component
// @param y: Y-coordinate component
// @param z: Z-coordinate component
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

// Struct for colors (RGB 0-255)
// @param r: Red component (0-255)
// @param g: Green component (0-255)
// @param b: Blue component (0-255)
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

// Struct for rays
// @param origin: Starting point of the ray
// @param direction: Direction vector of the ray (should be normalized)
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

// Object types enumeration
// @param SPHERE: Sphere primitive
// @param PLANE: Plane primitive
// @param CYLINDER: Cylinder primitive
// @param CONE: Cone primitive
typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}	t_obj_type;

// Union for object-specific data
// @param s_sphere: Sphere data (center point and radius)
// @param s_plane: Plane data (point on plane and normal vector)
// @param s_cylinder: Cylinder data (base point, axis, radius, height)
// @param s_cone: Cone data (center point, axis, radius, height)
typedef union u_obj_data
{
	struct
	{
		t_vec3	center;		// Center point of the sphere
		double	radius;		// Radius of the sphere
	}	s_sphere;
	struct
	{
		t_vec3	point;		// Point on the plane
		t_vec3	normal;		// Normal vector of the plane
	}	s_plane;
	struct
	{
		t_vec3	base;		// Base center point of cylinder
		t_vec3	axis;		// Axis direction vector
		double	radius;		// Radius of cylinder
		double	height;		// Height of cylinder
	}	s_cylinder;
	struct
	{
		t_vec3	center;		// Center point of cone base
		t_vec3	axis;		// Axis direction vector
		double	radius;		// Radius of cone base
		double	height;		// Height of cone
	}	s_cone;
}	t_obj_data;

// Struct for lighting parameters
// @param point: Point on surface being lit
// @param normal: Surface normal at the point
// @param view_dir: Direction from point to camera
// @param shininess: Material shininess factor
typedef struct s_light_params
{
	t_vec3	point;		// Point on surface being lit
	t_vec3	normal;		// Surface normal at the point
	t_vec3	view_dir;	// Direction from point to camera
	double	shininess;	// Material shininess factor
}	t_light_params;

// Texture types enumeration
// @param TEXTURE_NONE: No texture applied
// @param TEXTURE_CHECKERBOARD: Checkerboard pattern texture
// @param TEXTURE_BUMP_MAP: Bump mapping texture
typedef enum e_texture_type
{
	TEXTURE_NONE,
	TEXTURE_CHECKERBOARD,
	TEXTURE_BUMP_MAP
}	t_texture_type;

// Struct for objects
// @param type: Type of geometric primitive
// @param data: Union containing primitive-specific data
// @param color: RGB color of the object
// @param shininess: Specular reflection shininess factor
// @param texture_type: Type of texture applied
// @param texture_scale: Scaling factor for texture
// @param next: Pointer to next object in linked list
typedef struct s_object
{
	t_obj_type		type;			// Type of geometric primitive
	t_obj_data		data;			// Union containing primitive-specific data
	t_color			color;			// RGB color of the object
	double			shininess;		// Specular reflection shininess factor
	t_texture_type	texture_type;	// Type of texture applied
	double			texture_scale;	// Scaling factor for texture
	struct s_object	*next;			// Pointer to next object in linked list
}	t_object;

// Struct for light
// @param position: 3D position of the light source
// @param brightness: Light intensity (0.0 to 1.0)
// @param color: RGB color of the light
// @param next: Pointer to next light in linked list
typedef struct s_light
{
	t_vec3			position;		// 3D position of the light source
	double			brightness;		// Light intensity (0.0 to 1.0)
	t_color			color;			// RGB color of the light
	struct s_light	*next;			// Pointer to next light in linked list
}	t_light;

// Struct for camera
// @param position: 3D position of the camera
// @param direction: Direction vector the camera is facing
// @param fov: Field of view in degrees
typedef struct s_camera
{
	t_vec3	position;	// 3D position of the camera
	t_vec3	direction;	// Direction vector the camera is facing
	double	fov;		// Field of view in degrees
}	t_camera;

// Struct for ambient light
// @param ratio: Ambient light intensity (0.0 to 1.0)
// @param color: RGB color of the ambient light
typedef struct s_ambient
{
	double	ratio;		// Ambient light intensity (0.0 to 1.0)
	t_color	color;		// RGB color of the ambient light
}	t_ambient;

// Main scene struct
// @param camera: Camera configuration and position
// @param ambient: Ambient lighting settings
// @param lights: Linked list of light sources
// @param objects: Linked list of geometric objects
typedef struct s_scene
{
	t_camera	camera;		// Camera configuration and position
	t_ambient	ambient;	// Ambient lighting settings
	t_light		*lights;	// Linked list of light sources
	t_object	*objects;	// Linked list of geometric objects
}	t_scene;

// Main app struct
// @param mlx: MLX42 library instance
// @param img: MLX42 image for rendering
// @param scene: Complete scene data
// @param window_width: Window width in pixels
// @param window_height: Window height in pixels
typedef struct s_app
{
	mlx_t		*mlx;			// MLX42 library instance
	mlx_image_t	*img;			// MLX42 image for rendering
	t_scene		scene;			// Complete scene data
	int			window_width;	// Window width in pixels
	int			window_height;	// Window height in pixels
}	t_app;

// Additional parsing utils
// @param c: Parsed color value
// @param success: 1 if parsing succeeded, 0 if failed
typedef struct s_color_res
{
	t_color	c;		// Parsed color value
	int		success;	// 1 if parsing succeeded, 0 if failed
}	t_clr_res;

// @param v: Parsed 3D vector value
// @param success: 1 if parsing succeeded, 0 if failed
typedef struct s_vec3_res
{
	t_vec3	v;		// Parsed 3D vector value
	int		success;	// 1 if parsing succeeded, 0 if failed
}	t_vec3_res;

// @param f: Parsed float value
// @param success: 1 if parsing succeeded, 0 if failed
typedef struct s_float_res
{
	float	f;		// Parsed float value
	int		success;	// 1 if parsing succeeded, 0 if failed
}	t_float_res;

// Function prototypes with parameter explanations

// init.c
// @param app: Pointer to application struct to initialize
int			init_app(t_app *app);

// rendering/render.c
// @param app: Pointer to application struct containing scene and mlx data
void		render_scene(t_app *app);

// rendering/intersections.c
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

// rendering/lighting.c
// @param point: Point on surface to calculate lighting for
// @param normal: Surface normal at the point
// @param scene: Scene containing lights and ambient lighting
// @param obj: Object being lit (for material properties)
// @return: Final color with lighting applied
t_color		compute_lighting(t_vec3 point, t_vec3 normal,
				t_scene *scene, t_object *obj);

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
double		compute_diffuse(t_vec3 light_dir, t_vec3 normal);

// @param light_dir: Direction vector from point to light source
// @param normal: Surface normal vector
// @param view_dir: Direction vector from point to camera
// @param shininess: Material shininess factor
// @return: Specular lighting factor (0.0 to 1.0)
double		compute_specular(t_vec3 light_dir, t_vec3 normal,
				t_vec3 view_dir, double shininess);

// rendering/textures.c
// @param obj: Object to apply texture to
// @param point: Point on object surface
// @return: Texture color at the given point
t_color		apply_texture(t_object *obj, t_vec3 point);

// @param obj: Object to apply bump mapping to
// @param point: Point on object surface
// @param normal: Original surface normal
// @return: Modified normal vector with bump mapping applied
t_vec3		apply_bump_mapping(t_object *obj, t_vec3 point, t_vec3 normal);

// calculations/vec_ops.c
// @param a: First vector
// @param b: Second vector
// @return: Sum of the two vectors
t_vec3		vec_add(t_vec3 a, t_vec3 b);

// @param a: First vector
// @param b: Second vector
// @return: Difference of the two vectors (a - b)
t_vec3		vec_sub(t_vec3 a, t_vec3 b);

// @param a: Vector to multiply
// @param scalar: Scalar value to multiply by
// @return: Vector multiplied by scalar
t_vec3		vec_mul(t_vec3 a, double scalar);

// @param a: First vector
// @param b: Second vector
// @return: Dot product of the two vectors
double		vec_dot(t_vec3 a, t_vec3 b);

// @param v: Vector to calculate length of
// @return: Length (magnitude) of the vector
double		vec_length(t_vec3 v);

// calculations/vec_utils.c
// @param v: Vector to normalize
// @return: Normalized vector (unit vector)
t_vec3		vec_normalize(t_vec3 v);

// @param a: First vector
// @param b: Second vector
// @return: Cross product of the two vectors
t_vec3		vec_cross(t_vec3 a, t_vec3 b);

// @param incident: Incident ray direction
// @param normal: Surface normal vector
// @return: Reflected ray direction
t_vec3		vec_reflect(t_vec3 incident, t_vec3 normal);

// user_input/keys.c
// @param keydata: Key event data from MLX42
// @param param: User parameter (typically app pointer)
void		key_hook(mlx_key_data_t keydata, void *param);

// cleanup/cleanup.c
// @param scene: Scene struct to free all allocated memory from
void		free_scene(t_scene *scene);

// @param tokens: Array of strings to free
void		free_tokens(char **tokens);

// debugging/print_scene.c
// @param scene: Scene struct to print debug information for
void		print_scene(const t_scene *scene);

#endif
