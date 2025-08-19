#include "../../include/miniRT.h"

t_color parse_color(char *str)
{
    char **parts = ft_split(str, ',');
    if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3]) {
        int i = 0;
        while (parts && parts[i]) free(parts[i++]);
        free(parts);
        return (t_color){0,0,0};
    }
    t_color color;
    color.r = ft_atoi(parts[0]);
    color.g = ft_atoi(parts[1]);
    color.b = ft_atoi(parts[2]);
    if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255 || color.b < 0 || color.b > 255) {
        // Invalid color
        int i = 0;
        while (parts[i]) free(parts[i++]);
        free(parts);
        return (t_color){0,0,0};
    }
    int i = 0;
    while (parts[i]) free(parts[i++]);
    free(parts);
    return color;
}

t_vec3 parse_vec3(char *str)
{
    char **parts = ft_split(str, ',');
    if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3]) {
        int i = 0;
        while (parts && parts[i]) free(parts[i++]);
        free(parts);
        return (t_vec3){0,0,0};
    }
    t_vec3 vec;
    vec.x = ft_atof(parts[0]);
    vec.y = ft_atof(parts[1]);
    vec.z = ft_atof(parts[2]);
    int i = 0;
    while (parts[i]) free(parts[i++]);
    free(parts);
    return vec;
}

double parse_double(char *str)
{
    return ft_atof(str);  // Use custom ft_atof implemented in parser.c or libft
}

int parse_int(char *str)
{
	return ft_atoi(str);
}
