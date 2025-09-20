/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:14:48 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 10:53:57 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Moves camera forward in the direction it's facing */
void	move_camera_forward(t_app *app)
{
	t_vec3d	move_vec;

	move_vec = vec_mul(app->scene.camera.direction, app->move_speed);
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
}

/* Moves camera backward from the direction it's facing */
void	move_camera_backward(t_app *app)
{
	t_vec3d	move_vec;

	move_vec = vec_mul(app->scene.camera.direction, -app->move_speed);
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
}

/* Moves camera left (perpendicular to camera direction) */
void	move_camera_left(t_app *app)
{
	t_vec3d	right_vector;
	t_vec3d	move_vec;

	right_vector = vec_cross(app->scene.camera.direction, (t_vec3d){0, 1, 0});
	right_vector = vec_normalize(right_vector);
	move_vec = vec_mul(right_vector, -app->move_speed);
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
}

/* Moves camera right (perpendicular to camera direction) */
void	move_camera_right(t_app *app)
{
	t_vec3d	right_vector;
	t_vec3d	move_vec;

	right_vector = vec_cross(app->scene.camera.direction, (t_vec3d){0, 1, 0});
	right_vector = vec_normalize(right_vector);
	move_vec = vec_mul(right_vector, app->move_speed);
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
}

/* Moves camera up (Y-axis) */
void	move_camera_up(t_app *app)
{
	t_vec3d	move_vec;

	move_vec = (t_vec3d){0, app->move_speed, 0};
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
}

/* Moves camera down (Y-axis) */
void	move_camera_down(t_app *app)
{
	t_vec3d	move_vec;

	move_vec = (t_vec3d){0, -app->move_speed, 0};
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
}

/* Re-renders the scene after camera movement */
void	re_render_scene(t_app *app)
{
	mark_scene_dirty(app);
	optimized_re_render_scene(app);
}

/* Rotates camera horizontally (yaw) around the up vector */
void	rotate_camera_horizontal(t_app *app, double angle)
{
	t_vec3d	up;
	t_vec3d	right;
	t_vec3d	new_direction;
	t_vec3d	new_up;

	up = app->scene.camera.up;
	right = vec_cross(app->scene.camera.direction, up);
	right = vec_normalize(right);
	new_direction.x = app->scene.camera.direction.x
		* cos(angle) + right.x * sin(angle);
	new_direction.y = app->scene.camera.direction.y
		* cos(angle) + right.y * sin(angle);
	new_direction.z = app->scene.camera.direction.z
		* cos(angle) + right.z * sin(angle);
	app->scene.camera.direction = vec_normalize(new_direction);
	new_up = vec_cross(right, app->scene.camera.direction);
	app->scene.camera.up = vec_normalize(new_up);
}

/* Rotates camera vertically (pitch) around the right vector */
void	rotate_camera_vertical(t_app *app, double angle)
{
	t_vec3d	up;
	t_vec3d	right;
	t_vec3d	new_direction;
	t_vec3d	new_up;

	up = app->scene.camera.up;
	right = vec_cross(app->scene.camera.direction, up);
	right = vec_normalize(right);
	new_direction.x = app->scene.camera.direction.x * cos(angle) + up.x * sin(angle);
	new_direction.y = app->scene.camera.direction.y * cos(angle) + up.y * sin(angle);
	new_direction.z = app->scene.camera.direction.z * cos(angle) + up.z * sin(angle);
	app->scene.camera.direction = vec_normalize(new_direction);
	new_up = vec_cross(right, app->scene.camera.direction);
	app->scene.camera.up = vec_normalize(new_up);
}

/* Rotates camera around its forward axis (roll) */
void	rotate_camera_roll(t_app *app, double angle)
{
	t_vec3d	forward;
	t_vec3d	up;
	t_vec3d	right;
	t_vec3d	new_up;

	forward = app->scene.camera.direction;
	forward = vec_normalize(forward);
	up = app->scene.camera.up;
	right = vec_cross(forward, up);
	right = vec_normalize(right);
	new_up.x = up.x * cos(angle) + right.x * sin(angle);
	new_up.y = up.y * cos(angle) + right.y * sin(angle);
	new_up.z = up.z * cos(angle) + right.z * sin(angle);
	app->scene.camera.up = vec_normalize(new_up);
}

