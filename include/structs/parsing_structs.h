/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_structs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:10:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 09:10:00 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_STRUCTS_H
# define PARSING_STRUCTS_H

# include "app_structs.h"

// @param c: Parsed color value
// @param success: 1 if parsing succeeded, 0 if failed
typedef struct s_color_res
{
	t_color	c;
	int		success;
}	t_clr_res;

// @param v: Parsed 3D vector value
// @param success: 1 if parsing succeeded, 0 if failed
typedef struct s_vec3d_res
{
	t_vec3d	v;
	int		success;
}	t_vec3d_res;

// @param f: Parsed float value
// @param success: 1 if parsing succeeded, 0 if failed
typedef struct s_float_res
{
	float	f;
	int		success;
}	t_float_res;

#endif
