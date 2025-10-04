/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:17:31 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/04 11:43:47 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//  ┌─────────────────────────────────────────────────────────────────┐
//  │                    FRAME LOGIC DECISION TREE                    │
//  ├─────────────────────────────────────────────────────────────────┤
//  │                                                                 │
//  │ 1. Check: needs_rerender?                                       │
//  │    ❌ NO  → return (skip this frame)                            │
//  │    ✅ YES → continue                                            │
//  │                                                                 │
//  │ 2. Check: interaction_mode?                                     │
//  │    ❌ NO  → Full Resolution Rendering                           │
//  │    ✅ YES → Frame Skipping Logic                                │
//  │                                                                 │
//  │ 3. Frame Skipping (during interaction):                         │
//  │    Check: frame_counter % render_skip_frames == 0?              │
//  │    ❌ NO  → frame_counter++, return (skip this frame)           │
//  │    ✅ YES → Low Resolution Rendering                            │
//  │                                                                 │
//  │ 4. After Rendering:                                             │
//  │    • needs_rerender = false                                     │
//  │    • frame_counter++                                            │
//  │                                                                 │
//  └─────────────────────────────────────────────────────────────────┘
/* render loop that switches between full & low resolution */
void	render_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (!app->render.needs_rerender)
		return ;
	if (app->input.interaction_mode
		&& (app->render.frame_counter
			% app->render.render_skip_frames != 0))
	{
		app->render.frame_counter++;
		return ;
	}
	if (app->input.interaction_mode)
	{
		app->render.render_scale = 2;
		fill_window_with_raytracing_low_res(app, render_pixel);
		update_input_state(app);
	}
	else
	{
		app->render.render_scale = 1;
		fill_window_with_raytracing(app, render_pixel);
	}
	app->render.needs_rerender = false;
	app->render.frame_counter++;
}