/* Moves camera in X and Y directions (panning) */
void	move_camera_pan(t_app *app, double x_offset, double y_offset)
{
	t_vec3d	right;
	t_vec3d	up;
	t_vec3d	move_vec;

	right = vec_cross(app->scene.camera.direction, app->scene.camera.up);
	right = vec_normalize(right);
	up = app->scene.camera.up;
	up = vec_normalize(up);
	move_vec = vec_add(vec_mul(right, x_offset), vec_mul(up, -y_offset));
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
}

/* Handles mouse button events */
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	(void)mods;


	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (action == MLX_PRESS)
		{
			app->left_mouse_dragging = true;
			if (!app->interaction_mode)
			{
				app->interaction_mode = true;
				mark_scene_dirty(app);
			}
			mlx_get_mouse_pos(app->mlx, &app->last_mouse_x, &app->last_mouse_y);
		}
		else if (action == MLX_RELEASE)
		{
			app->left_mouse_dragging = false;
			if (!app->right_mouse_dragging && app->interaction_mode)
			{
				app->interaction_mode = false;
				mark_scene_dirty(app);
			}
		}
	}
	else if (button == MLX_MOUSE_BUTTON_RIGHT)
	{
		if (action == MLX_PRESS)
		{
			app->right_mouse_dragging = true;
			if (!app->interaction_mode)
			{
				app->interaction_mode = true;
				mark_scene_dirty(app);
			}
			mlx_get_mouse_pos(app->mlx, &app->last_mouse_x, &app->last_mouse_y);
		}
		else if (action == MLX_RELEASE)
		{
			app->right_mouse_dragging = false;
			if (!app->left_mouse_dragging && app->interaction_mode)
			{
				app->interaction_mode = false;
				mark_scene_dirty(app);
			}
		}
	}
}

/* Handles mouse cursor movement with accumulated smoothing */
void	cursor_hook(double xpos, double ypos, void *param)
{
	t_app	*app;
	double	delta_x;
	double	delta_y;
	double	yaw_angle;
	double	pitch_angle;

	app = (t_app *)param;
	if (!app->left_mouse_dragging && !app->right_mouse_dragging)
		return;
	delta_x = xpos - app->last_mouse_x;
	delta_y = ypos - app->last_mouse_y;
	app->accumulated_mouse_x += delta_x * app->mouse_sensitivity;
	app->accumulated_mouse_y += delta_y * app->mouse_sensitivity;
	yaw_angle = app->accumulated_mouse_x;
	pitch_angle = app->accumulated_mouse_y;
	if (fabs(app->accumulated_mouse_x) > 0.001 || fabs(app->accumulated_mouse_y) > 0.001)
	{
		if (app->left_mouse_dragging)
		{
			move_camera_pan(app, yaw_angle, pitch_angle);
		}
		else if (app->right_mouse_dragging)
		{
			rotate_camera_horizontal(app, -yaw_angle);
			rotate_camera_vertical(app, pitch_angle);
		}
		app->accumulated_mouse_x = 0.0;
		app->accumulated_mouse_y = 0.0;
		mark_scene_dirty(app);
	}

	app->last_mouse_x = (int)xpos;
	app->last_mouse_y = (int)ypos;
}

/* Handles mouse wheel scrolling for zooming with camera movement */
void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_app	*app;
	t_vec3d	move_vec;
	double	zoom_speed;

	app = (t_app *)param;
	(void)xdelta;
	zoom_speed = ydelta * app->zoom_speed * 0.5;
	move_vec = vec_mul(app->scene.camera.direction, zoom_speed);
	app->scene.camera.position = vec_add(app->scene.camera.position, move_vec);
	mark_scene_dirty(app);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(app->mlx);

	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W)
		{
			move_camera_forward(app);
			re_render_scene(app);
		}
		else if (keydata.key == MLX_KEY_S)
		{
			move_camera_backward(app);
			re_render_scene(app);
		}
		else if (keydata.key == MLX_KEY_A)
		{
			move_camera_left(app);
			re_render_scene(app);
		}
		else if (keydata.key == MLX_KEY_D)
		{
			move_camera_right(app);
			re_render_scene(app);
		}
		else if (keydata.key == MLX_KEY_Q)
		{
			move_camera_up(app);
			re_render_scene(app);
		}
		else if (keydata.key == MLX_KEY_E)
		{
			move_camera_down(app);
			re_render_scene(app);
		}
	}
}
