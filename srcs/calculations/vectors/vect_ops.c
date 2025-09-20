/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:17:50 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/19 09:21:48 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
* VECTOR OPERATIONS FOR 3D MATHEMATICS
*
* This file contains essential vector operations used in ray tracing:
* - Normalization: Converts vectors to unit length (magnitude = 1)
* - Cross product: Creates perpendicular vector from two input vectors
* - Reflection: Calculates mirror reflection of vector off surface
*
* MATHEMATICAL CONCEPTS:
*
* KEY TERMS:
* - Magnitude: Length/size of vector (distance from origin to point)
* - Perpendicular: At 90-degree angle to another vector/line
* - Normal: Unit vector perpendicular to a surface (length = 1)
* - Incident: Incoming ray/vector hitting a surface
* - Specular: Mirror-like reflection (shiny surfaces)
* - Dot product (·): Measures how aligned two vectors are
* 		(0=perpendicular, 1=same direction)
* - Cross product (×): Creates perpendicular vector from two input vectors
* - Unit vector: Vector with magnitude/length = 1
*
* CROSS PRODUCT (vec_cross):
* - Formula: a × b = (a_y×b_z - a_z×b_y, a_z×b_x - a_x×b_z, a_x×b_y - a_y×b_x)
* - Creates perpendicular vector following right-hand rule
* - Magnitude: |a × b| = |a| × |b| × sin(θ) = area of parallelogram
* - Used for surface normals and coordinate system creation
*
* VECTOR REFLECTION (vec_reflect):
* - Formula: R = I - 2(I·N)N where I=incident, N=normal, R=reflected
* - Implements law of reflection: angle of incidence = angle of reflection
* - Essential for specular highlights and mirror reflections
* - Preserves energy conservation in light interactions
*
* VECTOR NORMALIZATION (vec_normalize):
* - Formula: û = u / |u| where |u| = √(u_x² + u_y² + u_z²)
* - Converts any vector to unit length while preserving direction
* - Required for proper lighting calculations and surface normals
*
* Examples:
* vec_normalize({3, 4, 0}) = {0.6, 0.8, 0}     // Unit vector
* vec_cross({1,0,0}, {0,1,0}) = {0,0,1}        // Right-hand rule
* vec_reflect({1,-1,0}, {0,1,0}) = {1,1,0}     // Mirror reflection
*/

/* Normalizes vector to unit length */
t_vec3d	vec_normalize(t_vec3d v)
{
	double	length;

	length = vec_length(v);
	if (length == 0.0)
	{
		return ((t_vec3d){0, 0, 0});
	}
	return ((t_vec3d){v.x / length, v.y / length, v.z / length});
}

/* Calculates cross product of two vectors */
t_vec3d	vec_cross(t_vec3d a, t_vec3d b)
{
	return ((t_vec3d){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}

/* Reflects incident vector off surface normal */
t_vec3d	vec_reflect(t_vec3d incident, t_vec3d normal)
{
	double	dot_product;

	dot_product = vec_dot(incident, normal);
	return (vec_sub(incident, vec_mul(normal, 2.0 * dot_product)));
}
