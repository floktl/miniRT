#include "../../include/miniRT.h"

static t_color clamp_color(t_color c)
{
	// TODO: Clamp r,g,b to 0-255
	return c;
}

t_color compute_lighting(t_vec3 point, t_vec3 normal, t_scene *scene, t_color obj_color)
{
	// TODO: Compute ambient + diffuse per light, multiply by obj_color, clamp
	return (t_color){0,0,0};  // Stub black
}
