#include "../../include/miniRT.h"

void free_scene(t_scene *scene)
{
	if (!scene) return;
	t_object *obj = scene->objects;
	while (obj)
	{
		t_object *tmp = obj;
		obj = obj->next;
		free(tmp);
	}
	scene->objects = NULL;
	t_light *light = scene->lights;
	while (light)
	{
		t_light *tmp = light;
		light = light->next;
		free(tmp);
	}
	scene->lights = NULL;
}
