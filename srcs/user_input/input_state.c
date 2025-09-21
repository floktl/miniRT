/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:10:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/21 13:15:19 by fkeitel          ###   ########.fr       */
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
	if (app->scroll_activity && !app->left_mouse_dragging
		&& !app->right_mouse_dragging)
	{
		app->interaction_mode = false;
		app->needs_rerender = true;
	}
}
