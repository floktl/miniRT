/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:17:50 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/19 09:22:14 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * BASIC VECTOR UTILITIES FOR 3D MATHEMATICS
 *
 * This file contains fundamental vector operations used in ray tracing:
 * - Addition: Combines two vectors component-wise
 * - Subtraction: Finds difference between two vectors
 * - Scalar multiplication: Scales vector by a number
 * - Dot product: Calculates angle relationship between vectors
 * - Length: Computes magnitude (distance) of vector
 *
 * Examples:
 * vec_add({1,2,3}, {4,5,6}) = {5,7,9}          // Component addition
 * vec_sub({5,7,9}, {1,2,3}) = {4,5,6}          // Component subtraction
 * vec_mul({1,2,3}, 2.0) = {2,4,6}              // Scalar scaling
 * vec_dot({1,0,0}, {0,1,0}) = 0                // Perpendicular vectors
 * vec_length({3,4,0}) = 5.0                    // Pythagorean theorem
 */

/* Adds two vectors component-wise */
t_vec3d	vec_add(t_vec3d a, t_vec3d b)
{
	return ((t_vec3d){a.x + b.x, a.y + b.y, a.z + b.z});
}

/* Subtracts second vector from first vector */
t_vec3d	vec_sub(t_vec3d a, t_vec3d b)
{
	return ((t_vec3d){a.x - b.x, a.y - b.y, a.z - b.z});
}

/* Multiplies vector by scalar value */
t_vec3d	vec_mul(t_vec3d a, double scalar)
{
	return ((t_vec3d){a.x * scalar, a.y * scalar, a.z * scalar});
}

/* Calculates dot product of two vectors */
double	vec_dot(t_vec3d a, t_vec3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/* Calculates magnitude (length) of vector */
double	vec_length(t_vec3d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
