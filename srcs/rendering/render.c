#include "../../include/miniRT.h"

static t_ray get_ray(t_app *app, int x, int y)
{
	// TODO: Compute ray direction based on camera and pixel
	return (t_ray){(t_vec3){0,0,0}, (t_vec3){0,0,1}};
}

static double find_closest_intersection(t_ray ray, t_scene *scene, t_object **hit_obj)
{
	// TODO: Loop over objects, find min t >0, set hit_obj
	*hit_obj = NULL;
	return -1.0;
}

static t_vec3 get_normal(t_vec3 point, t_object *obj)
{
	// TODO: Compute normal based on object type
	return (t_vec3){0,0,1};
}

void render_scene(t_app *app)
{
	// TODO: Loop over pixels, get ray, intersect, light, put pixel
	// For testing, fill with blue
	int x, y;
	uint32_t color = 0x0000FFFF;
	y = 0;
	while (y < app->window_height)
	{
		x = 0;
		while (x < app->window_width)
		{
			mlx_put_pixel(app->img, x, y, color);
			x++;
		}
		y++;
	}
}
