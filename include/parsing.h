/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:30:00 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 10:16:43 by Florian Kei      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// Forward declarations for types defined in miniRT.h
typedef struct s_scene		t_scene;
typedef struct s_object		t_object;
typedef struct s_light		t_light;
typedef struct s_color		t_color;
typedef struct s_vec3		t_vec3;
typedef struct s_color_res	t_clr_res;
typedef struct s_vec3_res	t_vec3_res;
typedef struct s_float_res	t_float_res;

// parsing/parser.c
int			parse_scene(const char *filename, t_scene *scene);
int			parse_line(char *line, t_scene *scene);

// parsing/scene/parser_utils.c
int			count_tokens(char **tokens);
void		trim_token(char *token);
void		trim_all_tokens(char **tokens, int token_count);
void		replace_tabs_with_spaces(char *line);

// parsing/scene/parser_utils2.c
int			dispatch_and_return(t_scene *scene, char **tokens, const char *type,
				int (*parse_func)(char **, t_scene *));

// parsing/scene/parse_scene_elements.c
int			parse_ambient(char **tokens, t_scene *scene);
int			parse_camera(char **tokens, t_scene *scene);
int			parse_light(char **tokens, t_scene *scene);

// parsing/scene/parse_scene_utils.c
int			check_ambient_duplicate(t_scene *scene);
int			check_camera_duplicate(t_scene *scene);
int			validate_ambient_ratio(float ratio);
int			validate_camera_fov(float fov);
int			validate_light_brightness(float brightness);

// parsing/scene/parse_scene_utils2.c
int			parse_error(const char *element, const char *message);
int			count_and_init_tokens(char **tokens, int *token_count, int *idx);
int			parse_ambient_ratio(char **tokens, int *idx, int token_count,
				t_float_res *fr);
int			set_ambient_data(t_scene *scene, t_float_res fr, t_color col);
int			set_camera_data(t_scene *scene, t_vec3_res pr, t_vec3_res dr,
				t_float_res fr);

// parsing/scene/parse_scene_utils3.c
int			parse_ambient_color(char **tokens, int *idx, int token_count,
				t_clr_res *cr);
int			parse_camera_position(char **tokens, int *idx, int token_count,
				t_vec3_res *pr);
int			parse_camera_direction(char **tokens, int *idx, int token_count,
				t_vec3_res *dr);
int			parse_camera_fov(char **tokens, int *idx, int token_count,
				t_float_res *fr);

// parsing/scene/parse_light_utils.c
int			cleanup_light_error(t_light *light, const char *message);
int			parse_light_position(char **tokens, int *idx, int token_count,
				t_vec3_res *pr);
int			parse_light_brightness(char **tokens, int *idx, int token_count,
				t_float_res *br);
int			parse_light_color(char **tokens, int *idx, int token_count,
				t_clr_res *cr);

// parsing/scene/parse_light_utils2.c
int			setup_light(t_light *light, t_scene *scene);
int			parse_light_internal(char **tokens, t_scene *scene);

// parsing/primitives/parse_sphere.c
int			validate_sphere_diameter(float diameter);
int			parse_sphere_center(t_object *obj, char **tokens, int *idx,
				int token_count);
int			parse_sphere_diameter(t_object *obj, char **tokens, int *idx,
				int token_count);
int			parse_sphere_color(t_object *obj, char **tokens, int *idx,
				int token_count);
int			validate_sphere_data(t_object *obj, t_float_res dr);

// parsing/primitives/parse_primitive_utils.c
int			validate_plane_normal(t_vec3 normal);
int			validate_cylinder_dimensions(float diameter, float height);
int			init_object_and_count(t_object **obj, char **tokens,
				int *token_count, int *idx);

// parsing/primitives/parse_primitive_utils2.c
int			parse_plane_point(t_object *obj, char **tokens, int *idx,
				int token_count);
int			parse_plane_normal(t_object *obj, char **tokens, int *idx,
				int token_count);
int			parse_plane_color(t_object *obj, char **tokens, int *idx,
				int token_count);
