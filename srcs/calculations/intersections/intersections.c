/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:19:58 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/20 11:18:29 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
* GEOMETRIC PRIMITIVE INTERSECTION CALCULATIONS
*
* Intersection testing determines where rays hit geometric objects:
* - Ray-sphere intersection uses quadratic equation solving
* - Ray-plane intersection uses dot product calculations
* - Ray-cylinder intersection combines quadratic solving with height bounds
* - Ray-cone intersection uses quadratic equations with conical constraints
*
* Mathematical concepts:
* - Quadratic equations: ax² + bx + c = 0 for curved surfaces
* - Dot products: For plane intersections and distance calculations
* - Parametric equations: Ray = origin + t*direction
* - Distance bounds: Checking if intersection is within object limits
*/

// t = - (u \cdot (o-c)) \pm \sqrt{(u \cdot (o-c))^2 - (\|o-c\|^2 - r^2)}
//  Equation for a line starting at o
// x = o + d * u
// x : points on the line
// o : origin of the line
// d : distance from the origin of the line
// u : direction of line (a non-zero vector)

/*
* INTERSECTION FUNCTION MOCKUPS
*
* These functions are implemented in separate files:
* - intersect_plane() -> plane_intersection.c
* - intersect_cylinder() -> cylinder_intersection.c
* - intersect_cone() -> cone_intersection.c
* - intersect_sphere() -> sphere_intersection.c
*
* Each file contains the full implementation for its respective
* geometric primitive intersection calculation.
*/
