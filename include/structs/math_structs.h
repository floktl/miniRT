/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 10:02:01 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_STRUCTS_H
# define MATH_STRUCTS_H

// Struct for 3D vectors
// @param x: X-coordinate component
// @param y: Y-coordinate component
// @param z: Z-coordinate component
typedef struct s_vec3d
{
	double	x;
	double	y;
	double	z;
}	t_vec3d;

// Struct for 2D vectors
// @param x: X-coordinate component
// @param y: Y-coordinate component
typedef struct s_vec2d
{
	double	x;
	double	y;
}	t_vec2d;

// Struct for rays
// @param origin: Starting point of the ray
// @param direction: Direction vector of the ray (should be normalized)
typedef struct s_ray
{
	t_vec3d	origin;
	t_vec3d	direction;
}	t_ray;

#endif
