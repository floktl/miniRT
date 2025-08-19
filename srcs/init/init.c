#include "../../include/miniRT.h"

int init_app(t_app *app)
{
	app->window_width = WINDOW_WIDTH;
	app->window_height = WINDOW_HEIGHT;
	app->mlx = mlx_init(app->window_width, app->window_height, "miniRT", true);
	if (!app->mlx)
		return (1);
	app->img = mlx_new_image(app->mlx, app->window_width, app->window_height);
	if (!app->img || mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
	{
		mlx_terminate(app->mlx);
		return (1);
	}
	return (0);
}
