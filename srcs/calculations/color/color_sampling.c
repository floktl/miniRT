/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_sampling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 08:55:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 08:55:13 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Calculate average of four color values for anti-aliasing
** @param c1: First color
** @param c2: Second color
** @param c3: Third color
** @param c4: Fourth color
** @return: Averaged color value
*/
uint32_t	calculate_average_color(uint32_t c1, uint32_t c2,
		uint32_t c3, uint32_t c4)
{
	uint32_t	avg_r;
	uint32_t	avg_g;
	uint32_t	avg_b;

	avg_r = ((c1 >> 24) & 0xFF) + ((c2 >> 24) & 0xFF)
		+ ((c3 >> 24) & 0xFF) + ((c4 >> 24) & 0xFF);
	avg_g = ((c1 >> 16) & 0xFF) + ((c2 >> 16) & 0xFF)
		+ ((c3 >> 16) & 0xFF) + ((c4 >> 16) & 0xFF);
	avg_b = ((c1 >> 8) & 0xFF) + ((c2 >> 8) & 0xFF)
		+ ((c3 >> 8) & 0xFF) + ((c4 >> 8) & 0xFF);
	return (((avg_r / 4) << 24) | ((avg_g / 4) << 16)
		| ((avg_b / 4) << 8) | 0xFF);
}

/*
** Calculate average color from multiple samples for anti-aliasing
** Uses sub-pixel sampling within a single pixel for smoother edges
** @param app: Pointer to application struct
** @param pixel_calculator: Function pointer to calculate pixel color
** @param x: Base x coordinate
** @param y: Base y coordinate
** @return: Averaged color value from 4 sub-pixel samples
*/
uint32_t	get_supersampled_color(t_app *app,
		uint32_t (*pixel_calculator)(t_app*, int, int),
		int x, int y)
{
	uint32_t	color1;
	uint32_t	color2;
	uint32_t	color3;
	uint32_t	color4;

	color1 = pixel_calculator(app, x, y);
	if (x + 1 < app->window_width && y + 1 < app->window_height)
	{
		color2 = pixel_calculator(app, x + 1, y);
		color3 = pixel_calculator(app, x, y + 1);
		color4 = pixel_calculator(app, x + 1, y + 1);
		return (calculate_average_color(color1, color2, color3, color4));
	}
	else
		return (color1);
}
