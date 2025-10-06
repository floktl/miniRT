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
// @param LIGHT: Light source sphere
typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	LIGHT
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
		t_vec3d	center;
		double	radius;
	}	s_sphere;
	struct
	{
		t_vec3d	point;
		t_vec3d	normal;
	}	s_plane;
	struct
	{
		t_vec3d	base;
		t_vec3d	axis;
		double	radius;
		double	height;
	}	s_cylinder;
	struct
	{
		t_vec3d	vertex;
		t_vec3d	center;
		t_vec3d	axis;
		double	radius;
		double	height;
	}	s_cone;
}	t_obj_data;

// Struct for lighting parameters
// @param point: Point on surface being lit
// @param normal: Surface normal at the point
// @param view_dir: Direction from point to camera
// @param shininess: Material shininess factor
typedef struct s_light_params
{
	t_vec3d			point;
	t_vec3d			normal;
	t_vec3d			view_dir;
	double			shininess;
	struct s_scene	*scene;
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
	t_obj_type		type;
	t_obj_data		data;
	t_color			color;
	double			shininess;
	t_texture_type	texture_type;
	double			texture_scale;
	bool			is_light_sphere;
	struct s_object	*next;
}	t_object;

// Struct for light
// @param position: 3D position of the light source
// @param brightness: Light intensity (0.0 to 1.0)
// @param color: RGB color of the light
// @param next: Pointer to next light in linked list
typedef struct s_light
{
	t_vec3d			position;
	double			brightness;
	t_color			color;
	struct s_light	*next;
}	t_light;

// Struct for camera
// @param position: 3D position of the camera
// @param direction: Direction vector the camera is facing
// @param fov: Field of view in degrees
typedef struct s_camera
{
	t_vec3d	position;
	t_vec3d	direction;
	t_vec3d	up;
	double	fov;
}	t_camera;

// Struct for ambient light
// @param ratio: Ambient light intensity (0.0 to 1.0)
// @param color: RGB color of the ambient light
typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

// Main scene struct
// @param camera: Camera configuration and position
// @param ambient: Ambient lighting settings
// @param lights: Linked list of light sources
// @param objects: Linked list of geometric objects
typedef struct s_scene
{
	t_camera	camera;
	t_ambient	ambient;
	t_light		*lights;
	t_object	*objects;
}	t_scene;

// Window and display state
// @param mlx: MLX42 library instance
// @param img: MLX42 image for rendering
// @param width: Window width in pixels
// @param window_height: Window height in pixels
typedef struct s_window_state
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			width;
	int			height;
}	t_window_state;

// Camera movement state
// @param original_pos: Original camera position
// @param original_dir: Original camera direction
// @param move_speed: Camera movement speed
typedef struct s_camera_state
{
	t_vec3d		original_pos;
	t_vec3d		original_dir;
	double		move_speed;
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
	bool		left_dragging;
	bool		right_dragging;
	int			last_x;
	int			last_y;
	double		left_sensitivity;
	double		right_sensitivity;
	double		accumulated_x;
	double		accumulated_y;
}	t_mouse_state;

// Zoom state
// @param factor: Current zoom factor
// @param speed: Zoom speed multiplier
// @param min_zoom: Minimum zoom level
// @param max_zoom: Maximum zoom level
typedef struct s_zoom_state
{
	double		factor;
	double		speed;
	double		min_zoom;
	double		max_zoom;
}	t_zoom_state;

// Rendering state
// @param needs_rerender: Flag indicating scene needs re-rendering
// @param frame_counter: Frame counter for simple frame limiting
// @param render_skip_frames: Skip frames during interaction
// @param render_scale: Render scale factor (1 = full resolution, 2 = half)
// @param sphere_color: Color for drawing spheres in debug mode
typedef struct s_render_state
{
	bool		needs_rerender;
	int			frame_counter;
	int			render_skip_frames;
	int			render_scale;
	uint32_t	sphere_color;
}	t_render_state;

// Input state
// @param interaction_mode: True when user is actively interacting
// @param scroll_activity: True when scroll wheel is being used
// @param shift_pressed: True when Shift key is currently pressed
typedef struct s_input_state
{
	bool		interaction_mode;
	bool		scroll_activity;
	bool		ctrl_pressed;
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
	t_window_state	window;
	t_scene			scene;
	t_camera_state	camera;
	t_mouse_state	mouse;
	t_zoom_state	zoom;
	t_render_state	render;
	t_input_state	input;
}	t_app;

#endif
