#include "../../include/miniRT.h"

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_app *app = (t_app *)param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(app->mlx);
}
