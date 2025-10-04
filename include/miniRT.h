/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:32:32 by fkeitel           #+#    #+#             */
/*   Updated: 2025/10/04 12:00:49 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# include "MLX42/MLX42.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "structs/app_structs.h"
# include "structs/parsing_structs.h"
# include "functions/parsing.h"
# include "functions/init.h"
# include "functions/calculations.h"
# include "functions/rendering.h"
# include "functions/user_input.h"
# include "functions/cleanup.h"
# include "functions/debugging.h"

// Default window settings
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

#endif
