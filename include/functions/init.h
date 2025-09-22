/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 10:12:51 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "../structs/app_structs.h"

// init.c
// @param app: Pointer to application struct to initialize
int			init_app(t_app *app);

// @param app: Pointer to application struct
void		init_camera_variables(t_app *app);

// @param app: Pointer to application struct
void		init_mouse_variables(t_app *app);

// @param app: Pointer to application struct
void		init_zoom_variables(t_app *app);

// @param app: Pointer to application struct
void		init_performance_variables(t_app *app);

#endif
