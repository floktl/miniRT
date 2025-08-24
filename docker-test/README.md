# miniRT Docker Testing Environment

This Docker setup provides a Linux environment with valgrind for testing your miniRT project for memory leaks.

## Prerequisites

- Docker installed on your system
- Docker Compose installed

## Quick Start

1. **Build the Docker image:**
   ```bash
   ./docker-test/build.sh
   ```

2. **Start the container:**
   ```bash
   ./docker-test/run.sh
   ```

3. **Test a specific scene:**
   ```bash
   ./docker-test/test_scene.sh scenes/sample.rt
   ```

4. **Test all scenes:**
   ```bash
   ./docker-test/test_all.sh
   ```

5. **Using Makefile (recommended):**
   ```bash
   # Test single scene
   make container-test SCENE=scenes/sample.rt

   # Test all scenes with full output
   make container-test-all

   # Test all scenes with summary only
   make container-test-quick
   ```

5. **Stop the container:**
   ```bash
   ./docker-test/stop.sh
   ```

## Manual Usage

### Access the container interactively:
```bash
docker exec -it minirt-valgrind-test bash
```

### Run valgrind manually:
```bash
# Inside the container
./run_valgrind.sh scenes/sample.rt
```

### Available scenes:
- `scenes/sample.rt`
- `scenes/colorful.rt`
- `scenes/multi_spheres.rt`
- `scenes/room.rt`
- `scenes/miniRT_samples/*.rt`

## What's Included

- **Ubuntu 22.04** base image
- **valgrind** for memory leak detection
- **clang/clang++** compilers
- **cmake** and **git** for building dependencies
- **GLFW** and OpenGL libraries
- **MLX42** library (automatically cloned and built)

## Valgrind Configuration

The setup uses the same valgrind configuration as your local environment:
- Full leak checking
- All leak kinds shown
- Track origins enabled
- Suppressions from `valgrind.supp`

## Results

Test results are automatically saved to the `test_results/` directory with timestamps:

### Summary Files
- `test_summary_YYYYMMDD_HHMMSS.txt` - Individual test results
- `test_summary_all_YYYYMMDD_HHMMSS.txt` - Complete test suite summary

### Detailed Files
- `valgrind_scene_name_YYYYMMDD_HHMMSS.txt` - Full valgrind output
- `test_scene_name_YYYYMMDD_HHMMSS.txt` - Individual test output

### Terminal Output
- **Single test**: Shows only pass/fail status
- **All tests**: Shows summary statistics (passed/failed/warnings)
- **Quick test**: Shows only final summary

## Troubleshooting

### Container won't start:
- Make sure Docker is running
- Check if port conflicts exist
- Try rebuilding: `./docker-test/build.sh`

### Build fails:
- Check your internet connection (needs to download MLX42)
- Ensure all source files are present
- Check the Makefile configuration

### Valgrind shows false positives:
- The `valgrind.supp` file suppresses known library leaks
- Focus on "definitely lost" leaks in your code
- "possibly lost" and "indirectly lost" may be from libraries

## Code Flow for Testing

1. **Build Process** (`docker-test/Dockerfile`):
   - Installs dependencies (lines 8-20)
   - Copies project files (line 25)
   - Builds miniRT (line 28)
   - Creates valgrind test script (lines 30-75)

2. **Test Execution** (`docker-test/test_scene.sh`):
   - Starts container if not running (lines 15-18)
   - Runs valgrind test (line 21)
   - Copies results to host (lines 24-25)

3. **Valgrind Analysis** (`run_valgrind.sh` inside container):
   - Validates scene file (lines 8-20)
   - Runs valgrind with full options (lines 22-29)
   - Analyzes results for different leak types (lines 31-50)
