# miniRT - 3D Ray Tracer

A 3D ray tracer implementation in C that renders scenes from configuration files. This project implements a complete ray tracing engine with support for multiple geometric primitives, lighting, textures, and bonus features.

## 🎯 Features

### Core Features
- **Ray Tracing Engine**: Complete 3D ray tracing implementation
- **Multiple Primitives**: Sphere, Plane, Cylinder, and Cone support
- **Lighting System**: Ambient, diffuse, and specular lighting with Phong reflection model
- **Camera System**: Configurable camera with field of view and positioning
- **Scene Parsing**: Custom parser for .rt scene files
- **Real-time Rendering**: Interactive window with MLX42 graphics library

### Bonus Features
- **Specular Reflection**: Configurable shininess for realistic reflections
- **Texture Mapping**: Checkerboard patterns and bump mapping
- **Multi-colored Lights**: Support for multiple colored light sources
- **Advanced Primitives**: Cone primitive implementation
- **Texture Scaling**: Configurable texture scale parameters

## 📁 Project Structure

```
miniRT/
├── include/                 # Header files
│   ├── miniRT.h            # Main header with data structures
│   └── parsing.h           # Parsing function declarations
├── srcs/                   # Source code
│   ├── main.c             # Main entry point
│   ├── init/              # Initialization functions
│   ├── parsing/           # Scene parsing (organized in subfolders)
│   │   ├── parser.c       # Main parser dispatch
│   │   ├── primitives/    # Geometric primitive parsing
│   │   ├── scene/         # Scene element parsing
│   │   ├── tokens/        # Token parsing utilities
│   │   ├── colors/        # Color parsing
│   │   ├── vectors/       # Vector parsing
│   │   └── validation/    # Input validation
│   ├── rendering/         # Ray tracing and rendering
│   ├── calculations/      # Mathematical utilities
│   ├── user_input/        # Keyboard and mouse handling
│   ├── cleanup/           # Memory management
│   └── debugging/         # Debug output functions
├── libft/                 # Custom C library
├── MLX42/                 # Graphics library
├── scenes/                # Scene configuration files
│   └── miniRT_samples/    # Test scenes
├── scripts/               # Utility scripts for testing and debugging
├── docker-test/           # Docker-based testing environment
├── test_results/          # Test outputs (ignored by git)
├── valgrind.supp          # Valgrind suppression file
└── Makefile              # Build configuration
```

## 🚀 Building and Running

### Prerequisites
- linux or macOS (for MLX42 compatibility)
- GCC compiler
- Make

### Build Instructions
```bash
# Clone the repository
git clone <repository-url>
cd miniRT

# Build the project
make

# Run with a scene file
./miniRT scenes/miniRT_samples/01_valid_minimal.rt
```

### Build Targets
- `make` - Build the project
- `make clean` - Remove object files
- `make fclean` - Remove all build artifacts
- `make re` - Rebuild from scratch

### Testing
- `./scripts/test_scenes.sh` - Run tests on all scene files
- `./scripts/debug_test.sh` - Run tests with debug output
- `make test` - Run tests using Docker (requires Docker)
- `make valgrind SCENE=scene.rt` - Run Valgrind memory check on specific scene

## 📝 Scene File Format (.rt)

Scene files define the 3D environment using a custom format:

### Scene Elements
```
# Ambient lighting
A <ratio> <color>

# Camera
C <position> <direction> <fov>

# Light sources
L <position> <brightness> <color>

# Geometric primitives
sp <center> <diameter> <color> [shininess] [texture_type] [texture_scale]
pl <point> <normal> <color> [shininess] [texture_type] [texture_scale]
cy <base> <axis> <diameter> <height> <color> [shininess] [texture_type] [texture_scale]
co <center> <axis> <radius> <height> <color> [shininess] [texture_type] [texture_scale]
```

### Parameters
- **Positions/Vectors**: `x,y,z` format (e.g., `0,0,5`)
- **Colors**: `r,g,b` format (0-255, e.g., `255,0,0`)
- **Shininess**: Optional specular reflection parameter (default: 32.0)
- **Texture Types**: `none`, `checkerboard`, `bump`
- **Texture Scale**: Optional scaling factor (default: 1.0)

### Example Scene
```
# Minimal valid scene
A 0.2 255,255,255
C 0,0,-5 0,0,1 70
L 10,10,10 0.6 255,255,255
sp 0,0,5 2 200,30,30
pl 0,-2,0 0,1,0 120,120,120
cy 2,0,8 0,0,1 1.5 3 10,80,220
```

## 🎮 Controls

- **ESC** - Exit the program

## 🧪 Testing

The project includes comprehensive test scenes:

```bash
# Basic functionality
./miniRT scenes/miniRT_samples/01_valid_minimal.rt

# Bonus features
./miniRT scenes/miniRT_samples/31_bonus_comprehensive_test.rt

# Error handling
./miniRT scenes/miniRT_samples/06_invalid_duplicate_capitals.rt
```

### Test Categories
- **Valid Scenes**: Basic functionality and edge cases
- **Invalid Scenes**: Error handling and validation
- **Bonus Scenes**: Advanced features demonstration

## 🔧 Technical Details

### Architecture
- **Modular Design**: Clean separation of concerns
- **Memory Management**: Proper allocation and cleanup
- **Error Handling**: Comprehensive error checking
- **Code Standards**: Norminette compliance

### Libraries Used
- **MLX42**: Graphics and window management
- **libft**: Custom C utility functions
- **Standard C**: Math, string, and file operations

### Performance
- **Optimized Rendering**: Efficient ray-object intersection
- **Memory Efficient**: Minimal memory footprint
- **Real-time**: Interactive rendering capabilities

## 📋 Requirements

### Mandatory Features
- [x] Sphere, Plane, Cylinder primitives
- [x] Ambient, diffuse, specular lighting
- [x] Camera with configurable FOV
- [x] Scene file parsing (.rt format)
- [x] Real-time rendering window
- [x] Error handling and validation

### Bonus Features
- [x] Specular reflection (shininess)
- [x] Texture mapping (checkerboard, bump)
- [x] Multi-colored lights
- [x] Cone primitive
- [x] Texture scaling

## 🐛 Debugging

Enable debug output by running with verbose parsing:
```bash
./miniRT scenes/miniRT_samples/01_valid_minimal.rt
```

The program will output:
- Parsing progress
- Scene validation
- Object details
- Error messages

## 📄 License

This project is part of the 42 School curriculum and follows their coding standards and requirements.

## 👥 Contributing

This is an educational project. For questions or issues, please refer to the 42 School guidelines.

---

**Note**: This project requires linux/macOS for MLX42 compatibility. Scene files must have a `.rt` extension and follow the specified format.
