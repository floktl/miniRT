#include "../../include/miniRT.h"
#include <fcntl.h>
#include <unistd.h>  // for write
#include <stdio.h>  // Add this for printf

static int count_tokens(char **tokens) {
    int count = 0;
    while (tokens[count]) count++;
    return count;
}

static int parse_line(char *line, t_scene *scene)
{
    printf("Parsing line: %s\n", line);
    char **tokens = ft_split(line, ' ');
    if (!tokens || !tokens[0]) {
        printf("Empty or invalid line\n");
        // Free and skip
        int i = 0;
        while (tokens && tokens[i]) { free(tokens[i]); i++; }
        free(tokens);
        return 0;
    }
    int token_count = count_tokens(tokens);
    printf("Token count: %d, First token: %s\n", token_count, tokens[0]);
    if (ft_strncmp(tokens[0], "A", 2) == 0 && token_count == 3) {
        printf("Parsing Ambient\n");
        scene->ambient.ratio = ft_atof(tokens[1]);
        scene->ambient.color = parse_color(tokens[2]);
        if (scene->ambient.ratio < 0 || scene->ambient.ratio > 1) return 1;
    } else if (ft_strncmp(tokens[0], "C", 2) == 0 && token_count == 4) {
        printf("Parsing Camera\n");
        scene->camera.position = parse_vec3(tokens[1]);
        scene->camera.direction = vec_normalize(parse_vec3(tokens[2]));
        scene->camera.fov = ft_atof(tokens[3]);
        if (scene->camera.fov < 0 || scene->camera.fov > 180) return 1;
    } else if (ft_strncmp(tokens[0], "L", 2) == 0 && token_count == 4) {
        printf("Parsing Light\n");
        t_light *light = malloc(sizeof(t_light));
        if (!light) return 1;
        light->position = parse_vec3(tokens[1]);
        light->brightness = ft_atof(tokens[2]);
        light->color = parse_color(tokens[3]);
        light->next = scene->lights;
        scene->lights = light;
        if (light->brightness < 0 || light->brightness > 1) { free(light); return 1; }
    } else if (ft_strncmp(tokens[0], "sp", 3) == 0 && token_count == 4) {
        t_object *obj = malloc(sizeof(t_object));
        if (!obj) return 1;
        obj->type = SPHERE;
        obj->data.sphere.center = parse_vec3(tokens[1]);
        obj->data.sphere.radius = ft_atof(tokens[2]) / 2.0;
        obj->color = parse_color(tokens[3]);
        obj->next = scene->objects;
        scene->objects = obj;
        if (obj->data.sphere.radius <= 0) { free(obj); return 1; }
    } else if (ft_strncmp(tokens[0], "pl", 3) == 0 && token_count == 4) {
        t_object *obj = malloc(sizeof(t_object));
        if (!obj) return 1;
        obj->type = PLANE;
        obj->data.plane.point = parse_vec3(tokens[1]);
        obj->data.plane.normal = vec_normalize(parse_vec3(tokens[2]));
        obj->color = parse_color(tokens[3]);
        obj->next = scene->objects;
        scene->objects = obj;
    } else if (ft_strncmp(tokens[0], "cy", 3) == 0 && token_count == 6) {
        t_object *obj = malloc(sizeof(t_object));
        if (!obj) return 1;
        obj->type = CYLINDER;
        obj->data.cylinder.base = parse_vec3(tokens[1]);
        obj->data.cylinder.axis = vec_normalize(parse_vec3(tokens[2]));
        obj->data.cylinder.radius = ft_atof(tokens[3]) / 2.0;
        obj->data.cylinder.height = ft_atof(tokens[4]);
        obj->color = parse_color(tokens[5]);
        obj->next = scene->objects;
        scene->objects = obj;
        if (obj->data.cylinder.radius <= 0 || obj->data.cylinder.height <= 0) { free(obj); return 1; }
    } else {
        printf("Invalid line format\n");
        // Invalid line
        int i = 0;
        while (tokens[i]) { free(tokens[i]); i++; }
        free(tokens);
        return 1;  // Error on invalid
    }
    // Free tokens
    int i = 0;
    while (tokens[i]) { free(tokens[i]); i++; }
    free(tokens);
    return 0;
}

int parse_scene(const char *filename, t_scene *scene)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        write(2, "Error: Could not open file\n", 27);
        return 1;
    }
    char *line;
    while ((line = get_next_line(fd)))
    {
        printf("Read line: %s\n", line);
        if (line[0] != '#' && line[0] != '\n' && line[0] != 0) {
            if (parse_line(line, scene) != 0) {
                free(line);
                close(fd);
                return 1;
            }
        }
        free(line);
    }
    close(fd);
    // Validation: ensure required elements
    if (scene->camera.fov == 0 || scene->ambient.ratio == 0) {
        printf("Validation failed: FOV=%f, Ambient ratio=%f\n", scene->camera.fov, scene->ambient.ratio);
        write(2, "Error: Missing required elements\n", 33);
        return 1;
    }
    return 0;
}
