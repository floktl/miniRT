# miniRT Parsing Flow Chart

## Main Parsing Flow

```mermaid
flowchart TD
    A[Start: parse_scene] --> B[Open file]
    B --> C{File opened?}
    C -->|No| D[Error: Could not open file]
    C -->|Yes| E[Read line with get_next_line]
    E --> F{Line exists?}
    F -->|No| G[Close file]
    F -->|Yes| H[process_line]
    H --> I{Is comment/empty?}
    I -->|Yes| J[Free line, continue]
    I -->|No| K[parse_line]
    K --> L[Replace tabs with spaces]
    L --> M[Split line into tokens]
    M --> N{Tokens valid?}
    N -->|No| O[Free tokens, continue]
    N -->|Yes| P[Count tokens]
    P --> Q[dispatch_parse]
    Q --> R{Token type?}

    R -->|A| S[parse_ambient]
    R -->|C| T[parse_camera]
    R -->|L| U[parse_light]
    R -->|sp| V[parse_sphere]
    R -->|pl| W[parse_plane]
    R -->|cy| X[parse_cylinder]
    R -->|co| Y[parse_cone]
    R -->|Invalid| Z[Error: Invalid line]

    S --> AA[Free tokens]
    T --> AA
    U --> AA
    V --> AA
    W --> AA
    X --> AA
    Y --> AA
    Z --> AA

    AA --> BB{Parse success?}
    BB -->|No| CC[Error: Parsing failed]
    BB -->|Yes| DD[Continue to next line]
    DD --> E

    G --> EE[validate_scene]
    EE --> FF{Required elements?}
    FF -->|No| GG[Error: Missing required elements]
    FF -->|Yes| HH[Success: Scene parsed]

    J --> E
    O --> E
    CC --> II[Close file, return error]
```

## Scene Elements Parsing Flow

### Ambient Light Parsing
```mermaid
flowchart TD
    A[parse_ambient] --> B[check_ambient_duplicate]
    B --> C{Duplicate?}
    C -->|Yes| D[Error: Duplicate ambient]
    C -->|No| E[count_and_init_tokens]
    E --> F[parse_ambient_ratio]
    F --> G{Valid ratio?}
    G -->|No| H[Error: Invalid ratio]
    G -->|Yes| I[parse_ambient_color]
    I --> J{Valid color?}
    J -->|No| K[Error: Invalid color]
    J -->|Yes| L[set_ambient_data]
    L --> M[Success]
```

### Camera Parsing
```mermaid
flowchart TD
    A[parse_camera] --> B[check_camera_duplicate]
    B --> C{Duplicate?}
    C -->|Yes| D[Error: Duplicate camera]
    C -->|No| E[count_and_init_tokens]
    E --> F[parse_camera_position]
    F --> G{Valid position?}
    G -->|No| H[Error: Invalid position]
    G -->|Yes| I[parse_camera_direction]
    I --> J{Valid direction?}
    J -->|No| K[Error: Invalid direction]
    J -->|Yes| L[parse_camera_fov]
    L --> M{Valid FOV?}
    M -->|No| N[Error: Invalid FOV]
    M -->|Yes| O[set_camera_data]
    O --> P[Success]
```

### Light Parsing
```mermaid
flowchart TD
    A[parse_light] --> B[parse_light_internal]
    B --> C[count_and_init_tokens]
    C --> D[parse_light_position]
    D --> E{Valid position?}
    E -->|No| F[Error: Invalid position]
    E -->|Yes| G[parse_light_brightness]
    G --> H{Valid brightness?}
    H -->|No| I[Error: Invalid brightness]
    H -->|Yes| J[parse_light_color]
    J --> K{Valid color?}
    K -->|No| L[Error: Invalid color]
    K -->|Yes| M[create_light_object]
    M --> N[add_light_to_scene]
    N --> O[Success]
```

## Primitive Objects Parsing Flow

### Sphere Parsing
```mermaid
flowchart TD
    A[parse_sphere] --> B[create_sphere_object]
    B --> C[parse_sphere_position]
    C --> D{Valid position?}
    D -->|No| E[cleanup_object_error]
    D -->|Yes| F[parse_sphere_diameter]
    F --> G{Valid diameter?}
    G -->|No| E
    G -->|Yes| H[parse_sphere_color]
    H --> I{Valid color?}
    I -->|No| E
    I -->|Yes| J[parse_sphere_texture]
    J --> K[add_sphere_to_scene]
    K --> L[Success]
```

### Plane Parsing
```mermaid
flowchart TD
    A[parse_plane] --> B[create_plane_object]
    B --> C[parse_plane_position]
    C --> D{Valid position?}
    D -->|No| E[cleanup_object_error]
    D -->|Yes| F[parse_plane_normal]
    F --> G{Valid normal?}
    G -->|No| E
    G -->|Yes| H[parse_plane_color]
    H --> I{Valid color?}
    I -->|No| E
    I -->|Yes| J[parse_plane_texture]
    J --> K[add_plane_to_scene]
    K --> L[Success]
```

