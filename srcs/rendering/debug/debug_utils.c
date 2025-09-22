/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 09:49:53 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	format_vector_string(char *buffer, const char *label, t_vec3d vec)
{
	sprintf(buffer, "%s: (%.1f, %.1f, %.1f)", label, vec.x, vec.y, vec.z);
}

void	render_debug_text(t_app *app, t_vec3d hit_point)
{
	char		debug_cam_text[64];
	char		hit_point_text[64];
	mlx_image_t	*text_image;

	format_vector_string(debug_cam_text, "Debug Cam",
		app->scene.debug_camera.position);
	format_vector_string(hit_point_text, "Hit Point", hit_point);
	text_image = mlx_put_string(app->window.mlx, debug_cam_text, 10, 10);
	if (text_image)
		mlx_delete_image(app->window.mlx, text_image);
	text_image = mlx_put_string(app->window.mlx, hit_point_text, 10, 30);
	if (text_image)
		mlx_delete_image(app->window.mlx, text_image);
}

void	draw_circle_pixel(t_app *app, t_vec3d screen_pos, int x, int y)
{
	int	screen_x;
	int	screen_y;

	screen_x = (int)screen_pos.x + x;
	screen_y = (int)screen_pos.y + y;
	if (screen_x >= 0 && screen_x < app->window.width
		&& screen_y >= 0 && screen_y < app->window.height)
	{
		draw_red_pixel(app, screen_x, screen_y);
	}
}