int			parse_cylinder_base(t_object *obj, char **tokens, int *idx,
				int token_count);
int			parse_cylinder_axis(t_object *obj, char **tokens, int *idx,
				int token_count);

// parsing/primitives/parse_primitive_utils3.c
int			parse_cylinder_dimensions(t_object *obj, char **tokens,
				int *idx, int token_count);
int			parse_cylinder_color(t_object *obj, char **tokens, int *idx,
				int token_count);
int			validate_cylinder_data(t_object *obj, t_float_res dr,
				t_float_res hr);

// parsing/primitives/parse_primitives.c
int			parse_sphere(char **tokens, t_scene *scene);
int			parse_plane(char **tokens, t_scene *scene);
int			parse_cylinder(char **tokens, t_scene *scene);
int			parse_cone(char **tokens, t_scene *scene);
int			cleanup_object_error(t_object *obj, const char *message);

// parsing/primitives/parse_shininess.c
int			parse_object_shininess(t_object *obj, char **tokens, int *idx,
				int token_count);

// parsing/primitives/parse_cone.c
int			parse_cone_center(t_object *obj, char **tokens, int *idx,
				int token_count);
int			parse_cone_axis(t_object *obj, char **tokens, int *idx,
				int token_count);
int			parse_cone_dimensions(t_object *obj, char **tokens, int *idx,
				int token_count);
int			parse_cone_color(t_object *obj, char **tokens, int *idx,
				int token_count);
int			validate_cone_data(t_object *obj);

// parsing/primitives/parse_textures.c
int			parse_texture_type(t_object *obj, char **tokens, int *idx,
				int token_count);
int			parse_texture_scale(t_object *obj, char **tokens, int *idx,
				int token_count);

// parsing/colors/parse_color.c
t_color		parse_color(char *str);
int			is_color_zero(t_color c);

// parsing/colors/parse_color_utils.c
t_color		validate_color(t_color color, char **parts);
int			validate_color_values(t_color color);
int			clean_newlines(char *str);
int			trim_part(char *part, char **trimmed);
int			process_parts(char **parts, char **trimmed_parts);

// parsing/colors/parse_color_utils2.c
int			validate_and_parse_parts(char **trimmed_parts, char **parts,
				char *clean_str);
void		cleanup_memory(char **trimmed_parts, char **parts, char *clean_str);

// parsing/vectors/parse_vector.c
t_vec3		parse_vec3(char *str);
int			is_vec_zero(t_vec3 v);
int			is_vec_normalized(t_vec3 v);

// parsing/validation/parse_validation.c
int			is_integer_string(const char *str);

// parsing/tokens/parse_tokens.c
t_clr_res	parse_color_tokens(char **tokens, int *idx, int token_count);

// parsing/tokens/parse_token_utils.c
int			handle_single_token(char **tokens, int *idx, char **str);
int			check_color_validity(t_color c, char *str);
int			process_color_tokens_loop(char **tokens, int *idx, int token_count,
				char **str);
t_clr_res	init_clr_res(void);

// parsing/tokens/parse_tokens_vec.c
t_vec3_res	parse_vec3_tokens(char **tokens, int *idx, int token_count);

// parsing/vectors/parse_vec_token_utils.c
t_vec3_res	init_vec3_res(void);
t_vec3_res	process_single(char **tokens, int *local_idx, char **str);
t_vec3_res	handle_loop(char **tokens, int *local_idx, int token_count,
				char **str);

// parsing/vectors/parse_vec_token_utils2.c
int			handle_single_vec_token(char **tokens, int *local_idx, char **str);
int			check_vec_validity(t_vec3 v, char *str);
t_vec3_res	set_vec3_res(t_vec3 v, int local_idx, int *idx);
int			process_vec_tokens_loop(char **tokens, int *local_idx,
				int token_count, char **str);

// parsing/tokens/parse_tokens_float.c
t_float_res	parse_float_tokens(char **tokens, int *idx, int token_count);

#endif
