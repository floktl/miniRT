# Scripts Directory

This directory contains utility scripts for testing, debugging, and development of the miniRT project.

## Available Scripts

### Testing Scripts
- **`test_scenes.sh`** - Run tests on all scene files in the scenes directory
- **`debug_test.sh`** - Debug version of the test script with verbose output
- **`debug_test_execution.sh`** - Execute tests with detailed debugging information

### Usage

```bash
# Run all scene tests
./scripts/test_scenes.sh

# Run tests with debug output
./scripts/debug_test.sh

# Run tests with execution debugging
./scripts/debug_test_execution.sh
```

### Docker Testing

For Docker-based testing and Valgrind memory checking, see the `docker-test/` directory in the project root.

## Notes

- All scripts should be run from the project root directory
- Make sure the project is built (`make`) before running tests
- Test results are stored in `test_results/` directory
