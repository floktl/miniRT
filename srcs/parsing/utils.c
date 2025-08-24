/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:26:49 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/24 11:07:06 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <math.h>

static t_color	validate_color(t_color color, char **parts)
{
	int	i;

	if (color.r < 0 || color.r > 255
		|| color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
	{
		printf("color invalid");
		i = 0;
		while (parts[i])
			free(parts[i++]);
		free(parts);
		return ((t_color){0, 0, 0});
	}
	return (color);
}

static int	validate_color_values(t_color c)
{
	if (c.r < 0 || c.r > 255)
		return (1);
	if (c.g < 0 || c.g > 255)
		return (1);
	if (c.b < 0 || c.b > 255)
		return (1);
	return (0);
}

t_color	parse_color(char *str)
{
	char	**parts;
	int		i;
	t_color	color;
	char *trimmed_parts[3];
	char *clean_str;

	// Create a copy of the string and remove newlines
	clean_str = ft_strdup(str);
	if (!clean_str) {
		return ((t_color){0, 0, 0});
	}

	// Remove newlines from the string
	i = 0;
	while (clean_str[i]) {
		if (clean_str[i] == '\n' || clean_str[i] == '\r') {
			clean_str[i] = '\0';
			break;
		}
		i++;
	}

	parts = ft_split(clean_str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3]
		|| ft_strlen(parts[0]) == 0 || ft_strlen(parts[1]) == 0 || ft_strlen(parts[2]) == 0)
	{
		i = 0;
		while (parts && parts[i])
			free(parts[i++]);
		free(parts);
		free(clean_str);
		return ((t_color){0, 0, 0});
	}

	// Create trimmed copies of each part
	for (i = 0; i < 3; i++) {
		char *part = parts[i];
		// Skip leading whitespace
		while (*part == ' ' || *part == '\t') part++;
		// Find end and remove trailing whitespace
		int len = ft_strlen(part);
		while (len > 0 && (part[len-1] == ' ' || part[len-1] == '\t')) {
			len--;
		}
		// Create trimmed copy
		trimmed_parts[i] = malloc(len + 1);
		if (trimmed_parts[i]) {
			ft_strlcpy(trimmed_parts[i], part, len + 1);
		} else {
			// Handle malloc failure
			for (int j = 0; j < i; j++) {
				free(trimmed_parts[j]);
			}
			i = 0;
			while (parts[i])
				free(parts[i++]);
			free(parts);
			free(clean_str);
			return ((t_color){0, 0, 0});
		}
	}

	// Validate that all parts are integers
	if (!is_integer_string(trimmed_parts[0]) || !is_integer_string(trimmed_parts[1]) || !is_integer_string(trimmed_parts[2])) {
		// Free trimmed parts
		for (i = 0; i < 3; i++) {
			free(trimmed_parts[i]);
		}
		// Free original parts
		i = 0;
		while (parts[i])
			free(parts[i++]);
		free(parts);
		free(clean_str);
		return ((t_color){0, 0, 0});
	}

	color.r = ft_atoi(trimmed_parts[0]);
	color.g = ft_atoi(trimmed_parts[1]);
	color.b = ft_atoi(trimmed_parts[2]);

	// Free trimmed parts
	for (i = 0; i < 3; i++) {
		free(trimmed_parts[i]);
	}

	// Free original parts
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
	free(clean_str);
	if (validate_color_values(color))
		return ((t_color){0, 0, 0});
	return (color);
}


t_vec3	parse_vec3(char *str)
{
	char	**parts;
	t_vec3	vec;
	int		i;

	parts = ft_split(str, ',');
	i = 0;
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3]
		|| ft_strlen(parts[0]) == 0 || ft_strlen(parts[1]) == 0 || ft_strlen(parts[2]) == 0)
	{
		while (parts && parts[i])
			free(parts[i++]);
		free(parts);
		return ((t_vec3){0, 0, 0});
	}
	vec.x = ft_atof(parts[0]);
	vec.y = ft_atof(parts[1]);
	vec.z = ft_atof(parts[2]);
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (vec);
}

int is_color_zero(t_color c)
{
	return (c.r == 0 && c.g == 0 && c.b == 0);
}

int is_vec_zero(t_vec3 v)
{
	return (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f);
}

