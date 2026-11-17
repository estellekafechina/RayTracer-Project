# RayTracer Project

This repository is a student C++ project that will grow into a ray tracer. The
current milestone only establishes a small, cross-platform build and test setup.

## Toolchain

- C++20
- [CMake](https://cmake.org/) 3.25 or newer
- [Ninja](https://ninja-build.org/)
- [Catch2](https://github.com/catchorg/Catch2) 3.16.1, downloaded by CMake
- CTest as the common test runner

CMake provides the same project definition on Linux, macOS and Windows. The
committed presets use Ninja so that commands and build paths remain consistent
on every platform. The dev container is the reference environment when a native
toolchain is unavailable or when every contributor needs exactly the same setup.

## Everyday shortcuts

CMake workflow presets remain the source of truth, while the Makefile provides
short equivalents to common `npm run` commands:

| Task | Command |
|---|---|
| Remove compiled development files | `make clean` |
| Build the development project | `make build` |
| Build and run the application | `make run` |
| Build and run all tests | `make test` |

Run these commands from the repository root. They are available in the dev
container and work natively wherever CMake and Make are installed.

## Quick start with a dev container

Requirements:

- Docker
- an editor with [Dev Container](https://containers.dev/) support, such as
  VS Code or Zed

1. Clone the repository and open its directory in the editor.
2. Choose **Reopen in Container** (VS Code) or the equivalent dev-container
   command in your editor.
3. Wait for the image to build and for the initial CMake configuration to finish.
4. In the container terminal, build and run the demo:

   ```sh
   make run
   ```

Expected output:

```text
Hello, World!
```

The container is Linux-based and includes GCC, CMake, Ninja, Git and debugging
tools. The source directory is mounted into it, so edits remain in the local
repository.

## Native build

Install a C++20 compiler, CMake 3.25+ and Ninja, then run these commands from
the repository root:

```sh
cmake --preset dev
cmake --build --preset dev
ctest --preset dev
```

Run the demo on Linux or macOS:

```sh
./build/dev/raytracer
```

Run it from PowerShell on Windows:

```powershell
.\build\dev\raytracer.exe
```

The first CMake configuration needs an internet connection to download the
pinned Catch2 release. Later builds reuse the copy stored under `build/`.

For an optimized build without tests:

```sh
cmake --preset release
cmake --build --preset release
```

## Test-driven development

Tests live in `tests/` and use Catch2 assertions. CTest remains the top-level
runner, which means the same test command works locally, in the container and
in a future CI pipeline.

Use this red-green-refactor loop:

1. **Red:** add a small test that describes the next behaviour.
2. Build and run the tests; confirm that the new test fails for the expected
   reason.
3. **Green:** write the smallest implementation that makes it pass.
4. **Refactor:** improve the design while keeping all tests green.

Build and run the complete test suite:

```sh
make test
```

Run the Catch2 executable directly when filtering tests or inspecting its
more detailed output:

```sh
./build/dev/tests/raytracer_tests "[greeting]"
```

On Windows, use `build\dev\tests\raytracer_tests.exe` instead. When a new test
source file is added, list it in `tests/CMakeLists.txt` and rebuild.

## Project layout

```text
.
├── .devcontainer/       # Reproducible Linux development environment
├── app/                 # Executable entry point
├── include/raytracer/   # Public headers
├── src/                 # Library implementation
├── tests/               # Catch2 tests
├── CMakeLists.txt       # Project and target definitions
└── CMakePresets.json    # Shared development and release commands
```

The discovery work is documented in
[`docs/discovery/discovery-report.md`](docs/discovery/discovery-report.md).
