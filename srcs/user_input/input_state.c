/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:10:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 09:51:40 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Update interaction state based on current input activity
** Handles scroll inactivity detection and interaction mode management
** @param app: Pointer to application struct
*/
void	update_input_state(t_app *app)
{
	if (app->input.scroll_activity && !app->mouse.left_dragging
		&& !app->mouse.right_dragging)
	{
		app->input.interaction_mode = false;
		app->render.needs_rerender = true;
	}
}
