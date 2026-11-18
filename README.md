# RayTracer Project

This repository is a student C++ ray tracer project. The current version traces
one ray through the centre of a pinhole camera and returns the colour of a
sphere when the ray hits it.

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
(1, 0, 0)
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
in CI.

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
./build/dev/tests/raytracer_tests "[vector]"
```

On Windows, use `build\dev\tests\raytracer_tests.exe` instead. When a new test
source file is added, list it in `tests/CMakeLists.txt` and rebuild.

## Project layout

```text
.
├── .devcontainer/             # Reproducible Linux development environment
├── .github/                   # Contribution templates and CI workflow
├── docs/adr/                  # Architecture decision records
├── src/
│   ├── colour/                # Colour
│   ├── geometry/              # Ray and Sphere
│   ├── math/                  # Vector
│   ├── render/                # Camera and trace
│   └── main.cpp               # Executable entry point
├── tests/
│   ├── colour/                # Colour tests
│   ├── geometry/              # Ray and Sphere tests
│   ├── math/                  # Vector tests
│   ├── render/                # Camera and trace tests
│   ├── test_helpers.cpp
│   └── test_helpers.h
├── CMakeLists.txt             # Project and target definitions
└── CMakePresets.json          # Shared development and release commands
```

New classes go in the folder for their concept under `src/`, and their tests go
in the matching folder under `tests/`. Includes start from the `src/` root, as
described in [`docs/adr/0005-organize-source-by-concept.md`](docs/adr/0005-organize-source-by-concept.md).

The discovery work is documented in
[`docs/discovery/discovery-report.md`](docs/discovery/discovery-report.md).

## Contributing

Before submitting a change, read [CONTRIBUTING.md](CONTRIBUTING.md), the
[Code of Conduct](CODE_OF_CONDUCT.md) and the architecture decisions in
[`docs/adr/`](docs/adr/). Report suspected vulnerabilities privately according
to [SECURITY.md](SECURITY.md).

Pull requests are built and tested in the same dev container by GitHub Actions.

## Licence

This project is available under the [MIT Licence](LICENSE).
