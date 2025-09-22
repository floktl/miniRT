/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/09/22 10:10:09 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_INPUT_H
# define USER_INPUT_H

# include "../structs/app_structs.h"

// user_input/key_movement.c
// @param app: Pointer to application struct
// @param keydata: Key event data from MLX42
void		handle_forward_back_keys(t_app *app, mlx_key_data_t keydata);
void		handle_left_right_keys(t_app *app, mlx_key_data_t keydata);
void		handle_up_down_keys(t_app *app, mlx_key_data_t keydata);
void		handle_movement_keys(t_app *app, mlx_key_data_t keydata);

// user_input/keys.c
// @param keydata: Key event data from MLX42
// @param param: User parameter (typically app pointer)
void		key_hook(mlx_key_data_t keydata, void *param);

// user_input/mouse_buttons.c
// @param app: Pointer to application struct
void		handle_left_mouse_press(t_app *app);
void		handle_left_mouse_release(t_app *app);
void		handle_right_mouse_press(t_app *app);
void		handle_right_mouse_release(t_app *app);

// @param button: Mouse button that was pressed/released
// @param action: Action (press/release)
// @param mods: Modifier keys
// @param param: User parameter (typically app pointer)
void		mouse_hook(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);

// user_input/mouse_movement.c
// @param app: Pointer to application struct
// @param yaw_angle: Horizontal rotation angle
// @param pitch_angle: Vertical rotation angle
void		process_mouse_movement(t_app *app, double yaw_angle,
				double pitch_angle);

// @param xpos: X position of mouse cursor
// @param ypos: Y position of mouse cursor
// @param param: User parameter (typically app pointer)
void		cursor_hook(double xpos, double ypos, void *param);

// @param xdelta: Horizontal scroll delta
// @param ydelta: Vertical scroll delta
// @param param: User parameter (typically app pointer)
void		scroll_hook(double xdelta, double ydelta, void *param);

// user_input/input_state.c
// @param app: Pointer to application struct
void		update_input_state(t_app *app);

#endif