// Check if a vector is normalized (unit length)
int is_vec_normalized(t_vec3 v)
{
	double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (fabs(length - 1.0) < 0.0001);
}

// Check if a string represents an integer
int is_integer_string(const char *str)
{
	if (!str || !*str) return 0;

	// Skip leading whitespace
	while (*str == ' ' || *str == '\t') str++;

	// Handle sign
	if (*str == '+' || *str == '-') str++;

	// Must have at least one digit
	if (!*str || !(*str >= '0' && *str <= '9')) return 0;

	// Check all characters are digits
	while (*str) {
		if (*str < '0' || *str > '9') return 0;
		str++;
	}

	return 1;
}

color_result parse_color_tokens(char **tokens, int *idx, int token_count)
{
	color_result res = {{0, 0, 0}, 0};
	char *str = ft_strdup("");
	int local_idx = *idx;
	t_color c;
	char *tmp;

	if (local_idx >= token_count) {
		free(str);
		return res;
	}

	// Start with the first token
	tmp = ft_strdup(tokens[local_idx]);
	free(str);
	str = tmp;
	local_idx++;

	// Try to parse as color
	c = parse_color(str);
	// Check if it's a valid color (not 0,0,0 unless that's what was actually parsed)
	if (!is_color_zero(c) || (ft_strncmp(str, "0,0,0", 5) == 0 && ft_strlen(str) == 5)) {
		res.c = c;
		res.success = 1;
		*idx = local_idx;
		free(str);
		return res;
	}

	// If not a valid color, keep adding tokens until we get a valid color
	while (local_idx < token_count) {
		// Add a space before the next token if the current string doesn't end with a comma
		if (ft_strlen(str) > 0 && str[ft_strlen(str) - 1] != ',') {
			tmp = ft_strjoin(str, " ");
			free(str);
			str = tmp;
		}

		tmp = ft_strjoin(str, tokens[local_idx]);
		free(str);
		str = tmp;
		local_idx++;

		c = parse_color(str);
		// Check if it's a valid color (not 0,0,0 unless that's what was actually parsed)
		if (!is_color_zero(c) || (ft_strncmp(str, "0,0,0", 5) == 0 && ft_strlen(str) == 5)) {
			res.c = c;
			res.success = 1;
			*idx = local_idx;
			free(str);
			return res;
		}
	}
	free(str);
	return res;
}

vec3_result parse_vec3_tokens(char **tokens, int *idx, int token_count)
{
	vec3_result res = {{0.0f, 0.0f, 0.0f}, 0};
	char *str = ft_strdup("");
	int local_idx = *idx;
	t_vec3 v;
	char *tmp;

	if (local_idx >= token_count) {
		free(str);
		return res;
	}

	tmp = ft_strjoin(str, tokens[local_idx]);
	free(str);
	str = tmp;
	local_idx++;

	v = parse_vec3(str);
	if (!is_vec_zero(v) || ft_strncmp(str, "0,0,0", 5) == 0) {
		res.v = v;
		res.success = 1;
		*idx = local_idx;
		free(str);
		return res;
	}

	while (local_idx < token_count) {
		tmp = ft_strjoin(str, tokens[local_idx]);
		free(str);
		str = tmp;
		local_idx++;

		v = parse_vec3(str);
		if (!is_vec_zero(v) || ft_strncmp(str, "0,0,0", 5) == 0) {
			res.v = v;
			res.success = 1;
			*idx = local_idx;
			free(str);
			return res;
		}
	}
	free(str);
	return res;
}

float_result parse_float_tokens(char **tokens, int *idx, int token_count)
{
	float_result res = {0.0f, 0};
	char *str = ft_strdup("");
	int local_idx = *idx;
	float f;
	char *tmp;

	if (local_idx >= token_count) {
		free(str);
		return res;
	}

	// Start with the first token
	tmp = ft_strdup(tokens[local_idx]);
	free(str);
	str = tmp;
	local_idx++;

	// Try to parse as float
	f = ft_atof(str);
	// Check for invalid values (INF, NaN)
	if (isnan(f) || isinf(f)) {
		free(str);
		return res;
	}
	res.f = f;
	res.success = 1;
	*idx = local_idx;
	free(str);
	return res;
}
