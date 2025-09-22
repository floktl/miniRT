/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:10:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 09:10:00 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_STRUCTS_H
# define APP_STRUCTS_H

# include "MLX42/MLX42.h"
# include "math_structs.h"

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
	struct //sphere
	{
		t_vec3d	center;		// Center point of the sphere
		double	radius;		// Radius of the sphere
	}	s_sphere;
	struct //plane
	{
		t_vec3d	point;		// Point on the plane
		t_vec3d	normal;		// Normal vector of the plane
	}	s_plane;
	struct //cylinder
	{
		t_vec3d	base;		// Base center point of cylinder
		t_vec3d	axis;		// Axis direction vector
		double	radius;		// Radius of cylinder
		double	height;		// Height of cylinder
	}	s_cylinder;
	struct //cone
	{
		t_vec3d	center;		// Center point of cone base
		t_vec3d	axis;		// Axis direction vector
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
	t_vec3d	point;		// Point on surface being lit
	t_vec3d	normal;		// Surface normal at the point
	t_vec3d	view_dir;	// Direction from point to camera
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
// @param is_light_sphere: Flag indicating if this object is a light sphere
// @param next: Pointer to next object in linked list
typedef struct s_object
{
	t_obj_type		type;			// Type of geometric primitive
	t_obj_data		data;		// Union containing primitive-specific data
	t_color			color;		// RGB color of the object
	double			shininess;	// Specular reflection shininess factor
	t_texture_type	texture_type;	// Type of texture applied
	double			texture_scale;	// Scaling factor for texture
	bool			is_light_sphere;	// if object is light sphere
	struct s_object	*next;		// Pointer to next object in linked list
}	t_object;

// Struct for light
// @param position: 3D position of the light source
// @param brightness: Light intensity (0.0 to 1.0)
// @param color: RGB color of the light
// @param next: Pointer to next light in linked list
typedef struct s_light
{
	t_vec3d			position;	// 3D position of the light source
	double			brightness;	// Light intensity (0.0 to 1.0)
	t_color			color;		// RGB color of the light
	struct s_light	*next;		// Pointer to next light in linked list
}	t_light;

// Struct for camera
// @param position: 3D position of the camera
// @param direction: Direction vector the camera is facing
// @param fov: Field of view in degrees
typedef struct s_camera
{
	t_vec3d	position;	// 3D position of the camera
	t_vec3d	direction;	// Direction vector the camera is facing
	t_vec3d	up;			// Up vector for camera orientation (for roll rotation)
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
// @param debug_camera: Debug camera configuration and position (optional)
// @param ambient: Ambient lighting settings
// @param lights: Linked list of light sources
// @param objects: Linked list of geometric objects
typedef struct s_scene
{
	t_camera	camera;		// Camera configuration and position
	t_camera	debug_camera;	// Debug camera configuration and position
	bool		has_debug_camera;	// Flag indicating if debug camera present
	t_ambient	ambient;	// Ambient lighting settings
	t_light		*lights;	// Linked list of light sources
	t_object	*objects;	// Linked list of geometric objects
}	t_scene;

// Window and display state
// @param mlx: MLX42 library instance
// @param img: MLX42 image for rendering
// @param width: Window width in pixels
// @param window_height: Window height in pixels
typedef struct s_window_state
{
	mlx_t		*mlx;		// MLX42 library instance
	mlx_image_t	*img;		// MLX42 image for rendering
	int			width;	// Window width in pixels
	int			height;	// Window height in pixels
}	t_window_state;

// Camera movement state
// @param original_pos: Original camera position
// @param original_dir: Original camera direction
// @param move_speed: Camera movement speed
typedef struct s_camera_state
{
	t_vec3d		original_pos;	// Original camera position
	t_vec3d		original_dir;	// Original camera direction
	double		move_speed;	// Camera movement speed
}	t_camera_state;

// Mouse input state
// @param left_dragging: Whether left mouse is being dragged
// @param right_dragging: Whether right mouse is being dragged
// @param last_x: Last mouse X position
// @param last_y: Last mouse Y position
// @param left_sensitivity: Mouse sensitivity for left mouse (panning)
// @param right_sensitivity: Mouse sensitivity for right mouse (rotation)
// @param accumulated_x: Accumulated mouse movement for smoothing
// @param accumulated_y: Accumulated mouse movement for smoothing
typedef struct s_mouse_state
{
	bool		left_dragging;	// Whether left mouse is being dragged
	bool		right_dragging;	// Whether right mouse is being dragged
	int			last_x;		// Last mouse X position
	int			last_y;		// Last mouse Y position
	double		left_sensitivity;	// Mouse sensitivity for left mouse
	double		right_sensitivity;	// Mouse sensitivity for right mouse
	double		accumulated_x;	// Accumulated mouse movement for smoothing
	double		accumulated_y;	// Accumulated mouse movement for smoothing
}	t_mouse_state;

// Zoom state
// @param factor: Current zoom factor
// @param speed: Zoom speed multiplier
// @param min_zoom: Minimum zoom level
// @param max_zoom: Maximum zoom level
typedef struct s_zoom_state
{
	double		factor;		// Current zoom factor
	double		speed;		// Zoom speed multiplier
	double		min_zoom;	// Minimum zoom level
	double		max_zoom;	// Maximum zoom level
}	t_zoom_state;

// Rendering state
// @param needs_rerender: Flag indicating scene needs re-rendering
// @param frame_counter: Frame counter for simple frame limiting
// @param render_skip_frames: Skip frames during interaction
// @param render_scale: Render scale factor (1 = full resolution, 2 = half)
// @param sphere_color: Color for drawing spheres in debug mode
typedef struct s_render_state
{
	bool		needs_rerender;	// Flag indicating scene needs re-rendering
	int			frame_counter;	// Frame counter for simple frame limiting
	int			render_skip_frames;	// Skip frames during interaction
	int			render_scale;	// (1 = full resolution, 2 = half, etc.)
	uint32_t	sphere_color;	// Color for drawing spheres in debug mode
}	t_render_state;

// Input state
// @param interaction_mode: True when user is actively interacting
// @param scroll_activity: True when scroll wheel is being used
// @param shift_pressed: True when Shift key is currently pressed
typedef struct s_input_state
{
	bool		interaction_mode;	// True when user is actively interacting
	bool		scroll_activity;	// True when scroll wheel is being used
	bool		shift_pressed;		// True when Shift key is currently pressed
}	t_input_state;

// Main app struct
// @param window: Window and display state
// @param scene: Complete scene data
// @param camera: Camera movement state
// @param mouse: Mouse input state
// @param zoom: Zoom state
// @param render: Rendering state
// @param input: Input state
typedef struct s_app
{
	t_window_state	window;		// Window and display state
	t_scene			scene;		// Complete scene data
	t_camera_state	camera;		// Camera movement state
	t_mouse_state	mouse;		// Mouse input state
	t_zoom_state	zoom;		// Zoom state
	t_render_state	render;		// Rendering state
	t_input_state	input;		// Input state
}	t_app;

#endif