### Cylinder Parsing
```mermaid
flowchart TD
    A[parse_cylinder] --> B[create_cylinder_object]
    B --> C[parse_cylinder_position]
    C --> D{Valid position?}
    D -->|No| E[cleanup_object_error]
    D -->|Yes| F[parse_cylinder_normal]
    F --> G{Valid normal?}
    G -->|No| E
    G -->|Yes| H[parse_cylinder_diameter]
    H --> I{Valid diameter?}
    I -->|No| E
    I -->|Yes| J[parse_cylinder_height]
    J --> K{Valid height?}
    K -->|No| E
    K -->|Yes| L[parse_cylinder_color]
    L --> M{Valid color?}
    M -->|No| E
    M -->|Yes| N[parse_cylinder_texture]
    N --> O[add_cylinder_to_scene]
    O --> P[Success]
```

### Cone Parsing
```mermaid
flowchart TD
    A[parse_cone] --> B[create_cone_object]
    B --> C[parse_cone_position]
    C --> D{Valid position?}
    D -->|No| E[cleanup_object_error]
    D -->|Yes| F[parse_cone_normal]
    F --> G{Valid normal?}
    G -->|No| E
    G -->|Yes| H[parse_cone_diameter]
    H --> I{Valid diameter?}
    I -->|No| E
    I -->|Yes| J[parse_cone_height]
    J --> K{Valid height?}
    K -->|No| E
    K -->|Yes| L[parse_cone_color]
    L --> M{Valid color?}
    M -->|No| E
    M -->|Yes| N[parse_cone_texture]
    N --> O[add_cone_to_scene]
    O --> P[Success]
```

## Token Parsing Flow

### Vector Parsing
```mermaid
flowchart TD
    A[parse_vector] --> B[validate_vector_format]
    B --> C{Valid format?}
    C -->|No| D[Error: Invalid vector format]
    C -->|Yes| E[parse_float_tokens]
    E --> F{Valid floats?}
    F -->|No| G[Error: Invalid float values]
    F -->|Yes| H[create_vector]
    H --> I[Success]
```

### Color Parsing
```mermaid
flowchart TD
    A[parse_color] --> B[validate_color_format]
    B --> C{Valid format?}
    C -->|No| D[Error: Invalid color format]
    C -->|Yes| E[parse_integer_tokens]
    E --> F{Valid integers?}
    F -->|No| G[Error: Invalid integer values]
    F -->|Yes| H[validate_color_range]
    H --> I{In range 0-255?}
    I -->|No| J[Error: Color out of range]
    I -->|Yes| K[create_color]
    K --> L[Success]
```

### Float Parsing
```mermaid
flowchart TD
    A[parse_float] --> B[validate_float_format]
    B --> C{Valid format?}
    C -->|No| D[Error: Invalid float format]
    C -->|Yes| E[ft_atof conversion]
    E --> F{Conversion success?}
    F -->|No| G[Error: Float conversion failed]
    F -->|Yes| H[Success]
```

## File Structure and Function Locations

### Main Parser Files:
1. `srcs/parsing/parser.c` - Main parsing entry point
2. `srcs/parsing/scene/parse_scene_elements.c` - Scene elements (A, C, L)
3. `srcs/parsing/primitives/parse_primitives.c` - Primitive objects (sp, pl, cy, co)
4. `srcs/parsing/tokens/parse_tokens.c` - Token parsing utilities
5. `srcs/parsing/vectors/parse_vector.c` - Vector parsing
6. `srcs/parsing/colors/parse_color.c` - Color parsing

### Key Functions by File:
- **parser.c**: `parse_scene()`, `parse_line()`, `dispatch_parse()`
- **parse_scene_elements.c**: `parse_ambient()`, `parse_camera()`, `parse_light()`
- **parse_primitives.c**: `parse_sphere()`, `parse_plane()`, `parse_cylinder()`, `parse_cone()`
- **parse_tokens.c**: `parse_float()`, `parse_integer()`
- **parse_vector.c**: `parse_vector()`
- **parse_color.c**: `parse_color()`

## Error Handling Flow

```mermaid
flowchart TD
    A[Error occurs] --> B{Error type?}
    B -->|File| C[File error - close and exit]
    B -->|Parse| D[Parse error - cleanup and exit]
    B -->|Validation| E[Validation error - cleanup and exit]
    B -->|Memory| F[Memory error - cleanup and exit]

    C --> G[Return error code 1]
    D --> G
    E --> G
    F --> G
```

## Success Flow

```mermaid
flowchart TD
    A[All lines parsed] --> B[validate_scene]
    B --> C{Required elements present?}
    C -->|No| D[Error: Missing required elements]
    C -->|Yes| E[Scene ready for rendering]
    E --> F[Return success code 0]
```

This flow chart shows the complete parsing pipeline from file opening to scene validation, including all the different object types and their specific parsing requirements.
